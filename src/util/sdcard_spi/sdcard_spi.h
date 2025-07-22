/***************************************************************************//**
  * @file     spi.h
  * @brief    Altera AXI SPI driver
  * @details  Baremetal C driver targeting Altera based SPI lite cores.
  *           Written with riscv or arm irq structure in mind.
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

SD_NCR_TIMEOUT/**
 * @struct s_sdcard_spi
 * @brief A struct to store current state of the sdcard spi software protocol
 */
struct s_sdcard_spi
{
  uint8_t cs_num;
  struct s_spi *p_spi;
  enum {READY, INIT_V1, INIT_V2, CMD0_FAIL, CMD8_FAIL, VOLTAGE_RANGE_FAIL, CHECK_PATTERN_FAIL, CMD58_FAIL, UNKNOWN_FAIL, NOT_READY} state; 
};

/*********************************************//**
  * @brief Initializes sdcard over spi device
  * to defaults, this will put it in a state ready for
  * data transfer.
  *
  * @param memory_address is the starting memory_address
  * of the spi device on the system bus.
  * @param cs_num is the number of the sdcard chip select.
  *
  * @return s_sdcard_spi is a struct allocated with some memory.
  *************************************************/
struct s_sdcard_spi *initSdcardSpi(uint32_t memory_address, uint8_t cs_num);

#ifdef __cplusplus
}
#endif

#endif


