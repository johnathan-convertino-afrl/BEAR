/***************************************************************************//**
  * @file     zebbs.c
  * @brief    Zero stage bootloader for u-boot and baremetal applications.
  * @details  Will attempt to load u-boot first, then a file called app.bin
  *           after that it will jump to their start address. Meaning that JTAG
  *           loading of programs will work after reset.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     09/17/2025
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

#include <base.h>

#include <pff3a/diskio.h>
#include <beario/beario.h>

#include <stdint.h>
#include <string.h>

#define NUM_FILE_NAMES 2

void zebbs_printf(char *info_str);

int main()
{
  int index = NUM_FILE_NAMES;
  int error = 0;
  
  uint8_t *p_buf = NULL;
  
  char *p_file_names[NUM_FILE_NAMES] = {"app.bin", "fw_payload.bin"};
  
  FATFS file_sys;
  
  beario_stronly_printf("\n\r");
  
  zebbs_printf("Starting");
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    zebbs_printf("SDCARD MOUNT FAILED");
    
    return 0;
  }
  
  do
  {
    error = pf_open(p_file_names[--index]);
    
    if(!error) break;
  }
  while(index > 0);
  
  if(error) zebbs_printf("FAILED TO READ BINARY");
  
  p_buf = (uint8_t *)(index ? OPENSBI_START : DDR_ADDR);

  //if error index will be 0 and we will jump to ddr, this is so jtag loaded apps can be run after a reset.
  if(!error)
  {
    unsigned int len = 0;
    zebbs_printf("Load Started");
    
    do
    {
      error = pf_read(p_buf, 512, &len);
      
      if(error)
      {
        zebbs_printf("FAILED TO READ FILE");
        continue;
      }
      
      p_buf += len;
      
      //finished read
      if(len < 512)  zebbs_printf("Load Completed");
    }
    while(len >= 512);
    
  }
  
  zebbs_printf("Executing Jump");
  
  if(index)
  {
    __asm__ volatile ("li t0, %0" : : "i" (OPENSBI_START) :);
  }
  else
  {
    __asm__ volatile ("li t0, %0" : : "i" (DDR_ADDR) :);
  }
  
  __asm__ volatile ("jalr zero, t0, 0");
  
  return 0;
}

void zebbs_printf(char *info_str)
{
  beario_stronly_printf("ZEBBS: %s\n\r", info_str);
}
