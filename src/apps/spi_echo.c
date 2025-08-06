#include <base.h>

#include <uart/uart.h>
#include <spi/spi.h>

#include <stdint.h>

#define UART_ADDR   0x44A10000
#define SPI_ADDR    0x44A20000

int main()
{
  struct s_uart *p_uart = initUart(UART_ADDR);
  
  struct s_spi  *p_spi  = initSpi(SPI_ADDR);

  delay(2000);
  
  uint8_t i = 0;
  
  setSpiClockFreq(p_spi, 5000000);

  for(;;)
  {
    uint8_t copy;
    
    setSpiData(p_spi, i);
    
//     while(!getSpiReadReady(p_spi));
//     
//     copy = getSpiData(p_spi);
    
    i++;
  }
}
