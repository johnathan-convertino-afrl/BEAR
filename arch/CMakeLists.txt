################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

if(EXISTS ${RISCV_GCC_COMPILER})
  add_subdirectory(riscv)
endif()
