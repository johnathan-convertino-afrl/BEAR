################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/clint
)

set(CLINT_DRV_SRCS
  clint.c
  clint.h
)

add_library(clint_drv ${CLINT_DRV_SRCS})
