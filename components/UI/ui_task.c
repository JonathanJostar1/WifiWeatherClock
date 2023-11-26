#include "ui_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ui_init.h"

void ui_task(void *arg)
{
    ui_init();
    while (1)
    {
        vTaskDelay(1000);
    }
}


