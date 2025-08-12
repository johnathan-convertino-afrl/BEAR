################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

if(EXISTS ${RISCV_GCC_COMPILER})
  add_subdirectory(common)
  
  if(PLATFORM_VERONICA)
    add_subdirectory(veronica)
  endif()

  if(PLATFORM_WALLY)
    add_subdirectory(wally)
  endif()
endif()
