/*
   Register access functions for RISC-V system registers.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

*/

#ifndef __RISCV_BASE_H
#define __RISCV_BASE_H

#include <stdint.h>
        
#define PERF_ADDR_BASE  0x40000000

#define UART_ADDR     (0x04A10000 + PERF_ADDR_BASE)
#define SPI_ADDR      (0x04A20000 + PERF_ADDR_BASE)
#define GPIO_ADDR     (0x04A00000 + PERF_ADDR_BASE)
#define PLIC_ADDR     0x0C000000
#define CLINT_ADDR    0x02000000
#define DDR_ADDR      0x80000000
#define RAM_ADDR      0x08000000
#define ITIM_ADDR     0x00800000
#define ROM_ADDR      0x20010000
#define OPENSBI_START DDR_ADDR // eventually would like to do this in BRAM using SPL (MUST BE OPENSBI START IF NOT SPL)

//BUS CLOCK FREQ, USED FOR CLINT CALC INLINE FUNCTIONS
#define CPU_FREQ_HZ 50000000
#define BUS_FREQ_HZ 50000000
#define MS_DIVISOR  5000
#define US_DIVISOR  2500000

static inline void __delay(uint32_t len)
{
  volatile uint32_t index = 0;

  for(index = 0; index < len; index++)
  {
    __asm__ volatile ("nop");
  }
}

// rough approximations
static inline void __delay_ms(uint32_t len)
{
  volatile uint32_t index = 0;
  
  for(index = 0; index < len; index++)
  {
    __delay(CPU_FREQ_HZ/MS_DIVISOR);
  }
}

// rough approximations
static inline void __delay_us(uint32_t len)
{
  volatile uint32_t index = 0;
  
  for(index = 0; index < len; index++)
  {
    __delay(CPU_FREQ_HZ/US_DIVISOR);
  }
}

#endif // #define RISCV_BASE_H
