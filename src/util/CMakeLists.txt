################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

add_subdirectory(beario)

if(BUILD_UTIL_SDCARD_SPI)
  add_subdirectory(sdcard_spi)
endif()

if(BUILD_UTIL_FATFS)
  add_subdirectory(pff3a)
endif()
