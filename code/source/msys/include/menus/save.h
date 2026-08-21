#pragma once
extern "C" {
  #include <3ds/types.h>
}
#include "msys/include/menu.h"
#include "msys/include/draw.h"
#include "game/common_data.h"
#include "msys/include/file_functions.h"
#include "msys/include/menus/commands.h"
#include "msys/include/entrances.h"
#include "game/actor.h"
#include "common/advanced_context.h"

namespace msys {
    /// Finish a memfile load once the scene has come back up.
    void Save_ApplyPendingMomentum(void);
  extern Menu SaveMenu;

}
