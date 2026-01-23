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
#include <riscv-csr.h>

#include <pff3a/diskio.h>
#include <beario/beario.h>

#include <stdint.h>
#include <string.h>

#define NUM_FILE_NAMES 3
#define NUM_OF_TRIES 5

int zebbs_file_read(uint8_t *p_buf);
void zebbs_printf(char *info_str);

int main()
{
  int index = NUM_FILE_NAMES;
  int error = 0;
  int tries = NUM_OF_TRIES;

  char *p_file_names[NUM_FILE_NAMES] = {"app.bin", "u-boot.bin", "opensbi.bin"};
  
  FATFS file_sys;
  
  zebbs_printf("\n");

  zebbs_printf("Starting");
  
  __delay_ms(1000);
  
  do
  {
    error = pf_mount(&file_sys);
    
    if(!error) break;
    
    zebbs_printf("Restarting");
  } 
  while(--tries);
    
  if(error)
  {
    zebbs_printf("SDCARD MOUNT FAILED");
    
    return 0;
  }
  
  do
  {
    zebbs_printf(p_file_names[--index]);
    
    error = pf_open(p_file_names[index]);
    
    if(!error) break;
    
    if(error) 
    {
      zebbs_printf("FAILED TO OPEN FILE");
      //decrement index to load app
      if(index == (NUM_FILE_NAMES-1)) index--;
    }
  }
  while(index > 0);
  
  //if error index will be 0 and we will jump to ddr, this is so jtag loaded apps can be run after a reset.
  if(!error)
  {
    error = zebbs_file_read((uint8_t *)DDR_ADDR);
    
    //if we are not the last file and there is no error, load uboot
    if((index > 0) && !error)
    {
      error = pf_open(p_file_names[--index]);
      
      zebbs_printf(p_file_names[index]);
      
      if(error) zebbs_printf("FAILED TO OPEN FILE");
      
      error = zebbs_file_read((uint8_t *)UBOOT_START);
    }
    
  }
  
  zebbs_printf("Executing Jump");
  
  __asm__ volatile ("li a0, 0");
  
  __asm__ volatile ("la a2, _BAD_JUMP");

  __asm__ volatile ("li t0, %0" : : "i" (DDR_ADDR) :);
  
  __asm__ volatile ("jalr zero, t0, 0");
  
  __asm__ volatile ("_BAD_JUMP:");
  
  zebbs_printf("JUMP FAILED");
  
  return 0;
}

int zebbs_file_read(uint8_t *p_buf)
{
  int error = 0;
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
  
  return error;
}

void zebbs_printf(char *info_str)
{
  beario_stronly_printf("ZEBBS: %s\n\r", info_str);
}
