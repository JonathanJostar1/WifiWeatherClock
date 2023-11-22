set(GLOB_RECURSE SOURCE "net_task.c" "blufi_init.c" "blufi_security.c" "blufi_connect.c")

idf_component_register(SRCS "${SOURCE}"
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "bt" "nvs_flash" "mbedtls"
                       REQUIRES "Hardware")
