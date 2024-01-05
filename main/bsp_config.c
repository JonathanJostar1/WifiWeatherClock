#include "port_i2c.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "esp_vfs_eventfd.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "nvs.h"

const static char *TAG = "bsp_config";

int bsp_system_init(void)
{
    int ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        ESP_LOGW(TAG, "nvs_flash_init failed, try to nvs_flash_erase");
        ret = nvs_flash_erase();
        if(ret == ESP_OK) {
            nvs_flash_init();
        }
        else {
            ESP_LOGW(TAG, "nvs_flash_erase failed");
        }
    }
    else if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "nvs_flash_init failed[%d]", ret);
    }

    ret = esp_event_loop_create_default();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_event_loop_create_default failed[%d]", ret);
        return -2;
    }
    ESP_LOGI(TAG, "bsp_system_init finish");

    return 0;
}


void bsp_config(void)
{
    int ret = bsp_system_init();
    if(ret < 0)
    {
        ESP_LOGI(TAG, "bsp_system_init failed");
    }
}