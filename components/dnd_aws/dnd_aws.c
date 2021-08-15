/*
    Do Not Disturb AWS connection
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_shadow_interface.h"

#include "dnd_aws_console.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "DNDAWS"
#define AWS_IOT_STACK 9216
#define AWS_IOT_PRIORITY 5
#define AWS_IOT_CORE 1

#define MAX_LENGTH_OF_UPDATE_JSON_BUFFER 200
#define CONFIG_AWS_EXAMPLE_THING_NAME "dnd_sign_1"
#define CONFIG_AWS_EXAMPLE_CLIENT_ID "dnd_sign_1"

/**********************
 *  EXTERNS
 **********************/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t aws_root_ca_pem_end[] asm("_binary_aws_root_ca_pem_end");
extern const uint8_t certificate_pem_crt_start[] asm("_binary_certificate_pem_crt_start");
extern const uint8_t certificate_pem_crt_end[] asm("_binary_certificate_pem_crt_end");
extern const uint8_t private_pem_key_start[] asm("_binary_private_pem_key_start");
extern const uint8_t private_pem_key_end[] asm("_binary_private_pem_key_end");

/**********************
 *  STATIC PROTOTYPES
 **********************/
static esp_err_t event_handler(void *ctx, system_event_t *event);
static void aws_iot_task(void *param);

/**********************
 *  MODULE VARIABLES
 **********************/
/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
const int CONNECTED_BIT = BIT0;

/**********************
 *   Public Functions
 **********************/

void dnd_aws_initialize()
{
    ESP_LOGI(TAG, "Initializing AWS");

    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    
    dnd_aws_register_wifi_network();

    /* Temporarily pin task to core, due to FPU uncertainty */
    xTaskCreatePinnedToCore(&aws_iot_task, "aws_iot_task", AWS_IOT_STACK, NULL, AWS_IOT_PRIORITY, NULL, AWS_IOT_CORE);
}

/***
 *    Private functions
 ***/

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

static bool shadowUpdateInProgress;

void ShadowUpdateStatusCallback(const char *pThingName, ShadowActions_t action, Shadow_Ack_Status_t status,
                                const char *pReceivedJsonDocument, void *pContextData) {
    IOT_UNUSED(pThingName);
    IOT_UNUSED(action);
    IOT_UNUSED(pReceivedJsonDocument);
    IOT_UNUSED(pContextData);

    shadowUpdateInProgress = false;

    if(SHADOW_ACK_TIMEOUT == status) {
        ESP_LOGE(TAG, "Update timed out");
    } else if(SHADOW_ACK_REJECTED == status) {
        ESP_LOGE(TAG, "Update rejected");
    } else if(SHADOW_ACK_ACCEPTED == status) {
        ESP_LOGI(TAG, "Update accepted");
    }
}

void windowActuate_Callback(const char *pJsonString, uint32_t JsonStringDataLen, jsonStruct_t *pContext) {
    IOT_UNUSED(pJsonString);
    IOT_UNUSED(JsonStringDataLen);

    if(pContext != NULL) {
        ESP_LOGI(TAG, "Delta - Window state changed to %d", *(bool *) (pContext->pData));
    }
}

