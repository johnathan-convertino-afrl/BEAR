/*
   Baremetal main program with timer interrupt.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

   Tested with sifive-hifive-revb, but should not have any
   dependencies to any particular implementation.
   
*/


// Makes use of GCC interrupt and weak reference/alias attributes
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
// https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Function-Attributes.html#RISC-V-Function-Attributes

#include "vector-table.h"
#include "riscv-csr.h"

#include <stdint.h>

void init_machine_irq()
{
  // copy pasta from vector example
  // Global interrupt disable
  csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);

  csr_write_mie(0);

  // Setup the IRQ handler entry point, set the mode to vectored
  csr_write_mtvec((uint_xlen_t) riscv_mtvec_table | 0x00000001);

  // Enable MIE .. ?MIE_MTI_BIT_MASK?
  csr_write_mie(MIE_MEI_BIT_MASK | MIE_MTI_BIT_MASK | MIE_MSI_BIT_MASK);

  // Global interrupt enable
  csr_write_mstatus(MSTATUS_MPP_BIT_MASK | MSTATUS_MIE_BIT_MASK);
}

// Vector table - not to be called.
void riscv_mtvec_table(void)  __attribute__ ((naked, section(".text.mtvec_table") ,aligned(128)));
void riscv_utvec_table(void)  __attribute__ ((naked, section(".text.utvec_table") ,aligned(128)));

// Default "NOP" implementations
static void riscv_nop_machine(void)    __attribute__ ((interrupt ("machine")) );
static void riscv_nop_user(void)       __attribute__ ((interrupt ("user")) );

// Weak alias to the "NOP" implementations. If another function  
void riscv_mtvec_exception(void) __attribute__ ((interrupt ("machine")     , weak, alias("riscv_nop_machine") )); 
void riscv_mtvec_msi(void) __attribute__ ((interrupt ("machine")     , weak, alias("riscv_nop_machine") )); 
void riscv_mtvec_mti(void) __attribute__ ((interrupt ("machine")     , weak, alias("riscv_nop_machine") ));
void riscv_mtvec_mei(void) __attribute__ ((interrupt ("machine")     , weak, alias("riscv_nop_machine") ));
void riscv_mtvec_ssi(void) __attribute__ ((interrupt ("supervisor")  , weak, alias("riscv_nop_machine") ));
void riscv_mtvec_sti(void) __attribute__ ((interrupt ("supervisor")  , weak, alias("riscv_nop_machine") ));
void riscv_mtvec_sei(void) __attribute__ ((interrupt ("supervisor")  , weak, alias("riscv_nop_machine") ));

void riscv_utvec_usi(void) __attribute__ ((interrupt ("user")        , weak, alias("riscv_nop_user") ));
void riscv_utvec_uti(void) __attribute__ ((interrupt ("user")        , weak, alias("riscv_nop_user") ));
void riscv_utvec_uei(void) __attribute__ ((interrupt ("user")        , weak, alias("riscv_nop_user") ));

#pragma GCC push_options

// Ensure the vector table is aligned.
// The bottom 4 bits of MTVEC are ignored - so align to 16 bytes

// Vector table. Do not call!
// Possible entries defined by mcause table
// http://five-embeddev.com/riscv-isa-manual/latest/machine.html#sec:mcause
//
// When vectored interrupts are enabled, interrupt cause 0, which
// corresponds to user-mode software interrupts, are vectored to the
// same location as synchronous exceptions. This ambiguity does not
// arise in practice, since user-mode software interrupts are either
// disabled or delegated to user mode.
void riscv_mtvec_table(void) {
    __asm__ volatile (
        ".org  riscv_mtvec_table + 0*4;"
        "jal   zero,riscv_mtvec_exception;"  /* 0  */   
        ".org  riscv_mtvec_table + 1*4;"
        "jal   zero,riscv_mtvec_ssi;"  /* 1  */   
        ".org  riscv_mtvec_table + 3*4;"
        "jal   zero,riscv_mtvec_msi;"  /* 3  */   
        ".org  riscv_mtvec_table + 5*4;"
        "jal   zero,riscv_mtvec_sti;"  /* 5  */   
        ".org  riscv_mtvec_table + 7*4;"
        "jal   zero,riscv_mtvec_mti;"  /* 7  */   
        ".org  riscv_mtvec_table + 9*4;"
        "jal   zero,riscv_mtvec_sei;"  /* 9  */   
        ".org  riscv_mtvec_table + 11*4;"
        "jal   zero,riscv_mtvec_mei;"  /* 11 */   
        : /* output: none */                    
        : /* input : immediate */               
        : /* clobbers: none */
        );
}

// Vector table. Do not call!
void riscv_utvec_table(void) {
    __asm__ volatile (                          
        ".org  riscv_utvec_table + 0*4;"
        "jal   zero,riscv_utvec_usi;"  /* 0  */   
        ".org  riscv_utvec_table + 4*4;"
        "jal   zero,riscv_utvec_uti;"  /* 4  */   
        ".org  riscv_utvec_table + 8*4;"
        "jal   zero,riscv_utvec_uei;"  /* 8  */   
        : /* output: none */                    
        : /* input : immediate */               
        : /* clobbers: none */
        );
}

// Ensure all ISR functions are aligned.
#pragma GCC optimize ("align-functions=4")

static void riscv_nop_machine(void)  {
  // Nop machine mode interrupt.
  __asm__ volatile ("nop");
}
static void riscv_nop_user(void) {
  // Nop user mode interrupt.
  __asm__ volatile ("nop");
}

#pragma GCC pop_options

