#*******************************************************************************
# Copyright (c) 2010 - 2018 ACIN
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.

# C:\esp\projects\forte_2\src\arch

# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Alois Zoitl, Patrick Smejkal, Martin Melik-Merkumians
# *    - initial API and implementation and/or initial documentation
# *    - added utils directory
# *******************************************************************************/
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(SOURCE_GROUP ${SOURCE_GROUP}\\arch)

# 1. Versão mínima sempre na primeira linha


set(FORTE_ARCHITECTURE "FreeRTOSLwIP" CACHE STRING "Target architecture" FORCE)
set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "Build static library instead of executable" FORCE)


add_subdirectory(be_m1)
add_subdirectory(ecos)
add_subdirectory(freeRTOS)
add_subdirectory(macos)
add_subdirectory(netos)
add_subdirectory(pikeos_posix)
add_subdirectory(plcnext)
add_subdirectory(posix)
add_subdirectory(rcX)
add_subdirectory(vxworks)
add_subdirectory(win32)
add_subdirectory(utils)

# 1. Definições de Compatibilidade (Devem vir ANTES de tudo)
add_definitions(-DLWIP_ESP_LWIP_OPTS=1)
add_definitions(-DCONFIG_LWIP_IPV4=1)
add_definitions(-DLWIP_COMPAT_SOCKETS=1)
add_definitions(-Dlwip_socket=socket)
add_definitions(-Dlwip_setsockopt=setsockopt)

add_definitions(-Dlwip_bind=bind)
add_definitions(-Dlwip_listen=listen)
add_definitions(-Dlwip_accept=accept)
add_definitions(-Dlwip_send=send)
add_definitions(-Dlwip_recv=recv)
add_definitions(-Dlwip_sendto=sendto)
add_definitions(-Dlwip_recvfrom=recvfrom)

set(FORTE_FreeRTOSLwIP_INCLUDES 
    "C:/esp/projects/esp-4diac-forte/test_apps/TestApplication/build/config;C:/esp/v5.5.4/esp-idf/components/lwip/port/esp32xx/include;C:/esp/v5.5.4/esp-idf/components/lwip/port/freertos/include;C:/esp/v5.5.4/esp-idf/components/freertos/config/include;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/include;C:/esp/v5.5.4/esp-idf/components/heap/include;C:/esp/v5.5.4/esp-idf/components/soc/esp32/register;C:/esp/v5.5.4/esp-idf/components/soc/esp32/include;C:/esp/v5.5.4/esp-idf/components/soc/include;C:/esp/v5.5.4/esp-idf/components/hal/include;C:/esp/v5.5.4/esp-idf/components/esp_hw_support/include;C:/esp/v5.5.4/esp-idf/components/esp_common/include;C:/esp/v5.5.4/esp-idf/components/esp_system/include;C:/esp/v5.5.4/esp-idf/components/newlib/platform_include;C:/esp/v5.5.4/esp-idf/components/xtensa/include;C:/esp/v5.5.4/esp-idf/components/xtensa/esp32/include;C:/esp/v5.5.4/esp-idf/components/freertos/config/xtensa/include;C:/esp/v5.5.4/esp-idf/components/lwip/lwip/src/include;C:/esp/v5.5.4/esp-idf/components/lwip/port/include;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos;C:/esp/v5.5.4/esp-idf/components/freertos/esp_additions/include/freertos;C:/esp/v5.5.4/esp-idf/components/freertos/config/include/freertos;C:/esp/v5.5.4/esp-idf/components/esp_rom/include;C:/esp/v5.5.4/esp-idf/components/lwip/port/esp32xx/include;C:/esp/v5.5.4/esp-idf/components/esp_driver_gpio/include;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/include;C:/esp/v5.5.4/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include;C:/esp/v5.5.4/esp-idf/components/freertos/esp_additions/include/freertos;C:/esp/v5.5.4/esp-idf/components/freertos/esp_additions/include"
    CACHE STRING "Caminhos fixos" FORCE
)

# ==============================================================================
# Configurações de Build e Flags do FORTE para ESP32 / FreeRTOS
# ==============================================================================

# 1. Modo de Build (Debug)
set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build" FORCE)

# 2. Configurações da Biblioteca e Runtime FORTE
set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "Build FORTE as executable" FORCE)
set(FORTE_BUILD_STATIC_LIBRARY ON CACHE BOOL "Build FORTE as static library" FORCE)
set(FORTE_TicksPerSecond "100" CACHE STRING "FORTE timer resolution in ticks per second" FORCE)
set(FORTE_LOGLEVEL "LOGDEBUG" CACHE STRING "Log level for FORTE execution" FORCE)

# 3. Flags de Compilação C/C++ Base e suas Variações
set(ESP_EXTRA_FLAGS "-DLWIP_COMPAT_SOCKETS=1 -DLWIP_IGMP=1 -DLWIP_TIMEVAL_PRIVATE=0")

# Flags Base
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the C compiler" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the CXX compiler" FORCE)

# Variação: DEBUG
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the C compiler during DEBUG builds" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the CXX compiler during DEBUG builds" FORCE)

# Variação: RELEASE
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the C compiler during RELEASE builds" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the CXX compiler during RELEASE builds" FORCE)

# Variação: MINSIZEREL
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the C compiler during MINSIZEREL builds" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the CXX compiler during MINSIZEREL builds" FORCE)

# Variação: RELWITHDEBINFO
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the C compiler during RELWITHDEBINFO builds" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG ${ESP_EXTRA_FLAGS}" CACHE STRING "Flags used by the CXX compiler during RELWITHDEBINFO builds" FORCE)

forte_add_sourcefile_hcpp(timerha devlog)

SET(FORTE_LOGGER_BUFFER_SIZE "300" CACHE STRING "Buffer's length of the logger")
mark_as_advanced(FORTE_LOGGER_BUFFER_SIZE)
forte_add_custom_configuration("#define FORTE_LOGGER_BUFFER_SIZE ${FORTE_LOGGER_BUFFER_SIZE}")

