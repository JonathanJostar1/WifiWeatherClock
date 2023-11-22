#include "ui_init.h"
#include "port_i2c.h"
#include "u8g2.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

typedef uint8_t (*u8x8_msg_cb)(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


uint8_t gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
        oled_gpio_init();
        break;
    case U8X8_MSG_GPIO_SPI_DATA:
        gpio_set_level(OLED_SDA, arg_int);
        break;
    case U8X8_MSG_GPIO_SPI_CLOCK:
        gpio_set_level(OLED_SCK, arg_int);
        break;
    case U8X8_MSG_GPIO_CS: // CS默认接地
        break;
    case U8X8_MSG_GPIO_DC:
        gpio_set_level(OLED_DC, arg_int);
        break;
    case U8X8_MSG_GPIO_RESET:
        gpio_set_level(OLED_RST, arg_int);
        break;
    case U8X8_MSG_DELAY_MILLI:
        vTaskDelay(arg_int / portTICK_PERIOD_MS); // 1000hz
        break;
    default:
        return 0; // A message was received which is not implemented, return 0 to indicate an error
    }
    return 1;
}

uint8_t u8x8_byte_i2c_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
    static uint8_t buffer[32]; 
    static uint8_t buf_idx;
    uint8_t *data;

    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND:
        data = (uint8_t *)arg_ptr;
        while (arg_int > 0)
        {
            buffer[buf_idx++] = *data;
            data++;
            arg_int--;
        }
        break;
    case U8X8_MSG_BYTE_INIT:
        /* add your custom code to init i2c subsystem */
        break;
    case U8X8_MSG_BYTE_SET_DC:
        /* ignored for i2c */
        break;
    case U8X8_MSG_BYTE_START_TRANSFER:
        buf_idx = 0;
        break;
    case U8X8_MSG_BYTE_END_TRANSFER:
        esp32_i2c_write(u8x8_GetI2CAddress(u8x8), buf_idx, buffer);
        break;
    default:
        return 0;
    }
    return 1;
}

void ui_init(void)
{

    
}