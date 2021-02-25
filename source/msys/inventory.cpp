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

static void Inventory_ItemsMenuInit(void){
    InventoryItemsMenu.items[(u32)game::ItemId::Ocarina].on = game::HasItem(game::ItemId::Ocarina);
    InventoryItemsMenu.items[(u32)game::ItemId::Arrow].on = game::HasItem(game::ItemId::Arrow);
    InventoryItemsMenu.items[(u32)game::ItemId::FireArrow].on = game::HasItem(game::ItemId::FireArrow);
    InventoryItemsMenu.items[(u32)game::ItemId::IceArrow].on = game::HasItem(game::ItemId::IceArrow);
    InventoryItemsMenu.items[(u32)game::ItemId::LightArrow].on = game::HasItem(game::ItemId::LightArrow);
    //InventoryItemsMenu.items[(u32)game::ItemId::FairyOcarina].on = game::HasItem(game::ItemId::FairyOcarina);
    InventoryItemsMenu.items[(u32)game::ItemId::Bomb].on = game::HasItem(game::ItemId::Bomb);
    InventoryItemsMenu.items[(u32)game::ItemId::Bombchu].on = game::HasItem(game::ItemId::Bombchu);
    InventoryItemsMenu.items[(u32)game::ItemId::DekuStick].on = game::HasItem(game::ItemId::DekuStick);
    
}