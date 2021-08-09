idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES da_screen spi_flash nvs_flash fatfs esp-aws-iot)
