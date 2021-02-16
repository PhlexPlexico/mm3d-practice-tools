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
extern "C" void advance_main();
AdvanceState& GetAdvState();
} // namespace rst

typedef union {
    s32 val;
    struct {
        u32       a :  1; //1
        u32       b :  1; //2
        u32     sel :  1; //3
        u32    strt :  1; //4
        u32 d_right :  1; //5
        u32  d_left :  1; //6
        u32    d_up :  1; //7
        u32  d_down :  1; //8
        u32       r :  1; //9
        u32       l :  1; //10
        u32       x :  1; //11
        u32       y :  1; //12
        u32    gpio :  2; //14
        u32 padding : 14; //28
        u32 c_right :  1; //29
        u32  c_left :  1; //30
        u32    c_up :  1; //31
        u32  c_down :  1; //32
    };
} btn_t;

typedef union {
    s32 val;
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
    uint64_t timestamp;         // 0
    uint64_t timestamp_last;    // 8
    u32 index;             //10
    u32 pad_14[2];         //14
    btn_t btn_raw;              //1c
    cp_t cp_raw;                //20
    uint8_t pad_24;             //24
    pad_t pads[8];
};

struct touch_input_t {
    s16 x;
    s16 y;
};

typedef struct {
    struct touch_input_t touch;
    u32 updated;
} touch_t;

struct hid_touch_t {
    u64 timestamp;         // 0
    u64 timestamp_last;    // 8
    u32 index;             //10
    u32 pad_14;            //14
    touch_t raw;
    touch_t touches[8];
};

typedef struct  {
    struct hid_pad_t pad;
    struct hid_touch_t touch;
} hid_mem_t;

typedef struct { 
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;  
} advance_input_t;
extern advance_input_t inputs;

#define real_hid    (*(hid_mem_t *) real_hid_addr)
