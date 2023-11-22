#ifndef  __PORT_I2C_H_
#define  __PORT_I2C_H_

#include <stdio.h>
#include "driver/i2c.h"
#include "driver/gpio.h"


#define I2C_MASTER_SCL_IO           (1ULL << 16)               /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           (1ULL << 17)               /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000



/**
 * @brief Read a sequence of bytes
 */
esp_err_t i2c_register_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, size_t len);
/**
 * @brief Write a byte 
 */
esp_err_t i2c_register_write_one_byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);

/**
 * @brief Write bytes 
 */
esp_err_t i2c_register_write_bytes(uint8_t slave_addr, uint8_t *data, size_t size);

/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void);

#endif 
