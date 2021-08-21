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

#include "dnd_wifi.h"

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
static void aws_iot_task(void *param);

/**********************
 *  MODULE VARIABLES
 **********************/

static bool shadowUpdateInProgress;

/**
 * Context for the AWS IOT task as well as initialization and connection parameters
 **/
static struct _aws_iot_task_context_t
{
    AWS_IoT_Client client; // AWS IOT Client
    IoT_Client_Init_Params client_init_params; // Client initalization params
    IoT_Client_Connect_Params client_connect_params; // Client connection params
} aws_iot_context;

/**********************
 *   Public Functions
 **********************/

void dnd_aws_initialize()
{
    ESP_LOGI(TAG, "Initializing AWS");
    
    /* Temporarily pin task to core, due to FPU uncertainty */
    xTaskCreatePinnedToCore(&aws_iot_task, "aws_iot_task", AWS_IOT_STACK, NULL, AWS_IOT_PRIORITY, NULL, AWS_IOT_CORE);
}

/***
 *    Private functions
 ***/

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

static IoT_Error_t dnd_aws_mqtt_init()
{
    IoT_Error_t rc = FAILURE;

    // Set params to default
    aws_iot_context.client_init_params = iotClientInitParamsDefault;
    // Change params we want to change
    aws_iot_context.client_init_params.enableAutoReconnect = false; // We enable this later below
    aws_iot_context.client_init_params.pHostURL = AWS_IOT_MQTT_HOST;
    aws_iot_context.client_init_params.port = AWS_IOT_MQTT_PORT;
    aws_iot_context.client_init_params.pRootCALocation = (const char *)aws_root_ca_pem_start;
    aws_iot_context.client_init_params.pDeviceCertLocation = (const char *)certificate_pem_crt_start;
    aws_iot_context.client_init_params.pDevicePrivateKeyLocation = (const char *)private_pem_key_start;
    aws_iot_context.client_init_params.mqttCommandTimeout_ms = 20000;
    aws_iot_context.client_init_params.tlsHandshakeTimeout_ms = 5000;
    aws_iot_context.client_init_params.isSSLHostnameVerify = true;
    aws_iot_context.client_init_params.disconnectHandler = NULL;
    aws_iot_context.client_init_params.disconnectHandlerData = NULL;

    rc = aws_iot_mqtt_init(&aws_iot_context.client, &aws_iot_context.client_init_params);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_mqtt_init returned error : %d ", rc);
        abort();
    }

    return rc;
}

static IoT_Error_t dnd_aws_mqtt_connect()
{
    IoT_Error_t rc = FAILURE;

    ESP_LOGI(TAG, "Connecting to AWS...");
    aws_iot_context.client_connect_params.keepAliveIntervalInSec = 10;
    aws_iot_context.client_connect_params.isCleanSession = true;
    aws_iot_context.client_connect_params.MQTTVersion = MQTT_3_1_1;
    /* Client ID is set in the menuconfig of the example */
    aws_iot_context.client_connect_params.pClientID = CONFIG_AWS_EXAMPLE_CLIENT_ID;
    aws_iot_context.client_connect_params.clientIDLen = (uint16_t) strlen(CONFIG_AWS_EXAMPLE_CLIENT_ID);
    aws_iot_context.client_connect_params.isWillMsgPresent = false;

    do {
        rc = aws_iot_mqtt_connect(&aws_iot_context.client, &aws_iot_context.client_connect_params);
        if(SUCCESS != rc) {
            ESP_LOGE(TAG, "Error(%d) connecting to %s:%d", rc, aws_iot_context.client_init_params.pHostURL, aws_iot_context.client_init_params.port);
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    } while(SUCCESS != rc);

    return rc;
}

static IoT_Error_t dnd_aws_mqtt_subscribe()
{
    IoT_Error_t rc = FAILURE;

    const char *TOPIC = "test_topic/esp32";
    const int TOPIC_LEN = strlen(TOPIC);

    ESP_LOGI(TAG, "Subscribing...");
    void* iot_subscribe_callback_handler = NULL;
    rc = aws_iot_mqtt_subscribe(&aws_iot_context.client, TOPIC, TOPIC_LEN, QOS0, iot_subscribe_callback_handler, NULL);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Error subscribing : %d ", rc);
        abort();
    }

    return rc;
}

