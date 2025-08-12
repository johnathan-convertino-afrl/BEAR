################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(BARE_METAL_BOOT
  startup.c
  base.h
  riscv-csr.h
)

add_library(bare_metal_boot OBJECT ${BARE_METAL_BOOT})
