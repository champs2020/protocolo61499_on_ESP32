# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# Mantém apenas os componentes necessários e evita o conflito com a raiz externa
set(EXTRA_COMPONENT_DIRS
    components/forte_main
    components/open62541lib
    components/model
    components/opcua_server
)

# Adiciona globalmente a flag de saltos longos para o Xtensa resolver os desvios da biblioteca estática
add_compile_options(-mlongcalls)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp_forte_opca-ua_server)

 

 
 