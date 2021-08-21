idf_component_register(SRCS "dnd_wifi_console.c" "dnd_wifi.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_wifi bt wifi_provisioning fatfs nvs_flash console)
