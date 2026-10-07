
# FORCE DISABLE OPC UA - Must be before any add_subdirectory
set(FORTE_COM_OPC_UA OFF CACHE BOOL "" FORCE)


# 1. ESTA DEVE SER A PRIMEIRA LINHA DO ARQUIVO
cmake_minimum_required(VERSION 3.10)

# 2. RESOLVE OS WARNINGS DE POLÍTICA (Fim dos erros CMP)
cmake_policy(SET CMP0000 NEW)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0079 NEW)

# 3. ESTA DEVE SER A SEGUNDA INSTRUÇÃO
project(FORTE LANGUAGES C CXX)

# 4. CONFIGURAÇÃO DO LINKER PARA ESP32 (Linkagem Estática)
 set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE "LINKER:--whole-archive" "<LINK_ITEM>" "LINKER:--no-whole-archive")
 set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED TRUE)


set(FORTE_ARCHITECTURE "FreeRTOSLwIP" CACHE STRING "" FORCE)

add_definitions(-DCONFIG_IDF_TARGET_ESP32=1)
add_definitions(-DSET_FORTE_ARCHITECTURE=ON)

# 6. SEUS INCLUDES (Ajustado com o caminho da sua foto)
include_directories(BEFORE
    
    "C:/esp/projects/4diac-forte/core/arch/freeRTOS/include" 

    "C:/esp/projects/4diac-forte/dependencies/open62541/build"

    "C:/esp/projects/4diac-forte/dependencies/paho.mqtt.c/src"

    "C:/esp/v5.5.4/esp-idf/components/lwip/lwip/src/include/compat/posix"

    "C:/esp/v5.5.4/esp-idf/components/esp_rom/include"
    "C:/esp/v5.5.4/esp-idf/components/heap/include"
    "C:/esp/v5.5.4/esp-idf/components/soc/esp32/register"
    "C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos"

    "C:/esp/v5.5.4/esp-idf/components/xtensa/include"
    "C:/esp/v5.5.4/esp-idf/components/xtensa/esp32/include"

    # ESTAS DUAS LINHAS RESOLVEM O ERRO DO LWIPOPTS.H
    "C:/esp/v5.5.4/esp-idf/components/lwip/include/apps"
    "C:/esp/v5.5.4/esp-idf/components/lwip/port/include"

    "C:/esp/projects/hello_world/build/config"
    "C:/esp/v5.5.4/esp-idf/components/freertos/config/include"
    "C:/esp/v5.5.4/esp-idf/components/freertos/config/include/freertos"
    "C:/esp/v5.5.4/esp-idf/components/freertos/config/xtensa/include"


    # ESTE É O CAMINHO EXATO DA SUA IMAGEM (Até a pasta 'include')
    "C:/esp/v5.5.4/esp-idf/components/lwip/lwip/contrib/ports/win32/include"
    
    # Onde o script acha o sockets.h (Caminho da primeira foto)
    "C:/esp/v5.5.4/esp-idf/components/lwip/lwip/src/include"
    
    # Outros caminhos essenciais para o ESP32 não dar erro depois
    "C:/esp/v5.5.4/esp-idf/components/lwip/port/freertos/include"
    "C:/esp/v5.5.4/esp-idf/components/lwip/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_common/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_hw_support/include"
    "C:/esp/v5.5.4/esp-idf/components/soc/include"
    "C:/esp/v5.5.4/esp-idf/components/soc/esp32/include"
    "C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/include"
    "C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include"
    "C:/esp/v5.5.4/esp-idf/components/esp_system/include"
    "C:/esp/v5.5.4/esp-idf/components/hal/include"
    "C:/esp/v5.5.4/esp-idf/components/newlib/platform_include"
)

# ... (Continuação da Seção 6 com os Includes)

# 5. CONFIGURAÇÕES DE REDE E HARDWARE (Adicione aqui)

# 5. DEFINIÇÕES DE PRÉ-PROCESSADOR (Hardware e Tempo)
add_definitions(-D_GNU_SOURCE)
add_definitions(-D_POSIX_TIMERS)
add_definitions(-Dtimegm=mktime)

# Isso garante que o forte-core saiba como falar com o ESP32
add_definitions(-DLWIP_IPV4=1)
add_definitions(-DCONFIG_LWIP_TCP_OVERSIZE_MSS=1)
add_definitions(-DCONFIG_LWIP_IPV4=1)
add_definitions(-DCONFIG_IDF_TARGET_ESP32=1)
add_definitions(-DCONFIG_LWIP_DHCP_COARSE_TIMER_SECS=60)

# 7. CRIAÇÃO DOS ALVOS (Sempre DEPOIS das definições acima)
set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "" FORCE)
# 7. CRIAÇÃO DOS ALVOS
set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "" FORCE)

# REATIVE ESTA LINHA (Ela é o 'tronco' que evita os erros de 'non-existent target')
add_library(forte STATIC "")
# Ela diz: "Esqueça qualquer linkagem que tentaram empurrar para o alvo forte"
set_target_properties(forte PROPERTIES LINK_LIBRARIES "")

# 5. DEFINIÇÕES PARA EVITAR RECOMPILAÇÃO DE REDE
add_definitions(-DLWIP_COMPAT_SOCKETS=0)
add_definitions(-DLWIP_POSIX_SOCKETS_IO_NAMES=0)
add_definitions(-DLWIP_INTERNAL_ERRNO)

# Isso aqui impede a redefinição da struct ip_mreq
add_definitions(-D_IP_MREQ_TYPE_DEFINED)

# 8. SUBDIRETÓRIOS (Inicia a compilação real)
add_subdirectory(core)
add_subdirectory(stdfblib)
add_subdirectory(com)
add_subdirectory(modules)