idf_component_register(SRCS "dnd_aws_console.c" "dnd_aws.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp-aws-iot esp_wifi fatfs nvs_flash console)

target_add_binary_data(${COMPONENT_TARGET} "certs/aws-root-ca.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "certs/certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "certs/private.pem.key" TEXT)
                    