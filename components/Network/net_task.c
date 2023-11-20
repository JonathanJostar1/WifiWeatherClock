#include "net_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "blufi_connect.h"


const static char *TAG = "net_task";

void net_task(void *arg)
{
    initialise_wifi();

    blufi_init();
    while(1)
    {
        ESP_LOGI(TAG, "hello net_task");
        vTaskDelay(1000);
    }

}


