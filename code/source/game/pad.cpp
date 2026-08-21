/**
 * @file pad.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/pad.h"
#include "game/addresses.h"

#include "common/utils.h"

namespace game::pad {

  ControllerMgr& GetControllerMgr() {
    return *rnd::util::GetPointer<ControllerMgr>(ADDR_GetControllerMgr_729000);
  }

}  // namespace game::pad
