################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(YXML_UTIL_SRCS
  yxml.c
  yxml.h
)

add_library(yxml_util ${YXML_UTIL_SRCS})