static void aws_iot_task(void *param) {
    IoT_Error_t rc = FAILURE;

    char JsonDocumentBuffer[MAX_LENGTH_OF_UPDATE_JSON_BUFFER];
    size_t sizeOfJsonDocumentBuffer = sizeof(JsonDocumentBuffer) / sizeof(JsonDocumentBuffer[0]);
    float temperature = 0.0;

    bool windowOpen = false;
    jsonStruct_t windowActuator;
    windowActuator.cb = windowActuate_Callback;
    windowActuator.pData = &windowOpen;
    windowActuator.pKey = "windowOpen";
    windowActuator.type = SHADOW_JSON_BOOL;
    windowActuator.dataLength = sizeof(bool);

    jsonStruct_t temperatureHandler;
    temperatureHandler.cb = NULL;
    temperatureHandler.pKey = "temperature";
    temperatureHandler.pData = &temperature;
    temperatureHandler.type = SHADOW_JSON_FLOAT;
    temperatureHandler.dataLength = sizeof(float);

    ESP_LOGI(TAG, "AWS IoT SDK Version %d.%d.%d-%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

    // initialize the mqtt client
    AWS_IoT_Client mqttClient;

    ShadowInitParameters_t sp = ShadowInitParametersDefault;
    // Setup host and port
    sp.pHost = AWS_IOT_MQTT_HOST;
    sp.port = AWS_IOT_MQTT_PORT;

    // Setup Certificate
    sp.pClientCRT = (const char *)certificate_pem_crt_start;
    sp.pClientKey = (const char *)private_pem_key_start;
    sp.pRootCA = (const char *)aws_root_ca_pem_start;

    // Reconnect automatically if disconnected
    sp.enableAutoReconnect = false;

    // Handle disconnects
    sp.disconnectHandler = NULL;

    /* Wait for WiFI to show as connected */
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);

    // Initialize shadow
    ESP_LOGI(TAG, "Shadow Init");
    rc = aws_iot_shadow_init(&mqttClient, &sp);

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_shadow_init returned error %d, aborting...", rc);
        abort();
    }

    ShadowConnectParameters_t scp = ShadowConnectParametersDefault;
    scp.pMyThingName = CONFIG_AWS_EXAMPLE_THING_NAME;
    scp.pMqttClientId = CONFIG_AWS_EXAMPLE_CLIENT_ID;
    scp.mqttClientIdLen = (uint16_t) strlen(CONFIG_AWS_EXAMPLE_CLIENT_ID);

    ESP_LOGI(TAG, "Shadow Connect");
    rc = aws_iot_shadow_connect(&mqttClient, &scp);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_shadow_connect returned error %d, aborting...", rc);
        abort();
    }

    /*
     * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    rc = aws_iot_shadow_set_autoreconnect_status(&mqttClient, true);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Unable to set Auto Reconnect to true - %d, aborting...", rc);
        abort();
    }

    rc = aws_iot_shadow_register_delta(&mqttClient, &windowActuator);

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Shadow Register Delta Error");
    }
    temperature = 20.0f;

    // loop and publish a change in temperature
    while(NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc) {
        rc = aws_iot_shadow_yield(&mqttClient, 200);
        if(NETWORK_ATTEMPTING_RECONNECT == rc || shadowUpdateInProgress) {
            rc = aws_iot_shadow_yield(&mqttClient, 1000);
            // If the client is attempting to reconnect, or already waiting on a shadow update,
            // we will skip the rest of the loop.
            continue;
        }
        ESP_LOGI(TAG, "=======================================================================================");
        ESP_LOGI(TAG, "On Device: window state %s", windowOpen ? "true" : "false");

        rc = aws_iot_shadow_init_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
        if(SUCCESS == rc) {
            rc = aws_iot_shadow_add_reported(JsonDocumentBuffer, sizeOfJsonDocumentBuffer, 2, &temperatureHandler,
                                             &windowActuator);
            if(SUCCESS == rc) {
                rc = aws_iot_finalize_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
                if(SUCCESS == rc) {
                    ESP_LOGI(TAG, "Update Shadow: %s", JsonDocumentBuffer);
                    rc = aws_iot_shadow_update(&mqttClient, CONFIG_AWS_EXAMPLE_THING_NAME, JsonDocumentBuffer,
                                               ShadowUpdateStatusCallback, NULL, 4, true);
                    shadowUpdateInProgress = true;
                }
            }
        }
        ESP_LOGI(TAG, "*****************************************************************************************");
        ESP_LOGI(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(10000 / portTICK_RATE_MS);
    }

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "An error occurred in the loop %d", rc);
    }

    ESP_LOGI(TAG, "Disconnecting");
    rc = aws_iot_shadow_disconnect(&mqttClient);

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Disconnect error %d", rc);
    }

    vTaskDelete(NULL);
}
