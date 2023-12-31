#include "net_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "blufi_connect.h"


const static char *TAG = "net_task";

void net_task(void *arg)
{
    int ret = blufi_init();
    if(ret < 0)
    {
        ESP_LOGE(TAG, "blufi_init fail[%d]", ret);
    }

    while(1)
    {
        // ESP_LOGI(TAG, "%ld", esp_log_timestamp());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}


