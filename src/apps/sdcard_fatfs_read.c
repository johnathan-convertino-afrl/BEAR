#include <base.h>

#include <uart/uart.h>
#include <pff3a/diskio.h>

#include <stdint.h>

int main()
{
  // int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  FATFS file_sys;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    sendUartString(p_uart, "MOUNT FAILED\n");
  }
  
  error = pf_open("input.txt");
  
  if(error)
  {
    sendUartString(p_uart, "FILE OPEN FAILED\n");
  }

  for(;;)
  {
    int index_char;
    unsigned int len;
    
    DIR root_dir;
    
    error = pf_opendir(&root_dir,"/");
    
    if(error)
    {
      sendUartString(p_uart, "OPEN DIR FAILED");
    }
    else
    {
      sendUartString(p_uart, "LISTING DIR");
      
      do
      {
        FILINFO file_info;
        error = pf_readdir(&root_dir, &file_info);
        
        sendUartString(p_uart, file_info.fname);
      }
      while(!error);
    }
    
    delay(2000);
    
    sendUartString(p_uart, "Starting read of the first 512 Bytes..\n");
    
    pf_read(r_buf, 512, &len);	
    
    for(index_char = 0; index_char < 512; index_char++)
    {
      if(index_char == 0) sendUartString(p_uart, "\r");
      
      if(index_char%80 == 0)
      {
        sendUartString(p_uart, "\r");
      }
      
      while(p_uart->status.bits.tx_fifo_full);
      
      setUartTxData(p_uart, r_buf[index_char]);
    }
  }
}
