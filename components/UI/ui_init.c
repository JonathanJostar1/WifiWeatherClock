#include "ui_init.h"
#include "port_spi.h"
#include "u8g2.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "port_delay.h"
#include "port_gpio.h"
#include "esp_log.h"
#include "tft_demo.h"

const static char *TAG = "ui_init";

u8g2_t st7735_u8g2_handle;

uint8_t gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
    {
        ESP_LOGW(TAG, "U8X8_MSG_GPIO_AND_DELAY_INIT");
        gpio_output_pulldown_init(ST7735_DC_PIN);
        gpio_output_pulldown_init(ST7735_RST_PIN);
        // gpio_output_pulldown_init(ST7735_CS_PIN);
    }
    break;

    case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
        delay_us(arg_int * 10);
        break;

    case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
        delay_ms(arg_int);     // 在这里既然使用了freertos的vTaskDelay，那么u8g2必须在进程上下文运行
        break;
    default:
        return 0;
    }
    return 1;
}

uint8_t u8x8_byte_spi_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */

    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND:
        spi_send_data(lcd_spi, (uint8_t *)arg_ptr, arg_int);
        break;
    case U8X8_MSG_BYTE_SET_DC:
        gpio_pin_set_level(ST7735_DC_PIN, arg_int);
        break;
    case U8X8_MSG_BYTE_START_TRANSFER:
        // gpio_pin_set_level(ST7735_CS_PIN, 0);
        break;
    case U8X8_MSG_BYTE_END_TRANSFER:
        // gpio_pin_set_level(ST7735_CS_PIN, 1);
        break;
    default:
        return 0;
    }
    return 1;
}

void st7735_reset(void)
{
    gpio_pin_set_level(ST7735_RST_PIN, 1);
    vTaskDelay(5 / portTICK_PERIOD_MS);

    gpio_pin_set_level(ST7735_RST_PIN, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    gpio_pin_set_level(ST7735_RST_PIN, 1);
}

void st7735_u8g2_init(void)
{
    u8g2_Setup_st7571_128x128_f(&st7735_u8g2_handle, U8G2_R0, u8x8_byte_spi_cb, gpio_and_delay_cb); // 初始化 u8g2 结构体
    u8g2_InitDisplay(&st7735_u8g2_handle);                                                          // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
    u8g2_SetPowerSave(&st7735_u8g2_handle, 0);                                                      // 打开显示器
    u8g2_ClearBuffer(&st7735_u8g2_handle);
    ESP_LOGW("ui_init", "u8g2 init done");
}

void draw_font(void)
{
    u8g2_t *u8g2 = &st7735_u8g2_handle;
    u8g2_ClearBuffer(u8g2);
    u8g2_SetFontMode(u8g2, 1);              /*字体模式选择*/
    u8g2_SetFontDirection(u8g2, 0);         /*字体方向选择*/
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf); /*字库选择*/
    u8g2_DrawStr(u8g2, 0, 20, "U");

    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(u8g2, 21, 8, "8");

    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 51, 30, "g");
    u8g2_DrawStr(u8g2, 67, 30, "\xb2");

    u8g2_DrawHLine(u8g2, 2, 35, 47);
    u8g2_DrawHLine(u8g2, 3, 36, 47);
    u8g2_DrawVLine(u8g2, 45, 32, 12);
    u8g2_DrawVLine(u8g2, 46, 33, 12);

    u8g2_SetFont(u8g2, u8g2_font_5x7_tr);
    u8g2_DrawStr(u8g2, 1, 54, "github.com/olikraus/u8g2");
    u8g2_SendBuffer(u8g2);
}

void draw_box(void)
{
    u8g2_t *u8g2 = &st7735_u8g2_handle;
    u8g2_ClearBuffer(u8g2);
    u8g2_DrawBox(u8g2, 3, 7, 25, 15);
    u8g2_SendBuffer(u8g2);
}

void testDrawPixelToFillScreen(void)
{
    u8g2_t *u8g2 = &st7735_u8g2_handle;
    u8g2_ClearBuffer(u8g2);

    u8g2_DrawPixel(u8g2, 0, 1);

    u8g2_SendBuffer(u8g2);
}

void ui_init(void)
{
    // tft_test_demo();
    spi_master_init();
    st7735_reset();
    st7735_u8g2_init();

    // draw(&st7735_u8g2_handle);

    // u8g2_SetFont(&st7735_u8g2_handle, u8g2_font_6x12_mr); // 设置英文字体
    // u8g2_DrawStr(&st7735_u8g2_handle, 0, 30, "hello world");
    // u8g2_SendBuffer(&st7735_u8g2_handle);		// 一定要发送buffer
}