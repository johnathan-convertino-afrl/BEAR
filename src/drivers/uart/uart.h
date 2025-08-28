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
#include "uart_map.h"

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

/*********************************************//**
  * @brief check if rx fifo is full
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 1 for full, 0 for not.
  *************************************************/
int getUartRxFifoFull(struct s_uart *p_uart);

/*********************************************//**
  * @brief check if rx fifo has valid data
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 1 for valid, 0 for not.
  *************************************************/
int getUartRxFifoValid(struct s_uart *p_uart);

/*********************************************//**
  * @brief check if TX fifo is empty
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 1 for empty, 0 for not.
  *************************************************/
int getUartTxFifoEmpty(struct s_uart *p_uart);

/*********************************************//**
  * @brief check if tx fifo is full
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 1 for full, 0 for not.
  *************************************************/
int getUartTxFifoFull(struct s_uart *p_uart);

/*********************************************//**
  * @brief check if interrupt is enabled
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 1 for enabled, 0 for not.
  *************************************************/
int getUartIrqEna(struct s_uart *p_uart);

/*********************************************//**
  * @brief check if there is an error
  *
  * @param p_uart pre-initialized struct from initUart
  *
  * @return 0 no error, 1 overrun, 2 frame, 4 parity. These can add up to 7. 
  *************************************************/
int getUartError(struct s_uart *p_uart);

/*********************************************//**
  * @brief reset tx fifo
  * 
  * @param p_uart pre initialized struct from initUart
  *************************************************/
void setUartResetTXfifo(struct s_uart *p_uart);

/*********************************************//**
  * @brief reset rx fifo
  * 
  * @param p_uart pre initialized struct from initUart
  *************************************************/
void setUartResetRXfifo(struct s_uart *p_uart);

/*********************************************//**
  * @brief reset rx fifo
  * 
  * @param p_uart pre initialized struct from initUart
  *************************************************/
void setUartResetRXfifo(struct s_uart *p_uart);

/*********************************************//**
  * @brief enable uart interrupt generation
  * 
  * @param p_uart pre initialized struct from initUart
  *************************************************/
void setUartIntrEna(struct s_uart *p_uart);

/*********************************************//**
  * @brief disable uart interrupt generation
  * 
  * @param p_uart pre initialized struct from initUart
  *************************************************/
void unsetUartIntrEna(struct s_uart *p_uart);

#ifdef __cplusplus
}
#endif

#endif


