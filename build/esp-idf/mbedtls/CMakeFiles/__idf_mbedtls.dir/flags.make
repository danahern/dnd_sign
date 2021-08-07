# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# compile ASM with /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
# compile C with /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
ASM_FLAGS =   -ffunction-sections -fdata-sections -Wall -Werror=all -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare -ggdb -Og -fmacro-prefix-map=/home/danahern/code/dnd_sign=. -fmacro-prefix-map=/home/danahern/code/dnd_sign/esp-idf=IDF -fstrict-volatile-bitfields -Wno-error=unused-but-set-variable -fno-jump-tables -fno-tree-switch-conversion -D_GNU_SOURCE -DIDF_VER=\"v4.4-dev-2487-g8131d6f46\" -DESP_PLATFORM

ASM_DEFINES = -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"

ASM_INCLUDES = -I/home/danahern/code/dnd_sign/build/config -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/port/include -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/mbedtls/include -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/esp_crt_bundle/include -I/home/danahern/code/dnd_sign/esp-idf/components/newlib/platform_include -I/home/danahern/code/dnd_sign/esp-idf/components/freertos/include -I/home/danahern/code/dnd_sign/esp-idf/components/freertos/port/xtensa/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include/soc -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include/soc/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/port/esp32/. -I/home/danahern/code/dnd_sign/esp-idf/components/heap/include -I/home/danahern/code/dnd_sign/esp-idf/components/log/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/include/apps -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/include/apps/sntp -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/lwip/src/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/port/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/port/esp32/include/arch -I/home/danahern/code/dnd_sign/esp-idf/components/soc/include -I/home/danahern/code/dnd_sign/esp-idf/components/soc/esp32/. -I/home/danahern/code/dnd_sign/esp-idf/components/soc/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/platform_port/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/include/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_common/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/port/soc -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/port/public_compat -I/home/danahern/code/dnd_sign/esp-idf/components/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/xtensa/include -I/home/danahern/code/dnd_sign/esp-idf/components/xtensa/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/driver/include -I/home/danahern/code/dnd_sign/esp-idf/components/driver/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_pm/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_ringbuf/include -I/home/danahern/code/dnd_sign/esp-idf/components/efuse/include -I/home/danahern/code/dnd_sign/esp-idf/components/efuse/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/vfs/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_wifi/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_event/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_netif/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_eth/include -I/home/danahern/code/dnd_sign/esp-idf/components/tcpip_adapter/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_phy/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_phy/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_ipc/include -I/home/danahern/code/dnd_sign/esp-idf/components/app_trace/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_timer/include 

C_FLAGS = -mlongcalls -Wno-frame-address   -ffunction-sections -fdata-sections -Wall -Werror=all -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare -ggdb -Og -fmacro-prefix-map=/home/danahern/code/dnd_sign=. -fmacro-prefix-map=/home/danahern/code/dnd_sign/esp-idf=IDF -fstrict-volatile-bitfields -Wno-error=unused-but-set-variable -fno-jump-tables -fno-tree-switch-conversion -std=gnu99 -Wno-old-style-declaration -D_GNU_SOURCE -DIDF_VER=\"v4.4-dev-2487-g8131d6f46\" -DESP_PLATFORM

C_DEFINES = -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"

C_INCLUDES = -I/home/danahern/code/dnd_sign/build/config -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/port/include -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/mbedtls/include -I/home/danahern/code/dnd_sign/esp-idf/components/mbedtls/esp_crt_bundle/include -I/home/danahern/code/dnd_sign/esp-idf/components/newlib/platform_include -I/home/danahern/code/dnd_sign/esp-idf/components/freertos/include -I/home/danahern/code/dnd_sign/esp-idf/components/freertos/port/xtensa/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include/soc -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/include/soc/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_hw_support/port/esp32/. -I/home/danahern/code/dnd_sign/esp-idf/components/heap/include -I/home/danahern/code/dnd_sign/esp-idf/components/log/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/include/apps -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/include/apps/sntp -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/lwip/src/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/port/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/lwip/port/esp32/include/arch -I/home/danahern/code/dnd_sign/esp-idf/components/soc/include -I/home/danahern/code/dnd_sign/esp-idf/components/soc/esp32/. -I/home/danahern/code/dnd_sign/esp-idf/components/soc/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/include -I/home/danahern/code/dnd_sign/esp-idf/components/hal/platform_port/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/include/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_rom/esp32 -I/home/danahern/code/dnd_sign/esp-idf/components/esp_common/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/port/soc -I/home/danahern/code/dnd_sign/esp-idf/components/esp_system/port/public_compat -I/home/danahern/code/dnd_sign/esp-idf/components/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/xtensa/include -I/home/danahern/code/dnd_sign/esp-idf/components/xtensa/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/driver/include -I/home/danahern/code/dnd_sign/esp-idf/components/driver/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_pm/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_ringbuf/include -I/home/danahern/code/dnd_sign/esp-idf/components/efuse/include -I/home/danahern/code/dnd_sign/esp-idf/components/efuse/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/vfs/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_wifi/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_event/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_netif/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_eth/include -I/home/danahern/code/dnd_sign/esp-idf/components/tcpip_adapter/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_phy/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_phy/esp32/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_ipc/include -I/home/danahern/code/dnd_sign/esp-idf/components/app_trace/include -I/home/danahern/code/dnd_sign/esp-idf/components/esp_timer/include 

