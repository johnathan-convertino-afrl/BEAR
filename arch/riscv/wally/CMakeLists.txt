################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

add_subdirectory(src)

add_subdirectory(irq)

if(NOT DEFINED BUILD_BOOT_LOADER)
  set(BUILD_ALL_EXAMPLES ON)
  set(BUILD_VECTOR_IRQ OFF)
  set(BUILD_NONVECTOR_IRQ ON)
  set(BUILD_BOOT_LOADER OFF)
else()
  set(BUILD_ALL_EXAMPLES OFF)
  set(BUILD_VECTOR_IRQ OFF)
  set(BUILD_NONVECTOR_IRQ OFF)
endif()
