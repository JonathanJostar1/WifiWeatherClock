#include <stdlib.h>
#include <unistd.h>
#include "port_delay.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "time.h"
#include "sys/time.h"

/* 毫秒延时 */
void port_delay_ms(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

/* 微秒延时 */
void port_delay_us(uint32_t us)
{
    usleep(us);
}

/* 获取系统节拍，每1ms加1 */
uint64_t port_get_systick(void)
{
    static uint32_t base = 0;
    if (base == 0 && xPortGetCoreID() == 0) {
        base = esp_log_early_timestamp();
    }
    TickType_t tick_count = xPortInIsrContext() ? xTaskGetTickCountFromISR() : xTaskGetTickCount();
    return base + tick_count * (1000 / configTICK_RATE_HZ);
}

uint32_t system_log_timestamp_get(void)
{
    return esp_log_timestamp();
}

