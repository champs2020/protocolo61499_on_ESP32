idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES forte_main opcua_server
    PRIV_REQUIRES spi_flash
)
