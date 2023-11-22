# components组件编译时会被自动构建(依据idf_component_register包含的头文件)

file(GLOB_RECURSE SOURCES Hardware/*.c Network/*.c UI/*.c U8g2/*.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "U8g2/" "Hardware/" "Network/" "UI/"
                       REQUIRES "driver" "bt" "nvs_flash" "mbedtls") 