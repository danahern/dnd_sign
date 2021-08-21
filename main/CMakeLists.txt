idf_component_register(SRCS "main.c" "screen.c"
                    INCLUDE_DIRS .
                    REQUIRES lvgl lvgl_esp32_drivers dnd_console spi_flash nvs_flash fatfs dnd_aws dnd_wifi console)
