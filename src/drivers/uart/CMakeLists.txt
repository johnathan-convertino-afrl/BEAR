################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ../uart
  )

set(UART_DRV_SRCS
  uart.h
)

if(XILINX_DRV_UART)
  list(APPEND UART_DRV_SRCS src/xilinx_uart.c)
endif()

add_library(uart_drv ${UART_DRV_SRCS})
