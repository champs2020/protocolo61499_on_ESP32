idf_component_register(
    SRCS "forte_main.cpp"
    INCLUDE_DIRS "."
    REQUIRES opcua_server
)

# Força o linker a reter todos os símbolos da biblioteca estática
target_link_libraries(${COMPONENT_LIB} PRIVATE
    -Wl,--whole-archive
    "${CMAKE_CURRENT_LIST_DIR}/libforte-static.a"
    -Wl,--no-whole-archive
)
target_link_libraries(${COMPONENT_LIB} PRIVATE idf::opcua_server)

# Adiciona globalmente a flag de saltos longos para evitar o erro de relocation no Xtensa
target_compile_options(${COMPONENT_LIB} PRIVATE -mlongcalls)
add_compile_options(-mlongcalls)