################################################################################
### date      2024.09.18
### author    Jay Convertino
### brief     Veronica Vexriscv examples
################################################################################

cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps)
endif()

# link_libraries()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -std=c99 -g -Wall -Wextra -ffunction-sections ")

# include_directories(
#   ${CMAKE_SOURCE_DIR}/src/drivers/
#   ${CMAKE_SOURCE_DIR}/src/util/
# )

foreach(DRIVER_LIB IN LISTS DRIVER_LIST)
  get_target_property(LIB_INCLUDES ${DRIVER_LIB} INCLUDE_DIRECTORIES)
  include_directories(${LIB_INCLUDES})
endforeach()

set(APP_LIST
  led_gpio_timer_irq
  pmp_write_lock_read
  sdcard_fatfs_read
  sdcard_raw_read
  spi_echo
  uart_echo_irq
  uart_echo
  axi_tft_write
  axi_tft_sdcard_fatfs_read_bitmap
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

foreach(app_name IN LISTS APP_LIST)
  add_executable(${app_name}.elf ${app_name}.c)
  target_link_libraries(${app_name}.elf PRIVATE ${DRIVER_LIST})
  
  gen_target_binary(${app_name}.elf)
endforeach()

message(STATUS "Applications selected to build:")

get_property(target_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

foreach(app_name ${target_names})
  message(STATUS "* ${app_name}")
endforeach(app_name ${target_names})

set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)
