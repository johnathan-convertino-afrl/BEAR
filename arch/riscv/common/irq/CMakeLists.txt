################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(IRQ_SRCS
  riscv-irq.h
  vector-table.c
  vector-table.h
)

add_library(irq ${IRQ_SRCS})
