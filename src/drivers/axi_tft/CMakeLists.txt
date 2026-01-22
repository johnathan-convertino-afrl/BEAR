################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/axi_tft
)

set(AXI_TFT_DRV_SRCS
  axi_tft.h
)

if(XILINX_DRV_AXI_TFT)
  list(APPEND AXI_TFT_DRV_SRCS src/xilinx/axi_tft.c src/xilinx/axi_tft_map.h)
  
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/drivers/axi_tft/src/xilinx/
  )
endif()

add_library(axi_tft_drv ${AXI_TFT_DRV_SRCS})

get_target_property(LIB_INCLUDES axi_tft_drv INCLUDE_DIRECTORIES)

target_include_directories(axi_tft_drv PUBLIC ${LIB_INCLUDES})
