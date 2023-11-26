#ifndef __PORT_GPIO_H_
#define __PORT_GPIO_H_

#include <stdint.h>
#include "driver/gpio.h"

/* 初始化上拉输出 */
void gpio_output_pullup_init(gpio_num_t gpio_pin);

/* 初始化下拉输出 */
void gpio_output_pulldown_init(gpio_num_t gpio_pin);

/* 设置输出电平 */
void gpio_pin_set_level(gpio_num_t gpio_pin, uint8_t level);

/* 电平翻转 */
void gpio_pin_level_toggle(gpio_num_t gpio_pin, uint8_t level);

#endif //__PORT_GPIO_H_