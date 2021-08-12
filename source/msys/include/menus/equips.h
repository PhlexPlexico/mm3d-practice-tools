#pragma once

#include "msys/include/menu.h"

namespace msys {
extern Menu EquipsMenu;

typedef enum {
  EQUIP_BUTTON_B = 0,
  EQUIP_BUTTON_Y,
  EQUIP_BUTTON_X,
  EQUIP_BUTTON_I,
  EQUIP_BUTTON_II,
} EquipButtons;
}  // namespace msys
