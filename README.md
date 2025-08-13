# FPGA baremetal example apps and zero stage bootloader (zeb)
# Currently a RISCV32 only C based set of libraries for baremetal examples. Designed to target multiple architectures in the future.

author: Jay Convertino  

date: 2024.10.02

license: MIT

## Release Versions
### Current
  - v0.0.0

### Past
  - none

## Info

  This setup uses the fiveembedded gcc startup and other support files to create the baremetal system. I've simply intergrated
  them with my cmake setup and added examples.
  
## Requirements (Ubuntu 24.04)

## Recommended
  
## Building
  1. mkdir build
  2. cd build
  3. cmake ../
  4. make

## Cmake options
  All applications are build OR the zero stage bootloader is built.
  - cmake ../  -DCMAKE_TOOLCHAIN_FILE=../arch/riscv/veronica/riscv.cmake
