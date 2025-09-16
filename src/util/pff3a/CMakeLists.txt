################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/util/
  ${CMAKE_SOURCE_DIR}/src/drivers/
)

set(FATFS_UTIL_SRCS
  diskio.c
  diskio.h
  pff.c
  pff.h
  pffconf.h
)

add_library(fatfs_util ${FATFS_UTIL_SRCS})
target_link_libraries(fatfs_util PUBLIC sdcard_spi_util beario_util)
