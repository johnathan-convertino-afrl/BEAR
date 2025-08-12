################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/uart/
)

set(UART_DRV_SRCS
  uart.h
)

if(XILINX_DRV_UART)
  list(APPEND UART_DRV_SRCS src/xilinx/uart.c src/xilinx/uart_map.h)
  
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/drivers/uart/src/xilinx
  )
endif()

add_library(uart_drv ${UART_DRV_SRCS})
