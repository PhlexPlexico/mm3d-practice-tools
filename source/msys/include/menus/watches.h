#pragma once

#include "msys/include/menu.h"

#define WATCHES_MAX 15
#define WATCHES_MAXNAME 6

namespace msys {
typedef enum {
  S8 = 0,
  U8,
  X8,
  S16,
  U16,
  X16,
  S32,
  U32,
  X32,
  F32,
} WatchType;

// Special behavior for WatchType++
inline WatchType operator++(WatchType& c, int) {
  c = (c == WatchType::F32) ? WatchType::S8 : WatchType(int(c) + 1);
  return c;
}

typedef struct Watch {
  WatchType type;
  u32 posX;
  u32 posY;
  void* addr;
  u8 display;  // whether to display on bottom screen
  char name[WATCHES_MAXNAME + 1];
} Watch;

extern Watch watches[WATCHES_MAX];

void WatchesMenuFunc(void);
void Watches_ToggleWatches(void);
void drawWatches();
void toggleWatches();
void Watches_Init();
}  // namespace msys
