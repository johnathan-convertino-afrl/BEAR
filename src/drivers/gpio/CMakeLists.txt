################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/gpio
)

set(GPIO_DRV_SRCS
  gpio.h
)

if(XILINX_DRV_UART)
  list(APPEND GPIO_DRV_SRCS src/xilinx/gpio.c src/xilinx/gpio_map.h)
  
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/drivers/gpio/src/xilinx/
  )
endif()

add_library(gpio_drv ${GPIO_DRV_SRCS})
