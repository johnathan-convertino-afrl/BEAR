################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

include_directories(
  .
  ${CMAKE_SOURCE_DIR}/src/util/
)

if(BOOTLOADER)
  set(BARE_METAL_STARTUP zebbs-startup.c zebbs-syscalls.c)
else()
  set(BARE_METAL_STARTUP apps-startup.c app-syscalls.c)
endif()

list(APPEND BARE_METAL_STARTUP dev_init.c)

add_library(bare_metal_startup OBJECT ${BARE_METAL_STARTUP})
target_link_libraries(bare_metal_startup PRIVATE fatfs_util uart_drv)
