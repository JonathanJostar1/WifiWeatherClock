file(GLOB_RECURSE SOURCE U8g2/*.c)

idf_component_register(SRCS ${SOURCE}
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "")
