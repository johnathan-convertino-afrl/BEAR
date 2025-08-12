################################################################################
### date      2024.09.18
### author    Jay Convertino
### brief     cmake for Veronica Vexriscv Examples
################################################################################

cmake_minimum_required(VERSION 3.14)

project(veronica_examples LANGUAGES C ASM )

if(!CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr/local/" CACHE PATH "..." FORCE)
endif()

add_subdirectory(arch)
add_subdirectory(src)

