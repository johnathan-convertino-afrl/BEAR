################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

#[[
find_library(LIB1 uart_drv HINTS ${CMAKE_SOURCE_DIR}/src/drivers/uart)

target_link_libraries(library2 PUBLIC LIB1)]]
# get_target_property(LIB_INCLUDES uart_drv INCLUDE_DIRECTORIES)
# 
# include_directories(
#   ${CMAKE_SOURCE_DIR}/src/drivers/uart
# )

if(BUILD_BOOT_LOADER)
  set(BARE_METAL_STARTUP zebbs-startup.c)
else()
  set(BARE_METAL_STARTUP apps-startup.c)
endif()

list(APPEND BARE_METAL_STARTUP syscalls.c dev_init.c dev_init.h global_devices.h)

add_library(bare_metal_startup OBJECT ${BARE_METAL_STARTUP})
target_link_libraries(bare_metal_startup PUBLIC uart_drv)
