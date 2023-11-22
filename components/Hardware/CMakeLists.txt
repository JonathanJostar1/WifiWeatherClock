set(hw_srcs "port_i2c.c")

idf_component_register(SRCS "${hw_srcs}"
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "")
