#ifndef __PORT_DELAY_H_
#define __PORT_DELAY_H_

#include <stdint.h>

/* ns级延时 */
void delay_ns(int ns);

/* us级延时 */
void delay_us(int us);

/* ms级延时 */
void delay_ms(int ms);

/* delay初始化 */
void delay_init(void);

/* 获取系统运行时间 */
uint32_t systemtick_get(void);

#endif 