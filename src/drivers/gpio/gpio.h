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

/*********************************************//**
  * @brief Write data to the GPIO 1 port
  *
  * @param p_gpio is the object returned from initGpio.
  * @param data is the 32bit data word to set the output to.
  *************************************************/
void setGpioData1(struct s_gpio *p_gpio, uint32_t data);

/*********************************************//**
  * @brief Read data to the GPIO 1 port
  *
  * @param p_gpio is the object returned from initGpio.
  * 
  * @return 32bit data word from gpio
  *************************************************/
uint32_t getGpioData1(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief Set GPIO tristate bits for data1 (0 output, 1 input).
  *
  * @param p_gpio is the object returned from initGpio.
  * @param data is the 32bit data word to set tristate to.
  *************************************************/
void setGpioTriData1(struct s_gpio *p_gpio, uint32_t data);

/*********************************************//**
  * @brief enable gpio global interrupt generation
  * 
  * @param p_gpio pre initialized struct from initGpio
  *************************************************/
void setGpioIntrEna(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief disable gpio global interrupt generation
  * 
  * @param p_gpio pre initialized struct from initGpio
  *************************************************/
void unsetGpioIntrEna(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief enable gpio channel one interrupt generation
  * 
  * @param p_gpio pre initialized struct from initGpio
  *************************************************/
void setGpioChanOneIntrEna(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief disable gpio channel one interrupt generation
  * 
  * @param p_gpio pre initialized struct from initGpio
  *************************************************/
void unsetGpioChanOneIntrEna(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief get channel one interrupt status
  * 
  * @param p_gpio pre initialized struct from initGpio
  * 
  * @return current Interrupt status, 1 it has been triggered, 0 it has not.
  *************************************************/
uint8_t getGpioChanOneIntrStatus(struct s_gpio *p_gpio);

/*********************************************//**
  * @brief Acknoledge the current interrupt
  * 
  * @param p_gpio pre initialized struct from initGpio
  *************************************************/
void ackGpioChanOneIntr(struct s_gpio *p_gpio);

#ifdef __cplusplus
}
#endif

#endif


