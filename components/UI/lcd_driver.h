#ifndef __LCD_DRIVER_H_
#define __LCD_DRIVER_H_

#include "port_gpio.h"
#include <stdint.h>

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

#define ST7735_DC_PIN      GPIO_NUM_5
#define ST7735_CS_PIN      GPIO_NUM_18
#define ST7735_RST_PIN     GPIO_NUM_4
#define ST7735_BLK_PIN     GPIO_NUM_19

#define X_MAX_PIXEL	       128
#define Y_MAX_PIXEL	       128

//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	gpio_pin_set_level(ST7735_CS_PIN, 1); 
#define	LCD_DC_SET  	gpio_pin_set_level(ST7735_DC_PIN, 1);        
#define	LCD_RST_SET  	gpio_pin_set_level(ST7735_RST_PIN, 1);     
#define	LCD_BLK_SET  	gpio_pin_set_level(ST7735_BLK_PIN, 1);

//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	gpio_pin_set_level(ST7735_CS_PIN, 0);  
#define	LCD_DC_CLR  	gpio_pin_set_level(ST7735_DC_PIN, 0);     
#define	LCD_RST_CLR  	gpio_pin_set_level(ST7735_RST_PIN, 0);    
#define	LCD_BLK_CLR  	gpio_pin_set_level(ST7735_BLK_PIN, 0); 


void Lcd_Reset(void);
void lcd_init(void);
void Lcd_Clear(uint16_t Color);
void LCD_WriteData_16Bit(uint16_t Data);
void Lcd_SetXY(uint16_t x, uint16_t y);
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data);
void Lcd_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);

#endif