static IoT_Error_t dnd_aws_shadow_send()
{
    IoT_Error_t rc = FAILURE;
    char JsonDocumentBuffer[MAX_LENGTH_OF_UPDATE_JSON_BUFFER];
    size_t sizeOfJsonDocumentBuffer = sizeof(JsonDocumentBuffer) / sizeof(JsonDocumentBuffer[0]);
    float temperature = 0.0;
    temperature = 20.0f;


    bool windowOpen = false;
    jsonStruct_t windowActuator;
    windowActuator.cb = NULL;
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

    rc = aws_iot_shadow_init_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
    if(SUCCESS == rc) {
        rc = aws_iot_shadow_add_reported(JsonDocumentBuffer, sizeOfJsonDocumentBuffer, 2, &temperatureHandler,
                                            &windowActuator);
        if(SUCCESS == rc) {
            rc = aws_iot_finalize_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
            if(SUCCESS == rc) {
                ESP_LOGI(TAG, "Update Shadow: %s", JsonDocumentBuffer);
                rc = aws_iot_shadow_update(&aws_iot_context.client, CONFIG_AWS_EXAMPLE_THING_NAME, JsonDocumentBuffer,
                                            ShadowUpdateStatusCallback, NULL, 4, true);
                shadowUpdateInProgress = true;
            }
        }
    }
    return rc;
}

static void aws_iot_task(void *param) {
    IoT_Error_t rc = FAILURE;

    ESP_LOGI(TAG, "AWS IoT SDK Version %d.%d.%d-%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

    // dnd_aws_shadow_init();
    dnd_aws_mqtt_init();
    

    /* Wait for WiFI to show as connected */
    xEventGroupWaitBits(dnd_wifi_event_group(), WIFI_CONNECTED_BIT,
                        false, true, portMAX_DELAY);

    
    // dnd_aws_shadow_connect();
    dnd_aws_mqtt_connect();

    
    /*
     * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    rc = aws_iot_shadow_set_autoreconnect_status(&aws_iot_context.client, true);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Unable to set Auto Reconnect to true - %d, aborting...", rc);
        abort();
    }

    IOT_UNUSED(dnd_aws_mqtt_subscribe());

    // rc = aws_iot_shadow_register_delta(&aws_iot_context.client, NULL);

    // if(SUCCESS != rc) {
    //     ESP_LOGE(TAG, "Shadow Register Delta Error");
    // }
    
    // while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)) {

    //     //Max time the yield function will wait for read messages
    //     rc = aws_iot_mqtt_yield(&client, 100);
    //     if(NETWORK_ATTEMPTING_RECONNECT == rc) {
    //         // If the client is attempting to reconnect we will skip the rest of the loop.
    //         continue;
    //     }

    //     ESP_LOGI(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
    //     vTaskDelay(1000 / portTICK_RATE_MS);
    //     sprintf(cPayload, "%s : %d ", "hello from ESP32 (QOS0)", i++);
    //     paramsQOS0.payloadLen = strlen(cPayload);
    //     rc = aws_iot_mqtt_publish(&client, TOPIC, TOPIC_LEN, &paramsQOS0);

    //     sprintf(cPayload, "%s : %d ", "hello from ESP32 (QOS1)", i++);
    //     paramsQOS1.payloadLen = strlen(cPayload);
    //     rc = aws_iot_mqtt_publish(&client, TOPIC, TOPIC_LEN, &paramsQOS1);
    //     if (rc == MQTT_REQUEST_TIMEOUT_ERROR) {
    //         ESP_LOGW(TAG, "QOS1 publish ack not received.");
    //         rc = SUCCESS;
    //     }
    // }

    // loop and publish a change in temperature
    while(NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc) {
        //Max time the yield function will wait for read messages
        rc = aws_iot_mqtt_yield(&aws_iot_context.client, 100);

        if(NETWORK_ATTEMPTING_RECONNECT == rc || shadowUpdateInProgress) {
             rc = aws_iot_mqtt_yield(&aws_iot_context.client, 100);
            // If the client is attempting to reconnect, or already waiting on a shadow update,
            // we will skip the rest of the loop.
            continue;
        }
        dnd_aws_shadow_send();
        ESP_LOGI(TAG, "*****************************************************************************************");
        ESP_LOGI(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(10000 / portTICK_RATE_MS);
    }

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "An error occurred in the loop %d", rc);
    }

    ESP_LOGI(TAG, "Disconnecting");
    rc = aws_iot_shadow_disconnect(&aws_iot_context.client);

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Disconnect error %d", rc);
    }

    vTaskDelete(NULL);
}
