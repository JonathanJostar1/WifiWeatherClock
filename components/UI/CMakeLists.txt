file(GLOB_RECURSE SOURCE UI/*.c)

idf_component_register(SRCS ${SOURCE}
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "Hardware" "Network" "U8g2")
