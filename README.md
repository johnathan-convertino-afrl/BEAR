# FPGA baremetal examples
# Currently a RISCV only C based set of libraries for baremetal examples. Designed to target multiple architectures in the future.

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

The Following options are off by default.
  * EXAMPLE APPLICATIONS:
    - BUILD_EXAMPLES_ALL : All applications will be built
    - BUILD_UART_EXAMPLES : Build only UART applications
    - BUILD_GPIO_EXAMPLES : Build only GPIO applications
    - BUILD_PMP_EXAMPLES : Build only PMP applications
    - BUILD_SDCARD_EXAMPLES : Build only SDCARD Applications
  * DRIVERS (will automagically build for applications above)
    - BUILD_DRV_UART : Xilinx UART Lite driver
    - BUILD_DRV_GPIO : Xilinx GPIO driver
    - BUILD_DRV_SPI  : Altera SPI driver

  * UTILITIES (will automagically build for applications above)
    - BUILD_UTIL_FATFS      : Open Source FATFS file system driver for embedded systems.
    - BUILD_UTIL_SDCARD_SPI : SDCARD read/write over SPI

To turn on UART for example:
  - cmake ../ -DBUILD_UART_EXAMPLES=ON
