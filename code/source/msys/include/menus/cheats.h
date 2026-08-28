#pragma once

#include "msys/include/menu.h"

namespace msys {
  extern Menu CheatsMenu;
  extern ToggleMenu CheatsItemsMenu;
  void Cheats_ApplyInfiniteItems(void);
  // TODO: Give keys in temples?
  // extern Menu CheatsKeysMenu;
  extern Menu TimeChangeMenu;
  extern Menu TimeSpeedMenu;
  extern Menu DayChangeMenu;

}  // namespace msys
