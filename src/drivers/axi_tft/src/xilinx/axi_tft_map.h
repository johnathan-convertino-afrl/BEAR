/***************************************************************************//**
  * @file     axi_tft_map.h
  * @brief    Xilinx AXI TFT driver
  * @details  Baremetal C driver targeting Xilinx based AXI TFT cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/12/2026
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

#ifndef __AXI_TFT_MAP_H
#define __AXI_TFT_MAP_H

#include <stdint.h>

#define XRES      640
#define YRES      480
#define XRES_VIR  1024
#define YRES_VIR  480

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct s_axi_tft
 * @brief A struct to use for various axi tft devices. Will get memory mapped by init.
 */
struct s_axi_tft
{
  /**
  * @var s_axi_tft::addr
  * Address register
  */
  volatile uint32_t addr;

  /**
  * @union u_cr
  * @brief Register cr with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_tft:u_cr:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @struct s_cr_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_tft:u_gier:s_cr_bits:tde
      * display enable
      */
      volatile uint8_t tde:1;
      /**
      * @var s_axi_tft:u_gier:s_cr_bits:dps
      * display rotate
      */
      volatile uint8_t dps:1;
      /**
      * @var s_axi_tft:u_cr:s_cr_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:30;
    } bits;
  } cr;

  /**
  * @union u_iesr
  * @brief Register iesr with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_tft:u_iesr:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_iesr_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_tft:u_iesr:s_iesr_bits:status
      * Status of address latch and vsync irq.
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_tft:u_ier:s_iesr_bits:reserved0
      * Unused bits
      */
      volatile uint32_t reserved0:2;
      /**
      * @var s_axi_tft:u_iesr:s_iesr_bits:ie
      * Enable Interrupt
      */
      volatile uint8_t ie:1;

      /**
      * @var s_axi_tft:u_ier:s_iesr_bits:reserved1
      * Unused bits
      */
      volatile uint32_t reserved1:28;
    } bits;
  } iesr;
};

#ifdef __cplusplus
}
#endif

#endif


