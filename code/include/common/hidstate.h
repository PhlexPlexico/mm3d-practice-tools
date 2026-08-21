#pragma once

#include "common/input.h"
#include "game/actor.h"

namespace rnd {

  struct AdvanceState {
    typedef enum { NORMAL = 0, PAUSED, STEP, LATCHED } frame_state_t;
    struct {
      frame_state_t advance_state = NORMAL;
      u8 d_down_latched;
      game::act::PosRot storedPos;
      u16 storedAngle;
    } advance_ctx_t;
    bool pauseUnpause = false;
    bool frameAdvance = false;
    bool menuExitFlag = false;
    bool showWatches = false;
    bool useISG = false;
    /// One bit per InfiniteItem; the counts are topped up every frame.
    u32 infiniteItems = 0;
  };

  AdvanceState& GetAdvState();

}  // namespace rnd
