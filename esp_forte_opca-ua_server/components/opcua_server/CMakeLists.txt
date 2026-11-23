idf_component_register(
    SRCS "opcua_server.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_system lwip log model open62541lib
    WHOLE_ARCHIVE
)
