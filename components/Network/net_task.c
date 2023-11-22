#include "net_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "blufi_connect.h"


const static char *TAG = "net_task";

void net_task(void *arg)
{
    int ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        nvs_flash_erase();
        ret = nvs_flash_init();
    }

    ret = blufi_init();
    if(ret < 0)
    {
        ESP_LOGE(TAG, "blufi_init fail[%d]", ret);
    }

    while(1)
    {
        // ESP_LOGI(TAG, "hello net_task");
        vTaskDelay(1000);
    }

}


