################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(FATFS_UTIL_SRCS
  source/diskio.h
  source/pff.c
  source/pff.h
  source/pffconf.h
)

add_library(fatfs_util ${FATFS_UTIL_SRCS})
