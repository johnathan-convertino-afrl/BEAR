################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

if(BUILD_BOOT_LOADER)
  set(BARE_METAL_STARTUP zebbs-startup.c)
else()
  set(BARE_METAL_STARTUP apps-startup.c)
endif()

list(APPEND BARE_METAL_STARTUP syscalls.c)

add_library(bare_metal_startup OBJECT ${BARE_METAL_STARTUP})
