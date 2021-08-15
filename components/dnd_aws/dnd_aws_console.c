/* Standard Includes */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS and ESP Includes */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"

#include "dnd_aws_console.h"


/*********************
 *      DEFINES
 *********************/
#define TAG "DND_AWS_CONSOLE"
#define CONSOLE_SSID_SIZE 33
#define CONSOLE_PASS_SIZE 65

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  MODULE VARIABLES
 **********************/

/**********************
 *   Public Functions
 **********************/

/***********************
 *   Private Functions
 ***********************/


/*
 * Function: set_wifi
 *
 *   Allows you to send ssid and password to connect to
 *
 */
static struct
{
    struct arg_str *ssid;
    struct arg_str *pass;
    struct arg_int *security;
    struct arg_int *pos;
    struct arg_end *end;
} wifi_args;

static int set_wifi(int argc, char **argv)
{
    uint8_t ssid[CONSOLE_SSID_SIZE];
    size_t ssid_len = 0;
    uint8_t pass[CONSOLE_PASS_SIZE];
    size_t pass_len = 0;
    uint16_t idx = 0;

    memset(ssid, 0, CONSOLE_SSID_SIZE);
    memset(pass, 0, CONSOLE_PASS_SIZE);

    int nerrors = arg_parse(argc, argv, (void **)&wifi_args);
    if (nerrors != 0)
    {
        arg_print_errors(stderr, wifi_args.end, argv[0]);
        return 1;
    }

    if (wifi_args.ssid->count)
    {
        ssid_len = strlen(wifi_args.ssid->sval[0]);
        memcpy(ssid, wifi_args.ssid->sval[0], ssid_len);
    }

    if (wifi_args.pass->count)
    {
        pass_len = strlen(wifi_args.pass->sval[0]);
        memcpy(pass, wifi_args.pass->sval[0], pass_len);

    }

    if (wifi_args.pos->count)
    {
        idx = wifi_args.pos->ival[0];
    }
    else {
        idx = 0;
    }


    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    // wifi_config_t wifi_config = {
    //     .sta = {
    //         .ssid = ssid,
    //         .password = pass,
    //     },
    // };
    wifi_config_t wifi_config = {0};
    memcpy(wifi_config.sta.ssid, ssid, ssid_len);
    memcpy(wifi_config.sta.password, pass, pass_len);

    
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );

    // WIFISecurity_t security;

    

    

    // if (wifi_args.security->count)
    // {
    //     security = (WIFISecurity_t)wifi_args.security->ival[0];
    // }
    // else {
    //     security = eWiFiSecurityWPA;
    // }

    ESP_LOGI(TAG, "Adding wifi");

    // WIFINetworkProfile_t profile = {0};
    // WIFINetworkProfile_t saved_profile = {0};
    // WIFIReturnCode_t result;
    // WIFINetworkParams_t connect_params = {0};

    // memcpy(&m_ssid, ssid, ssid_len+1);
    // memcpy(&m_pass, pass, pass_len+1);

    // m_network_params.pcSSID = (char *)m_ssid;
    // m_network_params.ucSSIDLength = ssid_len;
    // m_network_params.pcPassword = (char *)m_pass;
    // m_network_params.ucPasswordLength = pass_len;
    // m_network_params.xSecurity = security;



    // m_network_profile.xSecurity = security;
    // memcpy(m_network_profile.cPassword, (char *)pass, pass_len+1);
    // m_network_profile.ucPasswordLength = pass_len+1;
    // memcpy(m_network_profile.cSSID, (char *)ssid, ssid_len+1);
    // m_network_profile.ucSSIDLength = ssid_len+1;

    // printf("Network\n");
    // printf("\tSSID (len %d): %s\n", profile.ucSSIDLength, profile.cSSID);
    // printf("\tPASS (len %d): %s\n", profile.ucPasswordLength, profile.cPassword);
    // printf("\tSec:  %d\n", profile.xSecurity);


    // WIFIReturnCode_t res = WIFI_On();
    // printf(" Wifi on %d\n", res);

    // result = WIFI_NetworkAdd( &profile, &idx);
    // printf("Network Add Result: %d\n", result);

    // result = WIFI_NetworkGet( &saved_profile, idx);
    // printf("Network Get Result: %d\n", result);
    // printf("\tSSID (len %d): %s\n", saved_profile.ucSSIDLength, saved_profile.cSSID);
    // printf("\tPASS (len %d): %s\n", saved_profile.ucPasswordLength, saved_profile.cPassword);
    // printf("\tSec:  %d\n", saved_profile.xSecurity);

    // result = WIFI_ConnectAP( &connect_params );
    // printf("Connection Result: %d\n", result);

    // printf("Connecting to  SSID: %.*s\n", ssid_len, (const char*)ssid);
    // printf("               PASS: %.*s\n", pass_len, (const char*)pass);


    // xTaskNotify(console_wifi_task, CONSOLE_WIFI_ADD, eSetValueWithOverwrite);

    return ESP_OK;
}

void dnd_aws_register_wifi_network()
{
    wifi_args.ssid =
        arg_str0(NULL, NULL, "<n>",
                 "WiFi SSID");
    wifi_args.pass =
        arg_str0(NULL, NULL, "<n>",
                 "Password");
    wifi_args.security =
        arg_int0(NULL, NULL, "<n>",
                 "Security Type Number:\n\t0 - Open\n\t1 - WEP\n\t2 - WPA\n\t3 - WPA2\n");
    wifi_args.pos =
        arg_int0(NULL, NULL, "<n>",
                 "Postion to add the network");
    wifi_args.end = arg_end(3);
    const esp_console_cmd_t cmd = {
        .command = "set_wifi",
        .help = "Setup Wifi Network",
        .hint = NULL,
        .func = &set_wifi,
        .argtable = &wifi_args
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd));
}