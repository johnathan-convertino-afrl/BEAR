/***************************************************************************//**
  * @file     gpio.c
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

#include "gpio.h"

// Initializes gpio structure and device
// to defaults, no IRQ, 0 output data, ALL outputs.
struct s_gpio *initGpio(uint32_t memory_address)
{
  struct s_gpio *p_temp = (struct s_gpio *)memory_address;

  p_temp->data1 = 0;
  p_temp->tri1  = 0;
  p_temp->data2 = 0;
  p_temp->tri2  = 0;
  p_temp->gier.reg  = 0;
  p_temp->ier.reg   = 0;
  p_temp->isr.reg   = 0;

  return p_temp;
}

// Write data to the GPIO 1 port
void setGpioData1(struct s_gpio *p_gpio, uint32_t data)
{
  if(!p_gpio) return;
  
  p_gpio->data1 = data;
}

// Read data to the GPIO 1 port
uint32_t getGpioData1(struct s_gpio *p_gpio)
{
  if(!p_gpio) return 0;
  
  return p_gpio->data1;
}

// Set GPIO tristate bits for data1 (0 output, 1 input).
void setGpioTriData1(struct s_gpio *p_gpio, uint32_t data)
{
  if(!p_gpio) return;
  
  p_gpio->tri1 = data;
}

// enable gpio global interrupt generation
void setGpioIntrEna(struct s_gpio *p_gpio)
{
  if(!p_gpio) return;
  
  p_gpio->gier.bits.gie = 1;
}

// disable gpio global interrupt generation
void unsetGpioIntrEna(struct s_gpio *p_gpio)
{
  if(!p_gpio) return;
  
  p_gpio->gier.bits.gie = 0;
}

// enable gpio channel one interrupt generation
void setGpioChanOneIntrEna(struct s_gpio *p_gpio)
{
  if(!p_gpio) return;
  
  p_gpio->ier.bits.ch1_ena = 1;
}

// disable gpio channel one interrupt generation
void unsetGpioChanOneIntrEna(struct s_gpio *p_gpio)
{
  if(!p_gpio) return;
  
  p_gpio->ier.bits.ch1_ena = 0;
}

// get channel one interrupt status
uint8_t getGpioChanOneIntrStatus(struct s_gpio *p_gpio)
{
  if(!p_gpio) return -1;
  
  return p_gpio->isr.bits.ch1_sta;
}

// Acknoledge the current interrupt
void ackGpioChanOneIntr(struct s_gpio *p_gpio)
{
  if(!p_gpio) return;
  
  p_gpio->isr.bits.ch1_sta = 1;
}
