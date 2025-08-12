################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/plic
)

set(PLIC_DRV_SRCS
  plic.c
  plic.h
)

add_library(plic_drv ${PLIC_DRV_SRCS})
