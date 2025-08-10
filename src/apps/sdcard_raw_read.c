#include <base.h>

#include <uart/uart.h>
#include <sdcard_spi/sdcard_spi.h>

#include <stdint.h>

int main()
{
  int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  struct s_sdcard_spi sdcard_spi;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  error = initSdcardSpi(&sdcard_spi, SPI_ADDR, 0);
  
  sendUartString(p_uart, "\n\r");

  sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));

  for(;;)
  {
    int index_char;
    
    delay(2000);
    
    sendUartString(p_uart, "Starting read..\n");
    
    // read 256 KiB of SD CARD data.
    for(index = 0; index < 512; index++)
    {
      error = readSdcardSpi(&sdcard_spi, index, r_buf, 0, 512);
      
      if(error)
      {
        sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
        
        continue;
      }
      
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
}
