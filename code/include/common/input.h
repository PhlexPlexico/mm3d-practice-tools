#pragma once

#include "common/types.h"
#include "game/addresses.h"
#include "hid.h"

namespace rnd {

  typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
    cp_t cp_curr;
  } InputContext;

// The game's shared HID block; the pointer to it sits four bytes in.
#define real_hid (*(hid_mem_t**)(ADDR_SharedHidBlock + 4))

  extern "C" InputContext rInputCtx;

  /// Pad state with the IR pad's ZL/ZR and C-stick merged in, and the circle
  /// pad reported as directions. Raw HID alone reports none of those.
  u32 GetCurrentPadState(void);

  void Input_Update(void);
  u32 Input_WaitWithTimeout(u32 msec, u32 closingButton);
  u32 Input_Wait(void);

}  // namespace rnd
