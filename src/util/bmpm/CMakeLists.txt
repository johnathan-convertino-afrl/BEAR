################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(BMPM_UTIL_SRCS
  bmpm.c
  bmpm.h
)

add_library(bmpm_util ${BMPM_UTIL_SRCS})
