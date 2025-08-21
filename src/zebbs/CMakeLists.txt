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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -std=c99 -Os -g -Wall -Wextra -ffunction-sections ")

foreach(DRIVER_LIB IN LISTS DRIVER_LIST)
  get_target_property(LIB_INCLUDES ${DRIVER_LIB} INCLUDE_DIRECTORIES)
  include_directories(${LIB_INCLUDES})
endforeach()

set(BOOT_LIST
  zebbs
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

foreach(boot_name IN LISTS BOOT_LIST)
  add_executable(${boot_name}.elf ${boot_name}.c)
  target_link_libraries(${boot_name}.elf PRIVATE ${DRIVER_LIST})
  
  gen_target_binary(${boot_name}.elf)
endforeach()

message(STATUS "BOOT LOADER selected for build:")

get_property(target_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

foreach(boot_name ${target_names})
  message(STATUS "* ${boot_name}")
endforeach(boot_name ${target_names})

set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)
