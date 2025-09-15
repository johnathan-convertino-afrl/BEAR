#include <base.h>

#include <beario/beario.h>
#include <pff3a/diskio.h>

#include <stdint.h>

int main()
{
  // int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  FATFS file_sys;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  beario_printf("MOUNT DRIVE\n");
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    beario_printf("MOUNT FAILED\n");
    
    return 0;
  }
  
  beario_printf("OPEN TEXT\n");
  
  error = pf_open("input.txt");
  
  if(error)
  {
    beario_printf("FILE OPEN FAILED\n");
    return 0;
  }

  for(;;)
  {
    unsigned int index_char;
    unsigned int len;
    
    
    __delay_ms(2);
    
    error = pf_read(r_buf, 512, &len);
    
    if(error)
    {
      beario_printf("FAILED TO READ FILE\n");
      continue;
    }
    
    for(index_char = 0; index_char < len; index_char++)
    {
      if(index_char%64 == 0)
      {
        beario_printf("\r");
      }
      
      while(p_uart->status.bits.tx_fifo_full);
      
      setUartTxData(p_uart, r_buf[index_char]);
    }
    
    if(len < 512)
    {
      beario_printf("\n\rFINISHED READING FILE\n");
      return 0;
    }
  }
}
