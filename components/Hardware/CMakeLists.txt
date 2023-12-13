file(GLOB_RECURSE SOURCE Hardware/*.c)

idf_component_register(SRCS ${SOURCE}
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "esp_hw_support" "newlib")
