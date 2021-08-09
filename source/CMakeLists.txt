cmake_minimum_required(VERSION 3.13)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(restoration C CXX ASM)

add_executable(newcode
  common/context.cpp
  common/context.h
  common/debug.cpp
  common/debug.h
  common/flags.h
  common/hidstate.h
  common/hidstate.cpp
  common/types.h
  common/utils.h
  game/actor.cpp
  game/actor.h
  game/actors/boss_goht.h
  game/actors/boss_gyorg.h
  game/actors/boss_twinmold.h
  game/actors/obj_elegy_statue.h
  game/actors/obj_stone_tower_block.h
  game/as.cpp
  game/as.h
  game/camera.cpp
  game/camera.h
  game/collision.cpp
  game/collision.h
  game/common_data.cpp
  game/common_data.h
  game/context.cpp
  game/context.h
  game/items.cpp
  game/items.h
  game/memory.cpp
  game/memory.h
  game/message.cpp
  game/message.h
  game/pad.cpp
  game/pad.h
  game/player.cpp
  game/player.h
  game/random.cpp
  game/random.h
  game/scene.h
  game/states/state.cpp
  game/states/state.h
  game/states/state_ending.h
  game/states/state_sot_save.cpp
  game/states/state_sot_save.h
  game/static_context.cpp
  game/static_context.h
  game/sound.cpp
  game/ui.cpp
  game/ui.h
  game/ui/layouts/item_icon.cpp
  game/ui/layouts/item_icon.h
  game/ui/layouts/message_window.h
  game/ui/layouts/num_all.cpp
  game/ui/layouts/num_all.h
  game/ui/layouts/play_action_icon.h
  game/ui/layouts/play_hud.h
  game/ui/message_text.cpp
  game/ui/message_text.h
  game/ui/res.cpp
  game/ui/res.h
  game/ui/screens/gear_screen.h
  game/ui/screens/main_screen.cpp
  game/ui/screens/main_screen.h
  game/ui/screens/schedule_screen.h
  game/ui/screens/screen.h
  msys/include/csvc.h
  msys/include/draw.h
  msys/include/entrances.h
  msys/include/file_functions.h
  msys/include/fmt.h
  msys/include/menu.h
  msys/include/menus.h
  msys/include/MyThread.h
  msys/include/utils.h
  msys/include/fonts/ascii_font.h
  msys/include/lib/printf.h
  msys/include/lib/string.h
  msys/include/lib/types.h
  msys/include/menus/cheats.h
  msys/include/menus/commands.h
  msys/include/menus/debug.h
  msys/include/menus/equips.h
  msys/include/menus/file.h
  msys/include/menus/inventory.h
  msys/include/menus/save.h
  msys/include/menus/scene.h
  msys/include/menus/warps.h
  msys/include/menus/watches.h
  msys/3ds/abi.cpp
  msys/3ds/draw.cpp
  msys/3ds/MyThread.cpp
  msys/cheats.cpp
  msys/commands.cpp
  msys/debug.cpp
  msys/equips.cpp
  msys/file_functions.cpp
  msys/entrances.cpp
  msys/inventory.cpp
  msys/menu.cpp
  msys/menus.cpp
  msys/save.cpp
  msys/warps.cpp
  msys/watches.cpp
  rst/fixes/obj_stone_tower_block.cpp
  rst/fixes/ocarina.cpp
  rst/main.cpp
  rst/trampolines.s
)

#Practice Patch Includes
INCLUDE(FindPackageHandleStandardArgs)
set(CTRULIB_PATHS $ENV{CTRULIB} libctru ctrulib ${DEVKITPRO}/libctru ${DEVKITPRO}/ctrulib)

find_path(LIBCTRU_INCLUDE_DIR 3ds.h
            PATHS ${CTRULIB_PATHS}
            PATH_SUFFIXES include libctru/include )

find_library(LIBCTRU_LIBRARY NAMES ctru libctru.a
            PATHS ${CTRULIB_PATHS}
            PATH_SUFFIXES lib libctru/lib )

set(LIBCTRU_LIBRARIES ${LIBCTRU_LIBRARY} )
set(LIBCTRU_INCLUDE_DIRS ${LIBCTRU_INCLUDE_DIR} )

find_package_handle_standard_args(CTRULIB  DEFAULT_MSG
LIBCTRU_LIBRARY LIBCTRU_INCLUDE_DIR)

mark_as_advanced(LIBCTRU_INCLUDE_DIR LIBCTRU_LIBRARY )
if(CTRULIB_FOUND)
    set(CTRULIB ${LIBCTRU_INCLUDE_DIR}/..)
    message(STATUS "setting CTRULIB to ${CTRULIB}")

    add_library(3ds::ctrulib STATIC IMPORTED GLOBAL)
    set_target_properties(3ds::ctrulib PROPERTIES
    IMPORTED_LOCATION "${LIBCTRU_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBCTRU_INCLUDE_DIR}"
)
endif()

target_link_libraries(newcode PRIVATE 3ds::ctrulib)


include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(newcode PRIVATE nlohmann_json::nlohmann_json)
#End Practice Patch Includes
set_target_properties(newcode PROPERTIES SUFFIX ".elf")
target_compile_options(newcode PRIVATE -fdiagnostics-color=always -Wall -Wno-type-limits -Wno-invalid-offsetof -Wextra -std=c++17 -fno-exceptions -fomit-frame-pointer -ffunction-sections)
target_include_directories(newcode PRIVATE ./)

target_include_directories(newcode SYSTEM PRIVATE lib/eigen/)

if (NOT DEFINED CODEADDR)
  message(FATAL_ERROR "Set CODEADDR")
endif()
target_link_options(newcode PRIVATE "-Wl,--gc-sections,-Ttext-segment=${CODEADDR}")
add_custom_target(newcode_product ALL
  DEPENDS newcode
  COMMAND ${CMAKE_OBJCOPY} -O binary newcode.elf newcode.bin
  COMMAND sh -c "${CMAKE_OBJDUMP} -t newcode.elf>newcode.sym"
  BYPRODUCTS newcode.bin newcode.sym
)
