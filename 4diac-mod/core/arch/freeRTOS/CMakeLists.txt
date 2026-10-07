# 1. Lista de Includes do ESP-IDF v5.5
set(FORTE_FreeRTOSLwIP_INCLUDES 
    "C:/esp/projects/hello_world/build/config"
    "C:/esp/projects/hello_world/main"
    "C:/esp/v5.5.4/esp-idf/components/lwip/port/freertos/include"
    "C:/esp/v5.5.4/esp-idf/components/lwip/port/include"
    "C:/esp/v5.5.4/esp-idf/components/lwip/lwip/src/include"
    "C:/esp/v5.5.4/esp-idf/components/lwip/include"
    "C:/esp/v5.5.4/esp-idf/components/xtensa/esp32/include"
    "C:/esp/v5.5.4/esp-idf/components/xtensa/include"
    "C:/esp/v5.5.4/esp-idf/components/freertos/config/xtensa/include/freertos"
    "C:/esp/v5.5.4/esp-idf/components/freertos/config/include/freertos"
    "C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos"
    "C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/include"
    "C:/esp/v5.5.4/esp-idf/components/freertos/esp_additions/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_hw_support/include"
    "C:/esp/v5.5.4/esp-idf/components/soc/include"
    "C:/esp/v5.5.4/esp-idf/components/soc/esp32/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_system/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_common/include"
    "C:/esp/v5.5.4/esp-idf/components/hal/include"
    "C:/esp/v5.5.4/esp-idf/components/newlib/platform_include"
) # Espaço garantido aqui para evitar o Syntax Warning

# 2. Definições de Compilação (Unificadas)
add_definitions(-DLWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS)
add_definitions(-DLWIP_COMPAT_SOCKETS=0)
add_definitions(-DLWIP_POSIX_SOCKETS_IO_NAMES=0)
add_definitions(-DCONFIG_FREERTOS_UNICORE=0)
add_definitions(-DCONFIG_FREERTOS_HZ=100)
add_definitions(-DCONFIG_IDF_TARGET_ARCH_XTENSA=1)
add_definitions(-DCONFIG_IDF_TARGET_ESP32=1)
add_definitions(-DFORTE_ARCHITECTURE_FreeRTOSLwIP)