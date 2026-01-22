/***************************************************************************//**
  * @file     dev_init.c
  * @brief    Provide device init for apps and zebbs
  * @details  Setup UART and SDCARD for stdout/in, and file io.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/22/2026
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2026 Johnathan Convertino
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
#include <base.h>
#include "global_pointers.h"

struct s_uart *__gp_uart;

void __attribute__((constructor)) dev_init(void)
{
  __gp_uart = (struct s_uart *)UART_ADDR;
  
//   __gp_sdcard_spi = malloc(sizeof(struct s_sdcard_spi));
//   
//   if(!__gp_sdcard_spi) beario_stronly_printf("SDCARD SPI MALLOC RESULT WAS NULL\n\r");
}
