################################################################################
### date      2026.05.21
### author    Jay Convertino
### brief     Veronica Vexriscv DOOM for baremetal
################################################################################

cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps)
endif()

# link_libraries()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -std=c99 -ffunction-sections ")

# include_directories(
#   ${CMAKE_SOURCE_DIR}/src/drivers/
#   ${CMAKE_SOURCE_DIR}/src/util/
# )

foreach(DRIVER_LIB IN LISTS DRIVER_LIST)
  get_target_property(LIB_INCLUDES ${DRIVER_LIB} INCLUDE_DIRECTORIES)
  include_directories(${LIB_INCLUDES})
endforeach()

# set(USER_COMPILE_DEFINITIONS "NO_FILE_WRITES=1")

set(DOOM_SRCS
  am_map.h
  config.h
  deh_main.h
  deh_misc.h
  deh_str.h
  d_englsh.h
  d_event.h
  d_items.h
  d_iwad.h
  d_loop.h
  d_main.h
  d_mode.h
  doomdata.h
  doomdef.h
  doomfeatures.h
  doomgeneric.h
  doom.h
  doomkeys.h
  doomstat.h
  doomtype.h
  d_player.h
  dstrings.h
  d_textur.h
  d_think.h
  d_ticcmd.h
  f_finale.h
  f_wipe.h
  g_game.h
  hu_lib.h
  hu_stuff.h
  i_cdmus.h
  i_endoom.h
  i_joystick.h
  info.h
  i_scale.h
  i_sound.h
  i_swap.h
  i_system.h
  i_timer.h
  i_video.h
  m_argv.h
  m_bbox.h
  m_cheat.h
  m_config.h
  m_controls.h
  memio.h
  m_fixed.h
  m_menu.h
  m_misc.h
  m_random.h
  mus2mid.h
  net_client.h
  net_dedicated.h
  net_defs.h
  net_gui.h
  net_io.h
  net_loop.h
  net_packet.h
  net_query.h
  net_sdl.h
  net_server.h
  p_inter.h
  p_local.h
  p_mobj.h
  p_pspr.h
  p_saveg.h
  p_setup.h
  p_spec.h
  p_tick.h
  r_bsp.h
  r_data.h
  r_defs.h
  r_draw.h
  r_local.h
  r_main.h
  r_plane.h
  r_segs.h
  r_sky.h
  r_state.h
  r_things.h
  sha1.h
  sounds.h
  s_sound.h
  statdump.h
  st_lib.h
  st_stuff.h
  tables.h
  v_patch.h
  v_video.h
  w_checksum.h
  w_file.h
  wi_stuff.h
  w_main.h
  w_merge.h
  w_wad.h
  z_zone.h
  am_map.c
  d_event.c
  d_items.c
  d_iwad.c
  d_loop.c
  d_main.c
  d_mode.c
  d_net.c
  doomdef.c
  doomgeneric_bare_riscv.c
  doomgeneric.c
  doomstat.c
  dstrings.c
  dummy.c
  f_finale.c
  f_wipe.c
  g_game.c
  hu_lib.c
  hu_stuff.c
  i_cdmus.c
  icon.c
  i_endoom.c
  i_input.c
  i_joystick.c
  info.c
  i_scale.c
  i_sound.c
  i_system.c
  i_timer.c
  i_video.c
  m_argv.c
  m_bbox.c
  m_cheat.c
  m_config.c
  m_controls.c
  memio.c
  m_fixed.c
  m_menu.c
  m_misc.c
  m_random.c
  mus2mid.c
  p_ceilng.c
  p_doors.c
  p_enemy.c
  p_floor.c
  p_inter.c
  p_lights.c
  p_map.c
  p_maputl.c
  p_mobj.c
  p_plats.c
  p_pspr.c
  p_saveg.c
  p_setup.c
  p_sight.c
  p_spec.c
  p_switch.c
  p_telept.c
  p_tick.c
  p_user.c
  r_bsp.c
  r_data.c
  r_draw.c
  r_main.c
  r_plane.c
  r_segs.c
  r_sky.c
  r_things.c
  sha1.c
  sounds.c
  s_sound.c
  statdump.c
  st_lib.c
  st_stuff.c
  tables.c
  v_video.c
  w_checksum.c
  w_file.c
  w_file_mem_load.c
  wi_stuff.c
  w_main.c
  w_wad.c
  z_zone.c
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

add_executable(DOOM.elf ${DOOM_SRCS})
target_link_libraries(DOOM.elf PRIVATE ${DRIVER_LIST})

gen_target_binary(DOOM.elf)

message(STATUS "Applications selected to build:")

get_property(target_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

foreach(app_name ${target_names})
  message(STATUS "* ${app_name}")
endforeach(app_name ${target_names})

set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)
