################################################################################
### date      2025.07.17
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(SDCARD_SPI_UTIL_SRCS
  sdcard_spi.c
  sdcard_spi.h
)

add_library(sdcard_spi_util ${SDCARD_SPI_UTIL_SRCS})
