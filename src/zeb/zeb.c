#include <base.h>
#include <riscv-csr.h>

#include <uart/uart.h>
#include <plic/plic.h>
#include <clint/clint.h>
#include <irq/vector-table.h>

#include <stdint.h>
#include <stdlib.h>

#define UART_ADDR   0x44A10000
#define PLIC_ADDR   0x0C000000
#define CLINT_ADDR  0x02000000

//CPU CLOCK FREQ, USED FOR CLINT CALC INLINE FUNCTIONS
#define CPU_FREQ_HZ 50000000

struct s_uart *gp_uart;
struct s_plic *gp_plic;
struct s_clint *gp_clint;

static volatile uint64_t ecall_count = 0;

// Global to hold current timestamp, written in MTI handler.
static volatile uint64_t timestamp = 0;

static volatile uint64_t wtf_count = 0;

int main()
{
  gp_plic  = initPlic(PLIC_ADDR);
  gp_uart  = initUart(UART_ADDR);
  gp_clint = initClint(CLINT_ADDR);

  // init machine mvtec and enable machine irqs.
  init_machine_irq();

  // setup plic to enable interrupt 4, uart.
  gp_plic->priority4 = 7;

  gp_plic->threshold = 0;

  gp_plic->enable1.bits.i4 = 1;

  // setup uart to enable interrupts
  gp_uart->control.bits.ena_intr = 1;

  // Setup timer for 1 second interval
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpSeconds(CPU_FREQ_HZ, 1));

  for(;;)
  {
    // Wait for timer interrupt
    __asm__ volatile ("wfi");
    // Try a synchronous exception.
    __asm__ volatile ("ecall");
  }

  return 0;
}

#pragma GCC push_options
// Force the alignment for mtvec.BASE. A 'C' extension program could be aligned to to bytes.
#pragma GCC optimize ("align-functions=4")
// The 'riscv_mtvec_mei' function is added to the vector table by the vector_table.c
void riscv_mtvec_mei(void)
{
  uint32_t claim_num = 0;

  claim_num = gp_plic->claim;

  if(gp_uart->status.bits.rx_fifo_valid && gp_uart->status.bits.intr_ena)
  {
    uint8_t temp;

    temp = getUartRxData(gp_uart);

    setUartTxData(gp_uart, temp);
  }

  gp_plic->claim = claim_num;
}

// The 'riscv_mtvec_mti' function is added to the vector table by the vector_table.c
void riscv_mtvec_mti(void)
{
  // Timer exception, re-program the timer for a one second tick.
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpSeconds(CPU_FREQ_HZ, 1));
}
// The 'riscv_mtvec_exception' function is added to the vector table by the vector_table.c
// This function looks at the cause of the exception, if it is an 'ecall' instruction then increment a global counter.
void riscv_mtvec_exception(void)
{
  uint_xlen_t this_cause = csr_read_mcause();
  uint_xlen_t this_pc    = csr_read_mepc();

  //uint_xlen_t this_value = csr_read_mtval();
  switch (this_cause)
  {
    case RISCV_EXCP_ENVIRONMENT_CALL_FROM_M_MODE:
      ecall_count++;
      // Make sure the return address is the instruction AFTER ecall
      csr_write_mepc(this_pc+4);
      break;
    default:
      wtf_count++;
      break;
  }
}

#pragma GCC pop_options
