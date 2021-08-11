idf_component_register(SRCS "dnd_aws.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp-aws-iot esp_wifi fatfs nvs_flash)
