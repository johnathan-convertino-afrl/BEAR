/*
   Register access functions for RISC-V system registers.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

*/

#ifndef RISCV_BASE_H
#define RISCV_BASE_H

#include <stdint.h>

#define UART_ADDR   0x44A10000
#define SPI_ADDR    0x44A20000
#define GPIO_ADDR   0x44A00000
#define PLIC_ADDR   0x0C000000
#define CLINT_ADDR  0x02000000

static inline void delay(uint32_t len) {

  uint32_t index = 0;

  for(index = 0; index < len; index++)
  {
    __asm__ volatile ("nop");
  }
}

#endif // #define RISCV_BASE_H
