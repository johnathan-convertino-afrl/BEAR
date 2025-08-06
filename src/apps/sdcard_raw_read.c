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
  
  uint8_t buf[512] = {0};
  
  struct s_sdcard_spi sdcard_spi;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  error = initSdcardSpi(&sdcard_spi, SPI_ADDR, 0);
  
  sendUartString(p_uart, "\n\r");

  sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
  
  delay(2000);

  for(;;)
  {
    int index_char;
    int index_col = 0;
    
    delay(1000000);
    
    error = readSdcardSpi(&sdcard_spi, index, buf);
    
    if(error != 0)
    {
      sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
      
      for(index_char = 0; index_char < 512; index_char++)
        buf[index_char] = (uint8_t)'\r';
      
      buf[509] = 'E';
      buf[510] = '\n';
      buf[511] = '\r';
    }

    for(index_char = 0; index_char < 512; index_char++)
    {
      if(index_char == 0) sendUartString(p_uart, "\r");
      
      index_col++;
      
      setUartTxData(p_uart, buf[index_char]);

      if(index_col == 80)
      {
        sendUartString(p_uart, "\r");
        index_col = 0;
      }
    }
    sendUartString(p_uart, "\r");
  }
}
