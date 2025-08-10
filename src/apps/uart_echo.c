#include <base.h>

#include <uart/uart.h>

#include <stdint.h>

int main()
{
  struct s_uart *p_uart = initUart(UART_ADDR);

  delay(2000);

  for(;;)
  {
    delay(2000);

    if(p_uart->status.bits.rx_fifo_valid)
    {
      uint8_t temp;

      temp = getUartRxData(p_uart);

      setUartTxData(p_uart, temp);
    }
  }
}
