/***************************************************************************//**
  * @file     uart.h
  * @brief    Xilinx AXI UART driver
  * @details  Baremetal C driver targeting Xilinx based UART lite cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     08/26/2024
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2024 Johnathan Convertino
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

#ifndef __UART_DRV_H
#define __UART_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @struct s_uart
 * @brief A struct to use for various uart devices. Will get memory mapped by init.
 */
struct s_uart
{
  /**
  * @var s_uart::rx_fifo
  * Receive data FIFO
  */
  volatile uint32_t rx_fifo;
  /**
  * @var s_uart::tx_fifo
  * Transmit data FIFO
  */
  volatile uint32_t tx_fifo;

  /**
  * @union u_status
  * @brief Register status with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_uart:u_status:reg
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
      * @var s_uart:u_status:s_status_bits:rx_fifo_valid
      * Valid data in the receive fifo
      */
      volatile uint8_t rx_fifo_valid:1;
      /**
      * @var s_uart:u_status:s_status_bits:rx_fifo_full
      * Receive fifo is full
      */
      volatile uint8_t rx_fifo_full:1;
      /**
      * @var s_uart:u_status:s_status_bits:tx_fifo_empty
      * Transmit fifo is empty
      */
      volatile uint8_t tx_fifo_empty:1;
      /**
      * @var s_uart:u_status:s_status_bits:tx_fifo_full
      * Transmit fifo is full
      */
      volatile uint8_t tx_fifo_full:1;
      /**
      * @var s_uart:u_status:s_status_bits:intr_ena
      * Interrupt is enabled
      */
      volatile uint8_t intr_ena:1;
      /**
      * @var s_uart:u_status:s_status_bits:overrun_err
      * Receive fifo overflow error
      */
      volatile uint8_t overrun_err:1;
      /**
      * @var s_uart:u_status:s_status_bits:frame_err
      * Receive frame error, stop detected early.
      */
      volatile uint8_t frame_err:1;
      /**
      * @var s_uart:u_status:s_status_bits:parity_err
      * Receive has data with parity error
      */
      volatile uint8_t parity_err:1;
      /**
      * @var s_uart:u_status:s_status_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:24;
    } bits;
  } status;

  /**
  * @union u_control
  * @brief Register control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_uart:u_control:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_control_bits
    * @brief packed struct with bits.
    */
    struct s_control_bits
    {
      /**
      * @var s_uart:u_control:s_control_bits:rst_tx_fifo
      * Clear the transmit fifo
      */
      volatile uint8_t rst_tx_fifo:1;
      /**
      * @var s_uart:u_control:s_control_bits:rst_rx_fifo
      * Clear the receive fifo
      */
      volatile uint8_t rst_rx_fifo:1;
      /**
      * @var s_uart:u_control:s_control_bits:unused
      * Unused bits
      */
      volatile uint8_t unused:2;
      /**
      * @var s_uart:u_control:s_control_bits:ena_intr
      * Enable interrupt
      */
      volatile uint8_t ena_intr:1;
      /**
      * @var s_uart:u_control:s_control_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:27;
    } bits;
  } control;
};

/*********************************************//**
  * @brief Initializes uart structure and device
  * to defaults, no IRQ, clear all fifos.
  *
  * @param memory_address is the starting memory_address
  * of the uart on the system bus.
  *
  * @return s_uart is a struct with a pointer to the
  * device memory address
  *************************************************/
struct s_uart *initUart(uint32_t memory_address);

/*********************************************//**
  * @brief Read uart rx data
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 8 bit uint with data.
  *************************************************/
uint8_t getUartRxData(struct s_uart *p_uart);

/*********************************************//**
  * @brief Write uart tx data
  *
  * @param p_uart pre-initialized struct from initUart
  * @param data 8 bit uint to write to uart device
  *************************************************/
void setUartTxData(struct s_uart *p_uart, uint8_t data);

/*********************************************//**
  * @brief Write Strings to UART, send with \n\r terminaton
  *
  * @param p_uart pre-initialized struct from initUart
  * @param p_string String with null terminator.
  *************************************************/
void sendUartString(struct s_uart *p_uart, const char *p_string);

/*********************************************//**
  * @brief Read Strings from UART, with \n\r terminaton
  *
  * @param p_uart pre-initialized struct from initUart
  * @param p_string String for storage.
  * @param len max length the buffer can support.
  *
  * @return length of string with null terminator.
  *************************************************/
int recvUartString(struct s_uart *p_uart, char *p_string, int len);

#ifdef __cplusplus
}
#endif

#endif


