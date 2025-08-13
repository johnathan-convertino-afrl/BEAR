/***************************************************************************//**
  * @file     gpio.h
  * @brief    Xilinx AXI GPIO driver
  * @details  Baremetal C driver targeting Xilinx based GPIO cores.
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

#ifndef __GPIO_DRV_H
#define __GPIO_DRV_H

#include <stdint.h>
#include "gpio_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************//**
  * @brief Initializes gpio structure and device
  * to defaults, no IRQ, 0 output data, ALL outputs.
  *
  * @param memory_address is the starting memory_address
  * of the gpio on the system bus.
  *
  * @return s_gpio is a struct with a pointer to the
  * device memory address
  *************************************************/
struct s_gpio *initGpio(uint32_t memory_address);

#ifdef __cplusplus
}
#endif

#endif


