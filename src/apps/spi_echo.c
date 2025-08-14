#include <base.h>

#include <uart.h>
#include <spi.h>

#include <stdint.h>

int main()
{
  uint8_t i = 0;
  
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  struct s_spi  *p_spi  = initSpi(SPI_ADDR);

  __delay_ms(2);
  
  setSpiClockFreq(p_spi, 1000000);

  for(;;)
  {
    uint8_t res;
    
    setSpiData(p_spi, i);
    
    while(!getSpiReadReady(p_spi));
    
    res = getSpiData(p_spi);
    
    setUartTxData(p_uart, res);
    
    i++;
  }
}
