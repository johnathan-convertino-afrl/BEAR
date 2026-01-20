/***************************************************************************//**
  * @file     axi_ethernet_lite.c
  * @brief    Xilinx AXI Ethernet Lite driver
  * @details  Baremetal C driver targeting Xilinx based AXI Ethernet Lite cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/15/26
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

#include "axi_ethernet_lite.h"
#include <string.h>

// Write data to vram space
// void writeAxiTftVRAM(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t *p_buffer, uint32_t len, uint32_t const_data);

// Initializes axi ethernet lite structure and device
struct s_axi_ethernet_lite *initAxiEthernetLite(uint32_t memory_address)
{
  struct s_axi_ethernet_lite *p_temp = (struct s_axi_ethernet_lite *)memory_address;
  
  return p_temp;
}

// // set display scan control bit to on, rotate 180 degrees
// void setAxiTftDPSon(struct s_axi_tft *p_axi_tft)
// {
//   if(!p_axi_tft) return;
//   
//   p_axi_tft->cr.bits.dps = 1;
// }
// 
// // set display scan control bit to off, no rotation
// void setAxiTftDPSoff(struct s_axi_tft *p_axi_tft)
// {
//   if(!p_axi_tft) return;
//   
//   p_axi_tft->cr.bits.dps = 0;
// }
// // Write data to vram space
// void writeAxiTftVRAMbuffer(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t *p_buffer, uint32_t len)
// {
//   if(!p_buffer) return;
//   
//   writeAxiTftVRAM(p_axi_tft, start, p_buffer, len, 0);
// }
// 
// // Write data to vram space
// void writeAxiTftVRAMconst(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t const_data, uint32_t len)
// {
//   writeAxiTftVRAM(p_axi_tft, start, NULL, len, const_data);
// }
// 
// // Write data to vram space, passing null to p_buffer will write const_data instead.
// void writeAxiTftVRAM(struct s_axi_tft *p_axi_tft, uint32_t start, uint32_t *p_buffer, uint32_t len, uint32_t const_data)
// {
//   // X should be between 0 to 640
//   uint16_t x_cor = start % XRES;
//   // Y needs to be a line number up to 480 from 640 X pixels drawn
//   uint16_t y_cor = start / XRES;
//   
//   uint32_t offset = 0;
//   
//   if(!p_axi_tft) return;
//   
//   //Starting outside of the res
//   if(start >= (XRES*YRES)) return;
//   
//   //Buffer too long
//   if(len > (XRES*YRES-start)) return;
//   
//   //Buffer too short
//   if(len <= 0) return;
//   
//   //Get start address
//   uint32_t *p_vram = (uint32_t *)p_axi_tft->addr;
//   
//   //offset if we are starting on a line greater than 0 by the virtual res.
//   p_vram += XRES_VIR*y_cor;
//   
//   //Create up to 480 pixels high in Y.
//   for(y_cor; y_cor < YRES; y_cor++)
//   {
//     //Create up to 640 pixels long in X
//     for(x_cor; x_cor < XRES; x_cor++)
//     {
//       //increment buffer with current x
//       *(p_vram+x_cor) = (p_buffer ? *(p_buffer+offset) : const_data);
//       
//       if(++offset >= len) return;
//     }
//     
//     //update pointer to new x plus offset unused virtual pixes.
//     p_vram = p_vram+(XRES_VIR-XRES)+x_cor;
//   
//     // reset x here since x_cor is set to start
//     x_cor = 0;
//   }
// }
