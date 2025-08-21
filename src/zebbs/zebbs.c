#include <base.h>

#include <uart.h>
#include <pff3a/diskio.h>

#include <stdint.h>
#include <string.h>

#define NUM_FILE_NAMES 2

int main()
{
  int index = NUM_FILE_NAMES;
  int error = 0;
  
  uint8_t *p_buf = NULL;
  
  char *p_file_names[NUM_FILE_NAMES] = {"app.bin", "u-boot-spl.bin"};
  
  FATFS file_sys;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  sendUartString(p_uart, "ZEBBS: Starting");
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    sendUartString(p_uart, "ZEBBS: SDCARD MOUNT FAILED");
    
    return 0;
  }
  
  do
  {
    error = pf_open(p_file_names[--index]);
    
    if(!error) break;
  }
  while(index > 0);
  
  if(error) sendUartString(p_uart, "ZEBBS: FAILED TO READ APP OR UBOOT BINARY");
  
  p_buf = (uint8_t *)(index ? UBOOT_START : DDR_ADDR);

  //if error index will be 0 and we will jump to ddr, this is so jtag loaded apps can be run after a reset.
  if(!error)
  {
    sendUartString(p_uart, "ZEBBS: Load Started");
    for(;;)
    {
      unsigned int len = 0;

      error = pf_read(p_buf, 512, &len);
      
      if(error)
      {
        sendUartString(p_uart, "ZEBBS: FAILED TO READ FILE");
        continue;
      }
      
      p_buf += len;
      
      //finished read
      if(len < 512) 
      {
        sendUartString(p_uart, "ZEBBS: Load Completed");
        break;
      }
    }
  }
  
  sendUartString(p_uart, "ZEBBS: Executing Jump");
  
  if(index)
  {
    __asm__ volatile ("li t0, %0" : : "i" (UBOOT_START) :);
  }
  else
  {
    __asm__ volatile ("li t0, %0" : : "i" (DDR_ADDR) :);
  }
  
  __asm__ volatile ("jalr zero, t0, 0");
  
  return 0;
}
