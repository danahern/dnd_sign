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

#include <wifi_provisioning/manager.h>
#include <wifi_provisioning/scheme_ble.h>


#include "nvs.h"
#include "nvs_flash.h"

#include "dnd_wifi.h"
#include "dnd_wifi_console.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "DND_WIFI"
#define MAXIMUM_RETRY 5

/**********************
 *  EXTERNS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static void wifi_provisioning_init();


/**********************
 *  MODULE VARIABLES
 **********************/
/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

/**
 * Number of retries attempted
 **/
static uint8_t s_retry_num = 0;

// If the device has been provisioned
static bool s_provisioned = false;

/**
 * ESP WiFi Event loop parameters
 **/
// UNUSED
// esp_event_loop_args_t loop_args = {
//     .queue_size = 0,
//     .task_name = "evt_loop"
//     .task_priority = 5,
//     .task_stack_size = 0,
//     .task_core_id = 0
// };

/**
 * Handle to hold esp event loop
 **/
// UNUSED
// esp_event_loop_handle_t loop_handle;

/**********************
 *   Public Functions
 **********************/

void dnd_wifi_initialize()
{
    ESP_LOGI(TAG, "Initializing wifi");

    // Initialize wifi station
    ESP_ERROR_CHECK(esp_netif_init());

    // Create esp event loop
    ESP_ERROR_CHECK( esp_event_loop_create_default() );

    // Setup netif station config
    esp_netif_create_default_wifi_sta();

    // Wifi event group
    wifi_event_group = xEventGroupCreate();

    // wifi init config
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Listen to when we get an IP so we can start IoT connectoin
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        NULL));

    // Listen to all esp events
    ESP_ERROR_CHECK(esp_event_handler_instance_register(ESP_EVENT_ANY_BASE,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        NULL));

    // Listen to wifi provisioning
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_PROV_EVENT, 
                                                ESP_EVENT_ANY_ID, 
                                                &event_handler, 
                                                NULL));

    
    // Register wifi console commands
    dnd_wifi_register_wifi_network();

    wifi_provisioning_init();
}

// Returns wifi group so events can be listened to and waited on
EventGroupHandle_t dnd_wifi_event_group()
{
    return wifi_event_group;
}

/***
 *    Private functions
 ***/

static void wifi_provisioning_init()
{
    wifi_prov_mgr_config_t config = {
        .scheme = wifi_prov_scheme_ble,
        .scheme_event_handler = WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM
    };

    /* Initialize provisioning manager with the
     * configuration parameters set above */
    ESP_ERROR_CHECK(wifi_prov_mgr_init(config));

    /* Let's find out if the device is provisioned */
    ESP_ERROR_CHECK(wifi_prov_mgr_is_provisioned(&s_provisioned));
    
    /* If device is not yet provisioned start provisioning service */
    if (!s_provisioned) 
    {
        ESP_LOGI(TAG, "Starting provisioning");

#ifdef DND_WIFI_DEVICE_NAME
        char service_name[12] = DND_WIFI_DEVICE_NAME;
#else
        char service_name[12] = "dnd_sign_1";
#endif
        
        /* What is the security level that we want (0 or 1):
         *      - WIFI_PROV_SECURITY_0 is simply plain text communication.
         *      - WIFI_PROV_SECURITY_1 is secure communication which consists of secure handshake
         *          using X25519 key exchange and proof of possession (pop) and AES-CTR
         *          for encryption/decryption of messages.
         */
        wifi_prov_security_t security = WIFI_PROV_SECURITY_0;

        /* Do we want a proof-of-possession (ignored if Security 0 is selected):
         *      - this should be a string with length > 0
         *      - NULL if not used
         */
        const char *pop = NULL;

        /* What is the service key (could be NULL)
         * This translates to :
         *     - Wi-Fi password when scheme is wifi_prov_scheme_softap
         *     - simply ignored when scheme is wifi_prov_scheme_ble
         */
        const char *service_key = NULL;

        /* This will set a custom 128 bit UUID which will be included in the BLE advertisement
         * and will correspond to the primary GATT service that provides provisioning
         * endpoints as GATT characteristics. Each GATT characteristic will be
         * formed using the primary service UUID as base, with different auto assigned
         * 12th and 13th bytes (assume counting starts from 0th byte). The client side
         * applications must identify the endpoints by reading the User Characteristic
         * Description descriptor (0x2901) for each characteristic, which contains the
         * endpoint name of the characteristic */
        uint8_t custom_service_uuid[] = {
            /* LSB <---------------------------------------
             * ---------------------------------------> MSB */
            0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
            0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02,
        };

        /* If your build fails with linker errors at this point, then you may have
         * forgotten to enable the BT stack or BTDM BLE settings in the SDK (e.g. see
         * the sdkconfig.defaults in the example project) */
        wifi_prov_scheme_ble_set_service_uuid(custom_service_uuid);

        /* Start provisioning service */
        ESP_ERROR_CHECK(wifi_prov_mgr_start_provisioning(security, pop, service_name, service_key));

    } 
    else 
    {
        ESP_LOGI(TAG, "Already provisioned, starting Wi-Fi STA");

        /* We don't need the manager as device is already provisioned,
         * so let's release it's resources */
        wifi_prov_mgr_deinit();

        /* Start Wi-Fi in station mode */
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_start());
        
        /* Wait for Wi-Fi connection */
        xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);
    }
}

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    ESP_LOGD(TAG, "%s | Event base %s id %d", __func__, event_base, event_id);
    if (event_base == WIFI_PROV_EVENT) 
    {
        switch (event_id) {
            case WIFI_PROV_START:
                ESP_LOGI(TAG, "Provisioning started");
                break;
            case WIFI_PROV_CRED_RECV: {
                wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)event_data;
                ESP_LOGI(TAG, "Received Wi-Fi credentials"
                         "\n\tSSID     : %s\n\tPassword : %s",
                         (const char *) wifi_sta_cfg->ssid,
                         (const char *) wifi_sta_cfg->password);
                break;
            }
            case WIFI_PROV_CRED_FAIL: {
                wifi_prov_sta_fail_reason_t *reason = (wifi_prov_sta_fail_reason_t *)event_data;
                ESP_LOGE(TAG, "Provisioning failed!\n\tReason : %s"
                         "\n\tPlease reset to factory and retry provisioning",
                         (*reason == WIFI_PROV_STA_AUTH_ERROR) ?
                         "Wi-Fi station authentication failed" : "Wi-Fi access-point not found");
                break;
            }
            case WIFI_PROV_CRED_SUCCESS:
                ESP_LOGI(TAG, "Provisioning successful");
                break;
            case WIFI_PROV_END:
                /* De-initialize manager once provisioning is finished */
                wifi_prov_mgr_deinit();
                break;
            default:
                break;
        }
    }
    if(event_base == WIFI_EVENT)
    {
        if (event_id == WIFI_EVENT_STA_START)
        {
            esp_wifi_connect();
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
            if (s_retry_num < MAXIMUM_RETRY) {
                esp_wifi_connect();
                s_retry_num++;
                ESP_LOGI(TAG, "retry to connect to the AP");
            } else {
                xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
            }
            ESP_LOGI(TAG,"connect to the AP fail");
        } 
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        s_retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}
