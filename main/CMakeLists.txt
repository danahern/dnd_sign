idf_component_register(SRCS "main.c" "screen.c"
                    INCLUDE_DIRS .
                    REQUIRES lvgl lvgl_esp32_drivers spi_flash nvs_flash fatfs esp-aws-iot)
