#include <base.h>

#include <uart/uart.h>
#include <sdcard_spi/sdcard_spi.h>

#include <stdint.h>

#define UART_ADDR   0x44A10000
#define SPI_ADDR    0x44A20000

int main()
{
  int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  uint8_t w_buf[512] = {0};
  
  struct s_sdcard_spi sdcard_spi;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  error = initSdcardSpi(&sdcard_spi, SPI_ADDR, 0);
  
  sendUartString(p_uart, "\n\r");

  sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
  
  delay(2000);
  
  for(index = 0; index < 512; index++)
  {
    w_buf[index] = 'A';
  }

  for(;;)
  {
    int index_char;

    error = readSdcardSpi(&sdcard_spi, 0, r_buf);
    
    if(error != 0)
    {
      sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
      
      sendUartString(p_uart, "READ ERROR");
      
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
    
    error =  writeSdcardSpi(&sdcard_spi, 1, w_buf);
  
    if(error != 0)
    {
      sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
      
      sendUartString(p_uart, "WRITE ERROR");
    }
  }
}
