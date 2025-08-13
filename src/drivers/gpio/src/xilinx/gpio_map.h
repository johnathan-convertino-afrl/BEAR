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

#ifndef __GPIO_MAP_H
#define __GPIO_MAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct s_gpio
 * @brief A struct to use for various gpio devices. Will get memory mapped by init.
 */
struct s_gpio
{
  /**
  * @var s_gpio::data1
  * Channel 1 data register
  */
  volatile uint32_t data1;
  /**
  * @var s_gpio::tri1
  * Channel 1 tristate register
  */
  volatile uint32_t tri1;
  /**
  * @var s_gpio::data2
  * Channel 2 data register
  */
  volatile uint32_t data2;
  /**
  * @var s_gpio::tri2
  * Channel 2 tristate register
  */
  volatile uint32_t tri2;

  /**
  * @union u_gier
  * @brief Register gier with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_gpio:u_gier:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_gier_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_gpio:u_gier:s_gier_bits:reserver
      * Unused bits
      */
      volatile uint32_t reserved:31;
      /**
      * @var s_gpio:u_gier:s_gier_bits:gie
      * Global interupt enable bit
      */
      volatile uint8_t gie:1;
    } bits;
  } gier;

  /**
  * @union u_ier
  * @brief Register ier with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_gpio:u_ier:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_ier_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_gpio:u_ier:s_ier_bits:ch1_ena
      * Channel 1 interupt enable.
      */
      volatile uint8_t ch1_ena:1;

      /**
      * @var s_gpio:u_ier:s_ier_bits:ch2_ena
      * Channel 2 interupt enable.
      */
      volatile uint8_t ch2_ena:1;

      /**
      * @var s_gpio:u_ier:s_ier_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:30;
    } bits;
  } ier;

  /**
  * @union u_isr
  * @brief Register isr with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_gpio:u_isr:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_isr_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_gpio:u_isr:s_isr_bits:ch1_sta
      * Channel 1 interupt status.
      */
      volatile uint8_t ch1_sta:1;

      /**
      * @var s_gpio:u_isr:s_isr_bits:ch2_sta
      * Channel 2 interupt status.
      */
      volatile uint8_t ch2_sta:1;

      /**
      * @var s_gpio:u_ier:s_isr_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:30;
    } bits;
  } isr;
};

#ifdef __cplusplus
}
#endif

#endif


