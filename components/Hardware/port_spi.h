#ifndef  __PORT_SPI_H_
#define  __PORT_SPI_H_

#include "driver/spi_master.h"
#include "driver/gpio.h"


#define SPI_HOST_USE                SPI2_HOST
#define GPIO_PIN_NUM_MISO           GPIO_NUM_25
#define GPIO_PIN_NUM_MOSI           GPIO_NUM_23
#define GPIO_PIN_NUM_CLK            GPIO_NUM_19
#define GPIO_PIN_NUM_CS             GPIO_NUM_22
#define PARALLEL_LINES              GPIO_NUM_16

#define SPI_MASTER_CLK_FREQ         1*1000*1000




#endif // __PORT_SPI_H_
