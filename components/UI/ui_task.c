#include "ui_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ui_init.h"
#include "lcd_driver.h"
#include "tft_demo.h"

void ui_task(void *arg)
{
    lcd_init();
    while (1)
    {
        tft_test_demo();
        vTaskDelay(1000);
    }
}


