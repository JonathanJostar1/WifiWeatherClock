#ifndef __PORT_DELAY_H_
#define __PORT_DELAY_H_

#include <stdint.h>

#define delay_ms port_delay_ms
#define delay_us port_delay_us
#define system_tick port_get_systick

/* 毫秒延时 */
void port_delay_ms(uint32_t ms);

/* 微秒延时 */
void port_delay_us(uint32_t us);

/* 获取系统节拍，每1ms加1 */
uint64_t port_get_systick(void);

uint32_t system_log_timestamp_get(void);


#endif 