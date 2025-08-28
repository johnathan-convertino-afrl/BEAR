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

#ifndef __SPI_DRV_H
#define __SPI_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "spi_map.h"

/*********************************************//**
  * @brief Initializes spi structure and device
  * to defaults, no IRQ, clear all fifos.
  *
  * @param memory_address is the starting memory_address
  * of the uart on the system bus.
  *
  * @return s_spi is a struct with a pointer to the
  * device memory address
  *************************************************/
struct s_spi *initSpi(uint32_t memory_address);

/*********************************************//**
  * @brief Read spi rx data
  *
  * @param p_spi pre-initialized struct from initSpi
  *
  * @return 8 bit uint with data.
  *************************************************/
uint8_t getSpiData(struct s_spi *p_spi);

/*********************************************//**
  * @brief Write spi tx data
  *
  * @param p_spi pre-initialized struct from initSPI
  * @param data 8 bit uint to write to spi device
  *************************************************/
void setSpiData(struct s_spi *p_spi, uint8_t data);

/*********************************************//**
  * @brief Ready for read?
  *
  * @param p_spi pre-initialized struct from initSpi
  *
  * @return True, read is ready, false it is not (1 = true, 0 = false).
  *************************************************/
uint8_t getSpiReadReady(struct s_spi *p_spi);

/*********************************************//**
  * @brief Ready for a write?
  *
  * @param p_spi pre-initialized struct from initSPI
  *
  * @return True, write is ready, false it is not (1 = true, 0 = false).
  *************************************************/
uint8_t getSpiWriteReady(struct s_spi *p_spi);

/*********************************************//**
  * @brief Not active to transmit when 1 (no more data to transmit).
  *
  * @param p_spi pre-initialized struct from initSPI
  *
  * @return False, transmit is running, True it is not (1 = true, 0 = false).
  *************************************************/
uint8_t getSpiTransmitNotActive(struct s_spi *p_spi);

/*********************************************//**
  * @brief Internal fifo enabled if 1
  *
  * @param p_spi pre-initialized struct from initSPI
  *
  * @return True if fifo enabled, false if not (1 = true, 0 = false)
  *************************************************/
uint8_t getSpiFifoEnabled(struct s_spi *p_spi);

/*********************************************//**
  * @brief Receive Fifo is being reset
  *
  * @param p_spi pre-initialized struct from initSPI
  *
  * @return True if in reset, false if not (1 = true, 0 = false).
  *************************************************/
uint8_t getSpiReceiveFifoResetEnabled(struct s_spi *p_spi);

/*********************************************//**
  * @brief Transmit Fifo is being reset
  *
  * @param p_spi pre-initialized struct from initSPI
  *
  * @return True if in reset, false if not (1 = true, 0 = false).
  *************************************************/
uint8_t getSpiTransmitFifoResetEnabled(struct s_spi *p_spi);

/*********************************************//**
  * @brief set chip select
  * 
  * @param p_spi pre initialized struct from initSpi
  * @param num number of select device to set active during communication (0 is the first device select).
  *************************************************/
void setSpiChipSelect(struct s_spi *p_spi, uint8_t num);

/*********************************************//**
  * @brief manually clear chip select
  * 
  * @param p_spi pre initialized struct from initSpi
  * @param num number of select device to set inactive during communication (0 is first device select).
  *************************************************/
void clrSpiChipSelect(struct s_spi *p_spi, uint8_t num);

/*********************************************//**
  * @brief manually set all chip select to active (low)
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiForceSelect(struct s_spi *p_spi);

/*********************************************//**
  * @brief manually clear set all chip select to active (low)
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void clrSpiForceSelect(struct s_spi *p_spi);

/*********************************************//**
  * @brief set clock frequency, does nothing at the moment.
  * 
  * @param p_spi pre initialized struct from initSpi
  * @param freq frequency in hertz
  *************************************************/
void setSpiClockFreq(struct s_spi *p_spi, uint32_t freq);

/*********************************************//**
  * @brief reset tx fifo
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiResetTXfifo(struct s_spi *p_spi);

/*********************************************//**
  * @brief reset rx fifo
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiResetRXfifo(struct s_spi *p_spi);

/*********************************************//**
  * @brief block rx fifo
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiBlockRXfifo(struct s_spi *p_spi);

/*********************************************//**
  * @brief unblock rx fifo
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void unsetSpiBlockRXfifo(struct s_spi *p_spi);

/*********************************************//**
  * @brief set mode for CPHA/CPOL, does nothing at the moment.
  * 
  * @param p_spi pre initialized struct from initSpi
  * @param cpha cpha value of 0 or 1, anything else will result in a value of 0.
  * @param cpol cpol value of 0 or 1, anything else will result in a value of 0.
  *************************************************/
void setSpiMode(struct s_spi *p_spi, uint8_t cpha, uint8_t cpol);

/*********************************************//**
  * @brief set rx data available(ready, status bit will match) interrupt.
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiIrqRxEna(struct s_spi *p_spi);

/*********************************************//**
  * @brief unset rx data available(ready, status bit will match) interrupt (disable).
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void unsetSpiIrqRxEna(struct s_spi *p_spi);

/*********************************************//**
  * @brief set tx data available(ready, status bit will match) interrupt.
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void setSpiIrqTxEna(struct s_spi *p_spi);

/*********************************************//**
  * @brief unset tx data available(ready, status bit will match) interrupt (disable).
  * 
  * @param p_spi pre initialized struct from initSpi
  *************************************************/
void unsetSpiIrqTxEna(struct s_spi *p_spi);

#ifdef __cplusplus
}
#endif

#endif


