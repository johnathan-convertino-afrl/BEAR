/***************************************************************************//**
  * @file     beario.h
  * @brief    Generic Uart IO for C
  * @details  Baremetal C driver targeting UART
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     08/28/2025
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

#include <stdint.h>

#include "beario.h"

struct s_uart *__gp_uart = initUart(UART_ADDR);

// emulates printf functionality
int beario_printf(char *str_format, ...)
{
  
}

// emulates scanf functionality
int beario_scanf(char *str_format, ...)
{
  
}

// emulate putchar
int beario_putchar(int chr)
{
  while(getUartTxFifoFull(__gp_uart));
  
  setUartTxData(__gp_uart, (uint8_t) chr);
  
  return chr;
}

//emulate getchar
int beario_getchar()
{
  while(!getUartRxFifoValid(__gp_uart));
  
  return getUartRxData(__gp_uart);
}


