#pragma once

#include "msys/include/menu.h"
#include "msys/include/draw.h"
#include "game/common_data.h"
#define PZ3D_MEMFILE_MAX 3
namespace msys {
  extern Menu SaveMenu;
  typedef struct {
    u16 z3d_version;
    u16 timer_boundaries[3];
    game::SaveData file;
    u32 scene_flags[5];
    u16 scene;
  } memfile_t;
}
