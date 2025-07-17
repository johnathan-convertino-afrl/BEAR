################################################################################
### date      2025.07.17
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(SPI_DRV_SRCS
  spi.c
  spi.h
)

add_library(spi_drv ${SPI_DRV_SRCS})
