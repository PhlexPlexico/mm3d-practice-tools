#include "common/input.h"
#include "hid.h"
#include "common/utils.h"
extern "C" {
#include <3ds/svc.h>
}
namespace rnd {
  /// Fold in the inputs raw shared HID cannot report: ZL, ZR and the C-stick
  /// from the extended pad, and the circle pad as directions.
  static u32 MergeIrPad(u32 pad) {
    const ir_pad_state_t& ir = *util::GetPointer<ir_pad_state_t>(ADDR_IrPadState);

    /*
     * Not gated on a device-present flag. ir_hid_thread zeroes `held` when
     * there is no extended pad, so there is nothing to guard against -- and the
     * byte at 0x15 this used to test is 0 on a New 3DS, where ZL, ZR and the
     * C-stick are built in rather than coming from a Circle Pad Pro. Testing it
     * meant none of them were ever reported.
     */
    pad |= ir.held & IR_PAD_EXTRA_MASK;

    // Sticks report an analogue position but no direction, so derive one. Far
    // enough from centre to be deliberate, close enough to not need a shove.
    const s16 threshold = 40;
    const cp_t cp = real_hid->pad.pads[real_hid->pad.index].cp;
    if (cp.x > threshold)
      pad |= CPAD_RIGHT;
    if (cp.x < -threshold)
      pad |= CPAD_LEFT;
    if (cp.y > threshold)
      pad |= CPAD_UP;
    if (cp.y < -threshold)
      pad |= CPAD_DOWN;

    // The C-stick's digital bits only appear in some modes; its position is
    // always there, so treat it the same way as the circle pad.
    if (ir.cstick_x > threshold)
      pad |= CSTICK_RIGHT;
    if (ir.cstick_x < -threshold)
      pad |= CSTICK_LEFT;
    if (ir.cstick_y > threshold)
      pad |= CSTICK_UP;
    if (ir.cstick_y < -threshold)
      pad |= CSTICK_DOWN;

    return pad;
  }

  u32 GetCurrentPadState(void) {
    return MergeIrPad(real_hid->pad.pads[real_hid->pad.index].curr.val);
  }

#define HID_PAD (GetCurrentPadState())

  InputContext rInputCtx = {};

  void Input_Update() {
    rInputCtx.cur.val = MergeIrPad(real_hid->pad.pads[real_hid->pad.index].curr.val);
    rInputCtx.pressed.val = (rInputCtx.cur.val) & (~rInputCtx.old.val);
    rInputCtx.up.val = (~rInputCtx.cur.val) & (rInputCtx.old.val);
    rInputCtx.old.val = rInputCtx.cur.val;
    rInputCtx.cp_curr = real_hid->pad.pads[real_hid->pad.index].cp;
  }

  u32 buttonCheck(u32 key) {
    for (u32 i = 0x26000; i > 0; i--) {
      if (key != MergeIrPad(real_hid->pad.pads[real_hid->pad.index].curr.val))
        return 0;
    }
    return 1;
  }

  u32 Input_WaitWithTimeout(u32 msec, u32 closingButton) {
    u32 pressedKey = 0;
    u32 key = 0;
    u32 n = 0;
    u32 startingButtonState = HID_PAD;

    // Wait for no keys to be pressed
    while (HID_PAD && (msec == 0 || n <= msec)) {
      svcSleepThread(reinterpret_cast<s64>(1 * 1000 * 1000LL));
      n++;

      // If the player presses the closing button while still holding other buttons, the menu closes
      // (useful for buffering);
      u32 tempButtons = HID_PAD;
      if (tempButtons != startingButtonState && buttonCheck(tempButtons)) {
        if (tempButtons & closingButton) {
          break;
        } else {
          startingButtonState = tempButtons;
        }
      }
    }

    if (msec != 0 && n >= msec) {
      return 0;
    }

    do {
      // Wait for a key to be pressed
      while (!HID_PAD && (msec == 0 || n < msec)) {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
      }

      if (msec != 0 && n >= msec) {
        return 0;
      }

      key = HID_PAD;

      // Make sure it's pressed
      pressedKey = buttonCheck(key);
    } while (!pressedKey);

    return key;
  }

  u32 Input_Wait(void) {
    return Input_WaitWithTimeout(0, 0);
  }
}  // namespace rnd
