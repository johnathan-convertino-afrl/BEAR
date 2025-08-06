################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

## APPLICATIONS
if(BUILD_EXAMPLES_ALL)
  set(BUILD_UART_EXAMPLES ON)
  set(BUILD_GPIO_EXAMPLES ON)
  set(BUILD_PMP_EXAMPLES ON)
  set(BUILD_SDCARD_EXAMPLES ON)
  set(BUILD_SPI_EXAMPLES ON)
  set(BUILD_DRV_ALL ON)
  set(BUILD_UTIL_ALL ON)
else()
  set(BUILD_EXAMPLES_ALL OFF)
endif()

if(BUILD_UART_EXAMPLES)
  set(BUILD_DRV_UART ON)
endif()

if(BUILD_SPI_EXAMPLES)
  set(BUILD_DRV_UART ON)
  set(BUILD_DRV_SPI ON)
endif()

if(BUILD_GPIO_EXAMPLES)
  set(BUILD_DRV_GPIO ON)
  set(BUILD_DRV_UART ON)
endif()

if(BUILD_PMP_EXAMPLES)
  set(BUILD_DRV_UART ON)
endif()

if(BUILD_SDCARD_EXAMPLES)
  set(BUILD_UTIL_SDCARD_SPI ON)
  set(BUILD_DRV_UART ON)
  set(BUILD_DRV_SPI ON)
  set(BUILD_UTIL_FATFS OFF)
endif()

## DRIVERS
if(NOT DEFINED BUILD_DRV_ALL)
  set(BUILD_DRV_ALL OFF)
else()
  set(BUILD_DRV_UART ON)
  set(BUILD_DRV_GPIO ON)
  set(BUILD_DRV_SPI ON)
endif()

if(NOT DEFINED BUILD_DRV_UART)
  set(BUILD_DRV_UART OFF)
endif()

if(NOT DEFINED BUILD_DRV_GPIO)
  set(BUILD_DRV_GPIO OFF)
endif()

if(NOT DEFINED BUILD_UTIL_SDCARD_SPI)
  set(BUILD_UTIL_SDCARD_SPI OFF)
endif()

## UTILITY
if(NOT DEFINED BUILD_UTIL_ALL)
  set(BUILD_UTIL_ALL OFF)
else()
  set(BUILD_UTIL_FATFS ON)
  set(BUILD_UTIL_SDCARD_SPI ON)
endif()

if(NOT DEFINED BUILD_UTIL_FATFS)
  set(BUILD_UTIL_FATFS OFF)
endif()

add_subdirectory(apps)
add_subdirectory(drivers)
add_subdirectory(util)

if(CREATE_DOXYGEN)
  find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)

  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_MAN NO)
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doxygen)
  set(DOXYGEN_PROJECT_NAME DSP_NODE)
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  set(DOXYGEN_QUIET YES)
  set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)

  if(DOXYGEN_FOUND)
    doxygen_add_docs(doxygen ${CMAKE_CURRENT_SOURCE_DIR} ALL)
  endif()

endif()
