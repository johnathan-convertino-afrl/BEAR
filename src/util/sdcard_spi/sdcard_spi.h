/***************************************************************************//**
  * @file     sdcard_spi.h
  * @brief    SDCARD R/W over SPI
  * @details  Baremetal SDCARD read/write over SPI. This uses polling for all reads
  *           and writes.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     07/17/2025
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2025 Johnathan Convertino
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
  *****************************************************************************/

#ifndef __SDCARD_SPI_DRV_H
#define __SDCARD_SPI_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @struct s_sdcard_spi
 * @brief A struct to store current state of the sdcard spi software protocol
 */
struct s_sdcard_spi
{
  uint8_t cs_num;
  uint8_t last_r1;
  uint8_t last_error_token;
  uint8_t v1;
  uint8_t hc;

  enum
  {
    READY_HIGH_CAPACITY_V2,
    READY_STANDARD_CAPACITY_V2,
    READY_STANDARD_CAPACITY_V1,
    INIT_V1,
    INIT_V2,
    CMD0_FAIL,
    CMD8_FAIL,
    VOLTAGE_SET_FAIL,
    VOLTAGE_RANGE_FAIL,
    CHECK_PATTERN_FAIL,
    CMD16_FAIL,
    CMD58_FAIL,
    ACMD41_FAIL,
    READ_FAIL,
    WRITE_FAIL,
    UNKNOWN_FAIL,
    NOT_READY
  } state;
  
  struct s_spi *p_spi;
};

/*********************************************//**
  * @brief Initializes sdcard over spi device
  * to defaults, this will put it in a state ready for
  * data transfer.
  *
  * @param p_sdcard_spi is a pre-allocated struct that for
  * the sdcard driver.
  * @param memory_address is the starting memory_address
  * of the spi device on the system bus.
  * @param cs_num is the number of the sdcard chip select.
  * 
  * @return 0 on no error, 1 for an error.
  *************************************************/
uint8_t initSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t memory_address, uint8_t cs_num);

/*********************************************//**
  * @brief Read the sdcard over spi in 512 byte blocks for all standards.
  *
  * @param p_sdcard_spi is struct containing device information from init.
  * @param address start address to read a block, even for v1 (byte size is set to 512).
  * @param p_buffer array of uint8_t (bytes) for the 512 bytes read from the block.
  * 
  * @return 0 on no error, 1 for an error.
  *************************************************/
uint8_t readSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t address, uint8_t *p_buffer);

/*********************************************//**
  * @brief Write the sdcard over spi in 512 byte blocks for all standards.
  *
  * @param p_sdcard_spi is struct containing device information from init.
  * @param address start address to write a block, even for v1 (byte size is set to 512).
  * @param p_buffer array of uint8_t (bytes) for the 512 bytes to write to the block.
  * 
  * @return 0 on no error, 1 for an error
  *************************************************/
uint8_t writeSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t address, uint8_t *p_buffer);

/*********************************************//**
  * @brief Return a string based on the state of the device
  *
  * @param p_sdcard_spi is struct containing device information from init.
  * @return a string message
  *************************************************/
char *getSdcardSpiStateString(struct s_sdcard_spi *p_sdcard_spi);

#ifdef __cplusplus
}
#endif

#endif


