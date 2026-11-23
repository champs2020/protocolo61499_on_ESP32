idf_component_register(
    SRCS "open62541.c"
    INCLUDE_DIRS "."
    REQUIRES freertos lwip
    WHOLE_ARCHIVE
)

target_compile_definitions(${COMPONENT_LIB} PUBLIC UA_ARCHITECTURE_FREERTOSLWIP)
