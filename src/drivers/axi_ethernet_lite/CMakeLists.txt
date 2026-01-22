################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/axi_ethernet_lite
)

set(AXI_ETHERNET_LITE_DRV_SRCS
  axi_ethernet_lite.h
)

if(XILINX_DRV_AXI_ETHERNET_LITE)
  list(APPEND AXI_ETHERNET_LITE_DRV_SRCS src/xilinx/axi_ethernet_lite.c src/xilinx/axi_ethernet_lite_map.h)
  
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/drivers/axi_ethernet_lite/src/xilinx/
  )
endif()

add_library(axi_ethernet_lite_drv ${AXI_ETHERNET_LITE_DRV_SRCS})

get_target_property(LIB_INCLUDES axi_ethernet_lite_drv INCLUDE_DIRECTORIES)

target_include_directories(axi_ethernet_lite_drv PUBLIC ${LIB_INCLUDES})
