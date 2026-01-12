################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

if(EXISTS ${RISCV_GCC_COMPILER})
  add_subdirectory(plic)
  add_subdirectory(clint)
endif()

if(XILINX_DRV_UART)
  add_subdirectory(uart)
endif()

if(XILINX_DRV_GPIO)
  add_subdirectory(gpio)
endif()

if(ALTERA_DRV_SPI)
  add_subdirectory(spi)
endif()

if(XILINX_DRV_AXI_TFT)
  add_subdirectory(axi_tft)
endif()
