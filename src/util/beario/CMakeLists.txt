################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

get_target_property(LIB_INCLUDES uart_drv INCLUDE_DIRECTORIES)

include_directories(
  ${LIB_INCLUDES}
  ${CMAKE_SOURCE_DIR}/src/util/beario
)

set(BEARIO_UTIL_SRCS
  beario.c
  beario.h
)

add_library(beario_util ${BEARIO_UTIL_SRCS})
target_link_libraries(beario_util PUBLIC uart_drv)
