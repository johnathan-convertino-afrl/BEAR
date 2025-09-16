################################################################################
### date      2024.09.18
### author    Jay Convertino
################################################################################

cmake_minimum_required(VERSION 3.14)

add_subdirectory(drivers)
add_subdirectory(util)

if(BOOTLOADER)
  add_subdirectory(zebbs)
else()
  add_subdirectory(apps)
endif()

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
