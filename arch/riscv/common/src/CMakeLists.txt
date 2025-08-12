################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

set(BARE_METAL_STARTUP
  startup.c
)

add_library(bare_metal_startup OBJECT ${BARE_METAL_STARTUP})
