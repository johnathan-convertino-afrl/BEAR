# BEAR
## Baremetal Examples and Apps for RISCV
### Currently a RISCV32 only C based set of libraries for baremetal examples and zerostage bootloader. Designed to target multiple architectures in the future.
---

author: Jay Convertino  

date: 2024.10.02  

license: MIT  

---

## Release Versions
### Current
  - v0.0.0

### Past
  - none

## Info

  This setup uses the fiveembedded gcc startup and other support files to create the baremetal system. I've simply intergrated
  them with my cmake setup and added examples.
  
### Requirements (Ubuntu 24.04)
  
### Building example for Veronica
  1. mkdir build
  2. cd build
  3. cmake ../ -DCMAKE_TOOLCHAIN_FILE=../arch/riscv/veronica/riscv.cmake
  4. make

### Cmake options
  All applications are build OR the zero stage bootloader is built. The -DBOOTLOADER option will only build the zerostage bootloader (ZEBBS). Without it all apps will build WITHOUT the bootloader.
  
  - cmake ../  -DCMAKE_TOOLCHAIN_FILE=../arch/riscv/veronica/riscv.cmake
  - cmake ../  -DBOOTLOADER=ON -DCMAKE_TOOLCHAIN_FILE=../arch/riscv/veronica/riscv.cmake
