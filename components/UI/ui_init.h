#ifndef  __UI_INIT_H_
#define  __UI_INIT_H_

#include <stdio.h>
#include "driver/gpio.h"

#define ST7735_DC_PIN      GPIO_NUM_5
#define ST7735_CS_PIN      GPIO_NUM_18
#define ST7735_RST_PIN     GPIO_NUM_4
#define ST7735_BLK_PIN     GPIO_NUM_19

void ui_init(void);

void draw_font(void);

void draw_box(void);

void testDrawPixelToFillScreen(void);

#endif 