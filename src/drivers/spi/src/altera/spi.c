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

#include <stdlib.h>

#include "spi.h"

// Initializes spi structure and device
struct s_spi *initSpi(uint32_t memory_address)
{
  struct s_spi *p_temp = (struct s_spi *)memory_address;

  p_temp->status.reg  = 0;

  return p_temp;
}

// Read SPI rx data
uint8_t getSpiData(struct s_spi *p_spi)
{
  return (uint8_t)p_spi->rx_data;
}

// Write SPI tx data
void setSpiData(struct s_spi *p_spi, uint8_t data)
{
  p_spi->tx_data = (uint32_t)data;
}


// Ready for read?
uint8_t getSpiReadReady(struct s_spi *p_spi)
{
  return p_spi->status.bits.rrdy;
}

// Ready for a write?
uint8_t getSpiWriteReady(struct s_spi *p_spi)
{
  return p_spi->status.bits.trdy;
}

// Not active when 1 (aka not transmitting).
uint8_t getSpiTransmitNotActive(struct s_spi *p_spi)
{
  return p_spi->status.bits.tmt;
}

// fifo enabled?
uint8_t getSpiFifoEnabled(struct s_spi *p_spi)
{
  return p_spi->status_ext.bits.fifo_ena;
}

// RX reset active
uint8_t getSpiReceiveFifoResetEnabled(struct s_spi *p_spi)
{
  return p_spi->status_ext.bits.rst_rx_act;
}

// TX reset active
uint8_t getSpiTransmitFifoResetEnabled(struct s_spi *p_spi)
{
  return p_spi->status_ext.bits.rst_tx_act;
}

// set chip select
void setSpiChipSelect(struct s_spi *p_spi, uint8_t num)
{
  uint32_t temp = p_spi->slave_select;
  
  temp |= ((uint32_t)1 << num);
  
  p_spi->slave_select = temp;
}

// clear chip select
void clrSpiChipSelect(struct s_spi *p_spi, uint8_t num)
{
  uint32_t temp = p_spi->slave_select;
  
  temp &= ~((uint32_t)1 << num);
  
  p_spi->slave_select = temp;
}

// manually set all chip select to active (low)
void setSpiForceSelect(struct s_spi *p_spi)
{
  p_spi->control.bits.sso = 1;
}

// manually clear set all chip select to active (low)
void clrSpiForceSelect(struct s_spi *p_spi)
{
  p_spi->control.bits.sso = 0;
}

// set clock frequency, does nothing at the moment.
void setSpiClockFreq(struct s_spi *p_spi, uint32_t freq)
{
  p_spi->speed_control_ext = freq;
}

// reset tx fifo
void setSpiResetTXfifo(struct s_spi *p_spi)
{
  p_spi->control_ext.bits.rst_tx = 1;
}

// reset rx fifo
void setSpiResetRXfifo(struct s_spi *p_spi)
{
  p_spi->control_ext.bits.rst_rx = 1;
}

//  block rx fifo
void setSpiBlockRXfifo(struct s_spi *p_spi)
{
  p_spi->control_ext.bits.blk_rx = 1;
}

// unblock rx fifo
void unsetSpiBlockRXfifo(struct s_spi *p_spi)
{
  p_spi->control_ext.bits.blk_rx = 0;
}

// set mode for CPHA/CPOL, does nothing at the moment.
void setSpiMode(struct s_spi *p_spi, uint8_t cpha, uint8_t cpol)
{
  p_spi->control_ext.bits.cpha = (cpha == 1 ? cpha : 0);
  p_spi->control_ext.bits.cpol = (cpol == 1 ? cpol : 0);
}
