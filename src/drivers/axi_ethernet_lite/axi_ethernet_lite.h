/***************************************************************************//**
  * @file     axi_ethernet_lite.h
  * @brief    Xilinx AXI Ethernet Lite driver
  * @details  Baremetal C driver targeting Xilinx based AXI Ethernet Lite cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/15/2026
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

#ifndef __AXI_ETHERNET_LITE_DRV_H
#define __AXI_ETHERNET_LITE_DRV_H

#include <stdint.h>
#include "axi_ethernet_lite_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************//**
  * @brief Initializes axi ethernet lite structure and device
  * to defaults, no IRQ, 0 output data, ALL outputs.
  *
  * @param memory_address is the starting memory_address
  * of the axi tft on the system bus.
  *
  * @return s_axi_ethernet_lite is a struct with a pointer to the
  * device memory address
  *************************************************/
struct s_axi_ethernet_lite *initAxiEthernetLite(uint32_t memory_address);

// /*********************************************//**
//   * @brief get axi tft base video memory start address
//   * 
//   * @param p_axi_tft pre initialized struct from initAxiTft
//   * 
//   * @return 32bit unsigned int that is the address.
//   *************************************************/
// uint32_t getAxiTftVmemAddr(struct s_axi_tft *p_axi_tft);
// 
// /*********************************************//**
//   * @brief set axi tft base video memory start address
//   * 
//   * @param p_axi_tft pre initialized struct from initAxiTft
//   * 
//   * @param vmem_address new 2MB aligned base address.
//   *************************************************/
// void setAxiTftVmemAddr(struct s_axi_tft *p_axi_tft, uint32_t vmem_addr);
// 
// /*********************************************//**
//   * @brief Write buffer data to vram space
//   * 
//   * @param p_axi_tft pre initialized struct from initAxiTft
//   * @param start Pixel offset to start writting to.
//   * @param p_buffer 32bit unsigned data that is a8r8g8b8 (MSB to LSB).
//   * @param len Number of words (32bit) in the buffer to write.
//   *************************************************/
// void writeAxiTftVRAMbuffer(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t *p_buffer, uint32_t len);
// 
// /*********************************************//**
//   * @brief Write constant data to vram space
//   * 
//   * @param p_axi_tft pre initialized struct from initAxiTft
//   * @param start Pixel offset to start writting to.
//   * @param const_data 32bit unsigned data that is a8r8g8b8
//   * @param len Number of words (32bit) in the buffer to write.
//   *************************************************/
// void writeAxiTftVRAMconst(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t const_data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif


