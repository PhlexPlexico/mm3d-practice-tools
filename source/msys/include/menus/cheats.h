#pragma once

#include "msys/include/menu.h"

namespace msys {
    extern Menu CheatsMenu;
    extern Menu CheatsItemsMenu;
    // TODO: Give keys in temples?
    //extern Menu CheatsKeysMenu;
    extern Menu TimeChangeMenu;
    extern Menu TimeSpeedMenu;
    extern Menu DayChangeMenu;
    extern Menu LinkAmountInfo;

    enum LinkData {
        HEALTH = 0,
        MAGIC,
        RAZOR_SWORD,
        RUPEE
    };
}
