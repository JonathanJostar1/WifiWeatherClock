#include "port_delay.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define CPU_FREQUENCY_MAX       240*1000*1000
#define CPU_FREQUENCY_DEFAULT   160*1000*1000
#define CPU_FREQUENCY_MIN       80*1000*1000

static int cpu_clk = 0;     // 160M

static __inline void delay_clock(int ts)
{
    uint32_t start, curr;
 
    __asm__ __volatile__("rsr %0, ccount" : "=r"(start));
    do
    {
        __asm__ __volatile__("rsr %0, ccount" : "=r"(curr));

    }while (curr - start <= ts);
}

void delay_ns(int ns)
{
    delay_clock(ns * cpu_clk / 100000); //CPU_Freq=160MHz
}
 
void delay_us(int us)
{
    delay_clock(us * cpu_clk / 1000000); //CPU_Freq=160MHz
}
 
void delay_ms(int ms)
{
    delay_clock(ms * cpu_clk / 1000); //CPU_Freq=160MHz
}

void delay_init(void)
{
    cpu_clk = CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ;
    if (cpu_clk != CPU_FREQUENCY_MAX ||
       cpu_clk != CPU_FREQUENCY_DEFAULT ||
       cpu_clk != CPU_FREQUENCY_MIN)
    {
        cpu_clk = CPU_FREQUENCY_DEFAULT;
    }

}

uint32_t systemtick_get(void)
{
    return esp_log_timestamp();
}

