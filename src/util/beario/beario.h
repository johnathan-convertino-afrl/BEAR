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

#ifndef __BEAR_IO_UTIL_H
#define __BEAR_IO_UTIL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************//**
  * @brief emulates printf functionality
  * 
  * @param str_format same as the printf format line
  * @param ... Variable parameters.
  * 
  * @return Number of characters, or a negative value on error.
  *************************************************/
int beario_printf(char *str_format, ...);

/*********************************************//**
  * @brief emulates scanf functionality
  *
  * @param str_format same as the scanf format line
  * @param ... variable parameters
  * 
  * @return > 0 number of values converted, 0 no value, < 0 EOF.
  *************************************************/
int beario_scanf(char *str_format, ...);

/*********************************************//**
  * @brief emulate putchar
  * 
  * @param chr Character to print
  * 
  * @return success, return char written, failure EOF.
  *************************************************/
int beario_putchar(int chr);

/*********************************************//**
  * @brief emulate getchar
  * 
  * @return character or EOF on failure.
  *************************************************/
int beario_getchar();

#ifdef __cplusplus
}
#endif

#endif


