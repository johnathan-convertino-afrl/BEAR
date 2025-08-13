################################################################################
### date      2025.07.17
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/spi/
)

set(SPI_DRV_SRCS
  spi.h
)

if(ALTERA_DRV_SPI)
  list(APPEND SPI_DRV_SRCS src/altera/spi.c src/altera/spi_map.h)
  
  include_directories(
    ${CMAKE_SOURCE_DIR}/src/drivers/spi/src/altera
  )
endif()

add_library(spi_drv ${SPI_DRV_SRCS})
