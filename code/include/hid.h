/*
 * From n3rdswithgame, who may or may not have originally written this
 */

#pragma once
#include <stddef.h>
#include <stdint.h>

typedef union {
  uint32_t val;
  struct {
    uint32_t a : 1;         // 1
    uint32_t b : 1;         // 2
    uint32_t sel : 1;       // 3
    uint32_t strt : 1;      // 4
    uint32_t d_right : 1;   // 5
    uint32_t d_left : 1;    // 6
    uint32_t d_up : 1;      // 7
    uint32_t d_down : 1;    // 8
    uint32_t r : 1;         // 9
    uint32_t l : 1;         // 10
    uint32_t x : 1;         // 11
    uint32_t y : 1;         // 12
    uint32_t gpio : 2;      // 14
    uint32_t padding : 14;  // 28
    uint32_t c_right : 1;   // 29
    uint32_t c_left : 1;    // 30
    uint32_t c_up : 1;      // 31
    uint32_t c_down : 1;    // 32
  };
} btn_t;

typedef union {
  uint32_t val;
  struct {
    int16_t x;
    int16_t y;
  };
} cp_t;

typedef struct {
  btn_t curr;
  btn_t pressed;
  btn_t released;
  cp_t cp;
} pad_t;

struct hid_pad_t {
  uint64_t timestamp;       // 0
  uint64_t timestamp_last;  // 8
  uint32_t index;           // 10
  uint32_t pad_14[2];       // 14
  btn_t btn_raw;            // 1c
  cp_t cp_raw;              // 20
  uint8_t pad_24;           // 24
  pad_t pads[8];
};

struct touch_input_t {
  int16_t x;
  int16_t y;
};

typedef struct {
  struct touch_input_t touch;
  uint32_t updated;
} touch_t;

struct hid_touch_t {
  uint64_t timestamp;       // 0
  uint64_t timestamp_last;  // 8
  uint32_t index;           // 10
  uint32_t pad_14;          // 14
  touch_t raw;
  touch_t touches[8];
};

typedef struct {
  struct hid_pad_t pad;
  struct hid_touch_t touch;
} hid_mem_t;

/*
 * Layout taken from ir_hid_thread (0x1CAE2C), which is what fills this in. The
 * previous version of this struct was missing `pressed`, so everything from
 * offset 0x0C on was wrong by four bytes.
 *
 * ZL, ZR and the C-stick appear in `held` at the libctru bit positions. When no
 * extended pad is present the thread stores 0 there, so it can be read without
 * first checking for a device.
 */
typedef struct {
  int16_t cp_x, cp_y;          // 0x00
  int16_t cstick_x, cstick_y;  // 0x04
  uint32_t held;               // 0x08
  uint32_t pressed;            // 0x0C
  uint32_t released;           // 0x10
  uint8_t cstick_mode;         // 0x14
  uint8_t field_15;            // 0x15
} ir_pad_state_t;
#ifdef __cplusplus
static_assert(offsetof(ir_pad_state_t, held) == 0x08);
static_assert(offsetof(ir_pad_state_t, cstick_mode) == 0x14);
#endif

typedef struct {
  uint32_t field_00;
  struct hid_pad_t* hid_pad;
  uint32_t field_08;
  struct hid_touch_t* hid_touch;
  uint32_t field_10;
  uint32_t* hid_accl;  // need to add
  uint32_t field_18;
  uint32_t field_1c;
  uint32_t* hid_gyro;  // need to add
  uint32_t field_24;
  uint32_t* hid_debug;             // might add
  uint32_t mappable_mem_chunk[4];  // need to add
  uint32_t bool_3c;
  uint32_t hid_handle;
  uint32_t bool_44;
} hid_ctx_t;

#define real_ir_pad_addr 0x007C1490
#define real_ir_pad (*(volatile ir_pad_state_t*)real_ir_pad_addr)

// ZL | ZR | C-stick direction bits — the only bits raw HID can never supply.
#define IR_PAD_EXTRA_MASK 0x0F00C000

// Unsigned: CPAD_DOWN is bit 31, and (1 << 31) as a signed int overflows.
#define BUTTON_A (1u << 0)
#define BUTTON_B (1u << 1)
#define BUTTON_SELECT (1u << 2)
#define BUTTON_START (1u << 3)
#define BUTTON_RIGHT (1u << 4)
#define BUTTON_LEFT (1u << 5)
#define BUTTON_UP (1u << 6)
#define BUTTON_DOWN (1u << 7)
#define BUTTON_R1 (1u << 8)
#define BUTTON_L1 (1u << 9)
#define BUTTON_X (1u << 10)
#define BUTTON_Y (1u << 11)
#define BUTTON_ZL (1u << 14)
#define BUTTON_ZR (1u << 15)
#define CSTICK_RIGHT (1u << 24)
#define CSTICK_LEFT (1u << 25)
#define CSTICK_UP (1u << 26)
#define CSTICK_DOWN (1u << 27)
#define CPAD_RIGHT (1u << 28)
#define CPAD_LEFT (1u << 29)
#define CPAD_UP (1u << 30)
#define CPAD_DOWN (1u << 31)
