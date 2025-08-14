#include <base.h>

#include <uart.h>

#include <stdint.h>

int main()
{
  struct s_uart *p_uart = initUart(UART_ADDR);

  __delay_ms(2);

  for(;;)
  {
    __delay_ms(2);

    if(p_uart->status.bits.rx_fifo_valid)
    {
      uint8_t temp;

      temp = getUartRxData(p_uart);

      setUartTxData(p_uart, temp);
    }
  }
}
