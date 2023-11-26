#include "ui_init.h"
#include "port_i2c.h"
#include "u8g2.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "port_delay.h"
#include "port_gpio.h"
#include "esp_log.h"

u8g2_t st7735_u8g2_handle;

uint8_t gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
        {
            gpio_output_pulldown_init(ST7735_DC_PIN);
            ESP_LOGW("ui_init", "ST7735_DC_PIN init done");

            gpio_output_pulldown_init(ST7735_RST_PIN);
            ESP_LOGW("ui_init", "ST7735_RST_PIN init done");

            gpio_output_pulldown_init(ST7735_CS_PIN);
            ESP_LOGW("ui_init", "ST7735_CS_PIN init done");

            gpio_output_pulldown_init(ST7735_BLK_PIN);
            ESP_LOGW("ui_init", "ST7735_BLK_PIN init done");
        }
        break;

        case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
            delay_ns(arg_int);
            break;

        case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            delay_us(arg_int * 10);
            break;

        case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
            vTaskDelay(pdMS_TO_TICKS(arg_int)); //在这里既然使用了freertos的vTaskDelay，那么u8g2必须在进程上下文运行
            break;

        case U8X8_MSG_GPIO_DC:
            gpio_pin_set_level(ST7735_DC_PIN, arg_int);
            break;

        case U8X8_MSG_GPIO_RESET:
            gpio_pin_set_level(ST7735_RST_PIN, arg_int);
            break;

        case U8X8_MSG_GPIO_CS:
            gpio_pin_set_level(ST7735_CS_PIN, arg_int);
            break;

        default:
            return 0; 
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
        i2c_register_write_bytes(u8x8_GetI2CAddress(u8x8), buffer, buf_idx);
        break;
    default:
        return 0;
    }
    return 1;
}

void ui_init(void)
{

    i2c_master_init();

    u8g2_Setup_st7571_i2c_128x128_f(&st7735_u8g2_handle, U8G2_R0, u8x8_byte_i2c_cb, gpio_and_delay_cb);  // 初始化 u8g2 结构体

    u8g2_InitDisplay(&st7735_u8g2_handle); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
    u8g2_SetPowerSave(&st7735_u8g2_handle, 0); // 打开显示器
    u8g2_ClearBuffer(&st7735_u8g2_handle);

    gpio_pin_set_level(ST7735_BLK_PIN, 1);
    ESP_LOGW("ui_init", "u8g2 init done");

    u8g2_SetFont(&st7735_u8g2_handle, u8g2_font_6x12_mr); // 设置英文字体
    u8g2_DrawStr(&st7735_u8g2_handle, 0, 30, "hello world");
    u8g2_SendBuffer(&st7735_u8g2_handle);		// 一定要发送buffer
}