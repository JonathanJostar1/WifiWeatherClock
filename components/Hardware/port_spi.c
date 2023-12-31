#include "port_spi.h"
#include <string.h>
#include "esp_log.h"

const static char *TAG = "port_spi";
spi_device_handle_t lcd_spi;        // spi发送句柄

/* spi发送 */
void spi_send_data(spi_device_handle_t spi, const uint8_t *data, int len)
{
    esp_err_t ret;
    spi_transaction_t t;
    if (len == 0) {
        return;    //no need to send anything
    }
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length = len * 8;             //Len is in bytes, transaction length is in bits.
    t.tx_buffer = data;             //Data
    t.user = (void*)1;              //D/C needs to be set to 1
    ret = spi_device_polling_transmit(spi, &t); //Transmit!
    if(ret != ESP_OK)
    {
        //Should have had no issues.
        ESP_LOGE(TAG, "spi_device_polling_transmit fail");
    }          
}

/* spi初始化 */
void spi_master_init(void)
{
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = GPIO_PIN_NUM_MISO,
        .mosi_io_num = GPIO_PIN_NUM_MOSI,
        .sclk_io_num = GPIO_PIN_NUM_CLK,
        .quadwp_io_num      = -1,
        .quadhd_io_num      = -1,
        .max_transfer_sz = 4096,
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = SPI_MASTER_CLK_FREQ,  //Clock out at 10 MHz
        .mode = 0,                              //SPI mode 0
        .spics_io_num = GPIO_PIN_NUM_CS,        //CS pin
        .queue_size = 7,                        //We want to be able to queue 7 transactions at a time
    };

    //Initialize the SPI bus
    ret = spi_bus_initialize(SPI_HOST_USE, &buscfg, SPI_DMA_CH_AUTO);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "spi_bus_initialize fail");
    }
    ret = spi_bus_add_device(SPI_HOST_USE, &devcfg, &lcd_spi);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "spi_bus_add_device fail");
    }
}