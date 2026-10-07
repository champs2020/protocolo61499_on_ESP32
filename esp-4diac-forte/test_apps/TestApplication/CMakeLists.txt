# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# Mantém apenas o diretório do componente forte_main, eliminando o conflito com a raiz externa
set(EXTRA_COMPONENT_DIRS components/forte_main)

# Adiciona globalmente a flag de saltos longos para o Xtensa resolver os desvios da biblioteca estática
add_compile_options(-mlongcalls)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(TestApplication)

 

 
 