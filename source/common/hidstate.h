#pragma once

#include "common/types.h"
#define real_hid_addr   0x10002000

namespace rst {
struct AdvanceState {
    typedef enum {
        NORMAL = 0,
        PAUSED,
        STEP,
        LATCHED
    } frame_state_t;
    struct{
    frame_state_t advance_state = NORMAL;
    u8 d_down_latched;
    } advance_ctx_t;
};

extern "C" void svcSleepThread(u64);
AdvanceState& GetAdvState();
} // namespace rst

