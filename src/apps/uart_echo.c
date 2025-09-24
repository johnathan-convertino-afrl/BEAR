#include <base.h>

#include <uart.h>

#include <stdint.h>

int main()
{
  struct s_uart *p_uart = initUart(UART_ADDR);

  __delay_ms(2);
  
//  Inline assembly example of how to print an A on UART.
//   __asm__ volatile ("andi t3, zero, 0");
//   
//   __asm__ volatile ("lui t3, 0x44A10");
//   
//   __asm__ volatile ("li t2, 0x41");
//   
//   __asm__ volatile ("sw t2,4(t3)");
  
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
