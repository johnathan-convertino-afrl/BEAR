#include <base.h>
#include <riscv-csr.h>

#include <plic.h>
#include <clint.h>
#include <irq/vector-table.h>
#include <beario/beario.h>

#include <stdint.h>
#include <stdlib.h>

struct s_plic   *gp_plic;
struct s_clint  *gp_clint;
struct s_gpio   *gp_gpio;

static volatile uint64_t ecall_count = 0;

// Global to hold current timestamp, written in MTI handler.
static volatile uint64_t timestamp = 0;

static volatile uint64_t wtf_count = 0;

static volatile uint64_t seconds = 0;

static volatile uint32_t ddr_read = 0;

volatile uint32_t *DDR_START = (volatile uint32_t *)DDR_ADDR;

extern int _WFI_CALL_START, _FOR_LOOP_START, _FOR_LOOP_END;

int main()
{
  gp_plic  = initPlic(PLIC_ADDR);
  gp_clint = initClint(CLINT_ADDR);

  // init machine mvtec and enable machine irqs.
  init_machine_irq();

  *DDR_START = 0xDEADBEEF;

  //Address is right shift by 2. Region size is 2^(lszb+3) (0 is 8 bytes, 3 is 32, 011, the LSZB is 2 so 2+3 is 5.. 2^5).
  //This PMP only supports NAPOT mode, or disabled.
  csr_write_pmpaddr0((DDR_ADDR >> 2) | 0x00000003);

  //used one pmpconfig from pmpcfg0 aka pmp0cfg
  //all are 8 bits
  // 7 = lock, 4:3 = address matching mode, 2:0 = permissions
  csr_write_pmpcfg0(0x00000098);

  // Setup timer for 1 second interval
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpSeconds(CPU_FREQ_HZ, 1));

  ddr_read = *DDR_START;

  __asm__ volatile ("_FOR_LOOP_START:");

  for(;;)
  {

    *DDR_START = 0xAAAA5555;

    __asm__ volatile ("_WFI_CALL_START:");

    // Wait for timer interrupt
    __asm__ volatile ("wfi");

    // Try a synchronous exception.RISCV_EXCP_ENVIRONMENT_CALL_FROM_M_MODE
    __asm__ volatile ("ecall");

    __asm__ volatile ("_FOR_LOOP_END:");
  }

  return 0;
}

#pragma GCC push_options
// Force the alignment for mtvec.BASE. A 'C' extension program could be aligned to to bytes.
#pragma GCC optimize ("align-functions=4")

// The 'riscv_mtvec_mti' function is added to the vector table by the vector_table.c
void riscv_mtvec_mti(void)
{
  seconds++;

  // Timer exception, re-program the timer for a one second tick.
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpSeconds(CPU_FREQ_HZ, 1));

  beario_printf("TIMER TICK");
}
// The 'riscv_mtvec_exception' function is added to the vector table by the vector_table.c
// This function looks at the cause of the exception, if it is an 'ecall' instruction then increment a global counter.
void riscv_mtvec_exception(void)
{
  uint_xlen_t this_cause = csr_read_mcause();
  // uint_xlen_t this_pc    = csr_read_mepc();

  //uint_xlen_t this_value = csr_read_mtval();
  switch (this_cause)
  {
    case RISCV_EXCP_ENVIRONMENT_CALL_FROM_M_MODE:
      ecall_count++;
      // Make sure the return address is the instruction AFTER ecall
      beario_printf("ECALL FROM M MODE");
      csr_write_mepc((int)&_FOR_LOOP_END);
      break;
    case RISCV_EXCP_LOAD_ACCESS_FAULT:
      beario_printf("PMP.. READ LOCKED");
      // plus 14 since lw is done at start, an we want to skip all the other stuff
      csr_write_mepc((int)&_FOR_LOOP_START);
      break;
    case RISCV_EXCP_STORE_AMO_ACCESS_FAULT:
      beario_printf("PMP.. WRITE LOCKED");
      // plus 2, since sw is 2 bytes
      csr_write_mepc((int)&_WFI_CALL_START);
      break;
    default:
      wtf_count++;
      break;
  }
}

#pragma GCC pop_options
