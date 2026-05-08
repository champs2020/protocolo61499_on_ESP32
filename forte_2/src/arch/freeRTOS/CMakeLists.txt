#/************************************************************************************
# Copyright (c) 2016 - 2018 fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#  Guru Chandrasekhara - initial API and implementation and/or initial documentation
# * Jose Cabral - Cleaning
# ************************************************************************************/


SET(SOURCE_GROUP ${SOURCE_GROUP}\\freertos)

forte_add_architecture(FreeRTOSLwIP)

if("${FORTE_ARCHITECTURE}" STREQUAL "FreeRTOSLwIP")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})  

  set(FORTE_LOGLEVEL "NOLOG" CACHE STRING "Loglevel to use" FORCE)

# ----------- OLHAR PQ CADA LINHA
# Definição das Flags de Compilação para ESP32
set(MY_ESP32_FLAGS "-mlongcalls -ffunction-sections -fdata-sections -fno-threadsafe-statics -fno-rtti -fno-exceptions -DconfigMINIMAL_STACK_SIZE_FORTE=15000")

# Aplica as flags tanto para C quanto para C++
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)

# Aplica especificamente para as variantes de Build (Debug, Release, etc)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)

set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -Os ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os ${MY_ESP32_FLAGS}" CACHE STRING "" FORCE)
## --- CONFIGURAÇÕES DO FORTE ---

# Define a resolução de ticks (100 ticks por segundo)
set(FORTE_TicksPerSecond "100" CACHE STRING "Resolução de ticks do FORTE" FORCE)

# Desativa a construção do executável padrão
set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "Build FORTE executable" FORCE)

# Ativa a construção como biblioteca estática (libforte.a)
set(FORTE_BUILD_STATIC_LIBRARY ON CACHE BOOL "Build FORTE as static library" FORCE)

# Define o tipo de build para DEBUG
set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Tipo de build" FORCE)

# Define o nível de log para LOGDEBUG (máximo de detalhes)
set(FORTE_LOGLEVEL "LOGDEBUG" CACHE STRING "Nível de detalhamento do log" FORCE)

## ------------------------------
# -------------

  SET(FORTE_FreeRTOSLwIP_LIB_DIR "" CACHE PATH "Only for executable: ABSOLUTE path to FreeRTOSLwIP folder with object library FORTE_FreeRTOSLwIP_LIB")
  SET(FORTE_FreeRTOSLwIP_LIB "" CACHE STRING "Only for executable: FreeRTOSLwIP Library file in FORTE_FreeRTOSLwIP_DIR to be linked to forte")
  
  forte_add_sourcefile_h(fortealloc.h)
  forte_add_sourcefile_hcpp(forte_thread forte_sync freertostiha forte_sem forte_Init)
  forte_add_sourcefile_cpp(forte_architecture.cpp ../genforte_printer.cpp)
  forte_add_sourcefile_cpp(../genforte_realFunctions.cpp ./forte_architecture_time.cpp)
  
  forte_add_to_executable_cpp(main)
  
  forte_add_definition("-DFORTE_LITTLE_ENDIAN")
  
  forte_add_include_system_directories(${FORTE_FreeRTOSLwIP_INCLUDES})
  
  if(FORTE_COM_ETH)
    forte_add_handler(CFDSelectHandler sockhand)
    forte_add_sourcefile_hcpp( ../fdselecthand ../bsdsocketinterf)
    forte_add_sourcefile_h(../gensockhand.h)
    forte_add_sourcefile_h(sockhand.h)

    message("freeRTOS with LwIP arch needs the following flags to be defined (please do it in lwipopts.h):")
    message("#define LWIP_COMPAT_SOCKETS 1")
    message("#define LWIP_IGMP 1 //to use IP_ADD_MEMBERSHIP")
    message("#define LWIP_TIMEVAL_PRIVATE 0 //This is optional. Set this flag if you get a compilation error about redefinition of struct timeval")
  endif(FORTE_COM_ETH)
  
endif()
