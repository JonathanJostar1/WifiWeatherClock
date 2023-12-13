#ifndef  __PORT_SPI_H_
#define  __PORT_SPI_H_

#include "driver/spi_master.h"
#include "driver/gpio.h"


#define SPI_HOST_USE                SPI2_HOST
#define GPIO_PIN_NUM_CLK            GPIO_NUM_16
#define GPIO_PIN_NUM_MOSI           GPIO_NUM_17
#define GPIO_PIN_NUM_MISO           -1
#define GPIO_PIN_NUM_CS             GPIO_NUM_18

#define SPI_MASTER_CLK_FREQ         1*1000*1000

extern spi_device_handle_t lcd_spi;        // spi发送句柄

/* spi初始化 */
void spi_master_init(void);

/* spi发送 */
void spi_send_data(spi_device_handle_t spi, const uint8_t *data, int len);

#endif // __PORT_SPI_H_
