#include "port_gpio.h"

/* 初始化上拉输出 */
void gpio_output_pullup_init(gpio_pin_t gpio_pin)
{
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << gpio_pin),
        .pull_down_en = 0,
        .pull_up_en = 1,
    };
    gpio_config(&io_conf);
}

/* 初始化下拉输出 */
void gpio_output_pulldown_init(gpio_pin_t gpio_pin)
{
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << gpio_pin),
        .pull_down_en = 1,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);
}

/* 设置输出电平 */
void gpio_pin_set_level(gpio_pin_t gpio_pin, uint8_t level)
{
    esp_rom_gpio_pad_select_gpio(gpio_pin);
    gpio_set_direction(gpio_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio_pin, level);
}

/* 获取io电平 */
uint8_t gpio_pin_get_level(gpio_pin_t gpio_pin)
{
    return gpio_get_level(gpio_pin);
}

/* 电平翻转 */
void gpio_pin_level_toggle(gpio_pin_t gpio_pin, uint8_t level)
{
    gpio_get_level(gpio_pin) ? gpio_pin_set_level(gpio_pin, 0) : gpio_pin_set_level(gpio_pin, 1);
}