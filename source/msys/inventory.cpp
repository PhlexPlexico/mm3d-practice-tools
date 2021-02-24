#include "msys/include/menu.h"
#include "msys/include/menus/inventory.h"
#include "msys/include/draw.h"
#include "game/common_data.h"
#include "game/items.h"

#include <stdio.h>

static u32 SelectedBottle;

Menu InventoryMenu = {
    "Inventory",
    .nbItems = 5,
    {
        {"Items", METHOD, .method = Inventory_ItemsMenuFunc},
        {"Right Side Gear", METHOD, .method = Inventory_RightGearMenuFunc},
        {"Left Side Gear", METHOD, .method = Inventory_LeftGearMenuFunc},
        {"Ocarina Songs", METHOD, .method = Inventory_SongsMenuFunc},
        {"Amounts", METHOD, .method = Inventory_AmountsMenuFunc},
    }
};
