################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

add_subdirectory(plic)
add_subdirectory(clint)

if(BUILD_UART_EXAMPLES OR BUILD_DRV_UART)
  add_subdirectory(uart)
endif()

if(BUILD_GPIO_EXAMPLES OR BUILD_DRV_GPIO)
  add_subdirectory(gpio)
endif()

if(BUILD_SPI_EXAMPLES OR BUILD_SDCARD_EXAMPLES OR BUILD_DRV_SPI OR BUILD_UTIL_FATFS OR BUILD_UTIL_SDCARD_SPI)
  add_subdirectory(spi)
endif()
