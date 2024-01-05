file(GLOB_RECURSE SOURCE Network/*.c)

idf_component_register(SRCS ${SOURCE}
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "bt" "nvs_flash" "mbedtls" "lwip"
                       REQUIRES "Hardware")
