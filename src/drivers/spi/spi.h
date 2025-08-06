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
  
  
/**
* @struct s_spi
* @brief A struct to use for Altera spi devices. Will get memory mapped by init.
*/
struct s_spi
{
  /**
  * @var s_spi::rx_data
  * Receive data from spi
  */
  volatile uint32_t rx_data;
  
  /**
  * @var s_spi::tx_data
  * Transmit data for spi
  */
  volatile uint32_t tx_data;

  /**
  * @union u_status
  * @brief Register status with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_spi:u_status:reg
    * Status register
    */
    volatile uint32_t reg;

    /**
    * @union s_status_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_spi:u_status:s_status_bits:unused0
      * Unused bits
      */
      volatile uint8_t unused0:3;
      /**
      * @var s_spi:u_status:s_status_bits:roe
      * Receive has overrun (error).
      */
      volatile uint8_t roe:1;
      /**
      * @var s_spi:u_status:s_status_bits:toe
      * Transmit overrun (error)
      */
      volatile uint8_t toe:1;
      /**
      * @var s_spi:u_status:s_status_bits:tmt
      * Transmit shift register empty
      */
      volatile uint8_t tmt:1;
      /**
      * @var s_spi:u_status:s_status_bits:trdy
      * Transmit is ready
      */
      volatile uint8_t trdy:1;
      /**
      * @var s_spi:u_status:s_status_bits:rdy
      * Receive is ready
      */
      volatile uint8_t rrdy:1;
      /**
      * @var s_spi:u_status:s_status_bits:e
      * TOE or ROE is in an error state (active).
      */
      volatile uint8_t e:1;
      /**
      * @var s_spi:u_status:s_status_bits:eop
      * End of Packate has been detected
      */
      volatile uint8_t eop:1;
      /**
      * @var s_spi:u_status:s_status_bits:unused1
      * Unused bits
      */
      volatile uint32_t unused1:22;
    } bits;
  } status;

  /**
  * @union u_control
  * @brief Register control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_spi:u_control:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_control_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_spi:u_control:s_control_bits:unused0
      * Unused bits
      */
      volatile uint8_t unused0:3;
      /**
      * @var s_spi:u_control:s_control_bits:iroe
      * Set to generate interrupt on ROE going active.
      */
      volatile uint8_t iroe:1;
      /**
      * @var s_spi:u_control:s_control_bits:itoe
      * Set to generate interrupt on TOE going active.
      */
      volatile uint8_t itoe:1;
      /**
      * @var s_spi:u_control:s_control_bits:unused1
      * Unused bits
      */
      volatile uint8_t unused1:1;
      /**
      * @var s_spi:u_control:s_control_bits:itrdy
      * Set to generate interrupt on TRDY going active.
      */
      volatile uint8_t itrdy:1;
      /**
      * @var s_spi:u_control:s_control_bits:irrdy
      * Set to generate interrupt on RRDY going active.
      */
      volatile uint8_t irrdy:1;
      /**
      * @var s_spi:u_control:s_control_bits:ie
      * Set to generate interrupt on any error.
      */
      volatile uint8_t ie:1;
      /**
      * @var s_spi:u_control:s_control_bits:ieop
      * Set to generate interrupt on EOP going active.
      */
      volatile uint8_t ieop:1;
      /**
      * @var s_spi:u_control:s_control_bits:sso
      * Set to generate to 1 to make all slave selects active (override to 0).
      */
      volatile uint8_t sso:1;
      /**
      * @var s_spi:u_control:s_control_bits:unused1
      * Unused bits
      */
      volatile uint32_t unused2:21;
    } bits;
  } control;
  
  /**
  * @var s_spi::reserved
  * Unused register
  */
  volatile uint32_t reserved;
  
  /**
  * @var s_spi::slave_select
  * Select a slave by writting 1 (active) so chip select will go active low.
  */
  volatile uint32_t slave_select;
  
  /**
  * @var s_spi::eop_value
  * Set to value for comparison to tx or rx data to signal end of packet
  */
  volatile uint32_t eop_value;
  
  /**
  * @union u_status_ext
  * @brief Register status extended with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_spi:u_status_ext:reg
    * Status register ext
    */
    volatile uint32_t reg;

    /**
    * @union s_status_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_spi:u_status_ext:s_status_bits:fifo_ena
      * When 1 fifo is enabled
      */
      volatile uint8_t fifo_ena:1;
      /**
      * @var s_spi:u_status_ext:s_status_bits:rst_rx_act
      * RX fifo reset is active when 1
      */
      volatile uint8_t rst_rx_act:1;
      /**
      * @var s_spi:u_status_ext:s_status_bits:rst_tx_act
      * TX fifo reset is active when 1
      */
      volatile uint8_t rst_tx_act:1;
      /**
      * @var s_spi:u_status_ext:s_status_bits:unused0
      * Unused bits
      */
      volatile uint32_t unused0:29;
    } bits;
  } status_ext;
  
  /**
  * @union u_control_ext
  * @brief Register control extension with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_spi:u_control_ext:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_control_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_spi:u_control:s_control_bits:cpha
      * Set to change CPOL
      */
      volatile uint8_t cpol:1;
      /**
      * @var s_spi:u_control:s_control_bits:cpha
      * Set to change CPHA
      */
      volatile uint8_t cpha:1;
      /**
      * @var s_spi:u_control:s_control_bits:rst_tx
      * reset tx fifo
      */
      volatile uint8_t rst_tx:1;
      /**
      * @var s_spi:u_control:s_control_bits:rst_rx
      * reset rx fifo
      */
      volatile uint8_t rst_rx:1;
      /**
      * @var s_spi:u_control:s_control_bits:blk_rx
      * block rx output
      */
      volatile uint8_t blk_rx:1;
      /**
      * @var s_spi:u_control:s_control_bits:unused1
      * Unused bits
      */
      volatile uint32_t unused1:27;
    } bits;
  } control_ext;
  
  /**
  * @var s_spi::speed_control_ext
  * Set to a speed in hz for the SPI clock output.
  */
  volatile uint32_t speed_control_ext;
};

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

#ifdef __cplusplus
}
#endif

#endif


