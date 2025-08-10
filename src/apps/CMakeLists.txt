################################################################################
### date      2024.09.18
### author    Jay Convertino
### brief     Veronica Vexriscv examples
################################################################################

cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps)
endif()

link_libraries(bare_metal_boot irq)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -std=c99 -Os -g -Wall -Wextra -ffunction-sections ")

include_directories(
  ${CMAKE_SOURCE_DIR}/src/drivers/
  ${CMAKE_SOURCE_DIR}/src/util/
)
function(gen_target_binary TARGET_NAME)
  get_filename_component(TARGET_NAME_WE ${TARGET_NAME} NAME_WE)

  file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)

  # Post processing command to create a disassembly file
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
          COMMAND ${CMAKE_OBJDUMP} -S  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME} > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin/${TARGET_NAME_WE}.disasm
          COMMENT "Invoking: Disassemble")

  # Post processing command to create a hex file
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
          COMMAND ${CMAKE_OBJCOPY} -O ihex  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin/${TARGET_NAME_WE}.hex
          COMMENT "Invoking: Hex dump")

  # Post processing command to create a binary file
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
          COMMAND ${CMAKE_OBJCOPY} -O binary  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin/${TARGET_NAME_WE}.bin
          COMMENT "Invoking: Binary dump")
endfunction()

if(BUILD_UART_EXAMPLES)
  #uart echo, polling method.
  add_executable(uart_echo.elf uart_echo.c)
  target_link_libraries(uart_echo.elf PRIVATE uart_drv)

  gen_target_binary(uart_echo.elf)

  #uart echo, irq method
  add_executable(uart_echo_irq.elf uart_echo_irq.c)
  target_link_libraries(uart_echo_irq.elf PRIVATE uart_drv plic_drv clint_drv)

  gen_target_binary(uart_echo_irq.elf)

endif()

if(BUILD_GPIO_EXAMPLES)
  #gpio led increment, irq method
  add_executable(led_gpio_timer_irq.elf led_gpio_timer_irq.c)
  target_link_libraries(led_gpio_timer_irq.elf PRIVATE gpio_drv plic_drv clint_drv uart_drv)

  gen_target_binary(led_gpio_timer_irq.elf)

endif()

if(BUILD_PMP_EXAMPLES)
  #gpio led increment, irq method
  add_executable(pmp_write_lock_read.elf pmp_write_lock_read.c)
  target_link_libraries(pmp_write_lock_read.elf PRIVATE plic_drv clint_drv uart_drv)

  gen_target_binary(pmp_write_lock_read.elf)

endif()

if(BUILD_SDCARD_EXAMPLES)
  add_executable(sdcard_raw_read.elf sdcard_raw_read.c)
  target_link_libraries(sdcard_raw_read.elf PRIVATE uart_drv sdcard_spi_util spi_drv)

  gen_target_binary(sdcard_raw_read.elf)
  
  add_executable(sdcard_fatfs_read.elf sdcard_fatfs_read.c)
  target_link_libraries(sdcard_fatfs_read.elf PRIVATE uart_drv fatfs_util sdcard_spi_util spi_drv)

  gen_target_binary(sdcard_fatfs_read.elf)

endif()

if(BUILD_SPI_EXAMPLES)
  add_executable(spi_echo.elf spi_echo.c)
  target_link_libraries(spi_echo.elf PRIVATE uart_drv spi_drv)

  gen_target_binary(spi_echo.elf)

endif()

message(STATUS "Applications selected to build:")

get_property(target_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

foreach(app_name ${target_names})
  message(STATUS "* ${app_name}")
endforeach(app_name ${target_names})

set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)
