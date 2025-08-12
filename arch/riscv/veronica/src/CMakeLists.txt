################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(BARE_METAL_BASE
  base.h
  riscv-csr.h
)

add_library(bare_metal_base OBJECT ${BARE_METAL_BASE})
