set(network_srcs "net_task.c" "blufi_init.c" "blufi_security.c")

idf_component_register(SRCS "${network_srcs}"
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "bt" "nvs_flash" "mbedtls"
                       REQUIRES "")
