#include "include/menus/inventory.h"
#include "game/common_data.h"
#include "common/context.h"
#include "game/items.h"
#include "msys/include/menu.h"



static game::ItemId SelectedBottle;
static u32 SelectedBottleIndex;
static u32 BottleNumber;

static void DisableMenuToggles(ToggleMenu* menu) {
    for (u32 i = 0; i < menu->nbItems - 1; ++i) {
        menu->items[i].on = 0;
    }
}

static void Inventory_ItemsMenuInit(void) {
  game::InventoryData& inventory = game::GetCommonData().save.inventory;
  InventoryItemsMenu.items[(u32)game::ItemId::Ocarina].on = game::HasOcarina();
  InventoryItemsMenu.items[(u32)game::ItemId::Arrow].on = game::HasItem(game::ItemId::Arrow);
  InventoryItemsMenu.items[(u32)game::ItemId::FireArrow].on =
      game::HasItem(game::ItemId::FireArrow);
  InventoryItemsMenu.items[(u32)game::ItemId::IceArrow].on = game::HasItem(game::ItemId::IceArrow);
  InventoryItemsMenu.items[(u32)game::ItemId::LightArrow].on =
      game::HasItem(game::ItemId::LightArrow);
  // InventoryItemsMenu.items[(u32)game::ItemId::FairyOcarina].on =
  // game::HasItem(game::ItemId::FairyOcarina); Offset due to item missing.
  InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on = game::HasItem(game::ItemId::Bomb);
  InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on =
      game::HasItem(game::ItemId::Bombchu);
  InventoryItemsMenu.items[(u32)game::ItemId::DekuStick - 1].on =
      game::HasItem(game::ItemId::DekuStick);
  InventoryItemsMenu.items[(u32)game::ItemId::DekuNuts - 1].on =
      game::HasItem(game::ItemId::DekuNuts);
  InventoryItemsMenu.items[(u32)game::ItemId::MagicBean - 1].on =
      game::HasItem(game::ItemId::MagicBean);
  // InventoryItemsMenu.items[(u32)game::ItemId::FairySlingshot].on =
  // game::HasItem(game::ItemId::FairySlingshot);
  InventoryItemsMenu.items[(u32)game::ItemId::PowderKeg - 2].on =
      game::HasItem(game::ItemId::PowderKeg);
  InventoryItemsMenu.items[(u32)game::ItemId::PictographBox - 2].on =
      game::HasItem(game::ItemId::PictographBox);
  InventoryItemsMenu.items[(u32)game::ItemId::LensOfTruth - 2].on =
      game::HasItem(game::ItemId::LensOfTruth);
  InventoryItemsMenu.items[(u32)game::ItemId::Hookshot - 2].on =
      game::HasItem(game::ItemId::Hookshot);
  InventoryItemsMenu.items[(u32)game::ItemId::GreatFairySword - 2].on =
      game::HasItem(game::ItemId::GreatFairySword);
  // Loop through bottles and check which ones we have.
  int numBottles =
      std::count_if(inventory.items.begin(), inventory.items.end(), game::ItemIsBottled);
  for (int i = 0; i < numBottles; i++) {
    InventoryItemsMenu.items[(u32)game::ItemId::Bottle + i - 3].on = true;
  }
}

void Inventory_ItemsMenuFunc(void) {
  Inventory_ItemsMenuInit();
  ToggleMenuShow(&InventoryItemsMenu);
}

void Inventory_ItemsToggle(s32 selected) {
  game::InventoryData& inventory = game::GetCommonData().save.inventory;
  std::array<game::ItemId, 24> items = inventory.items;
  switch (selected) {
  case ((s32)game::ItemId::Bomb - 1):
    if (!InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on) {
      game::GiveItem(game::ItemId::BombBag);
      game::GiveItem(game::ItemId::Bomb);
      InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Bomb);
      //inventory.item_counts[(u32)game::ItemId::Bomb] = 0x00;
      InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bombchu - 1):
    if (!InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on) {
      game::GiveItem(game::ItemId::Bombchu);
      InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Bombchu);
      inventory.item_counts[(u32)game::ItemId::Bombchu] = 0x00;
      InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::DekuStick - 1):
    if (!game::HasItem(game::ItemId::DekuStick)) {
      game::GiveItem(game::ItemId::DekuStick);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuStick - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::DekuStick);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuStick - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::DekuNuts - 1):
    if (!game::HasItem(game::ItemId::DekuNuts)) {
      game::GiveItem(game::ItemId::DekuNuts);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuNuts - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::DekuNuts);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuNuts - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::MagicBean - 1):
    if (!game::HasItem(game::ItemId::MagicBean)) {
      game::GiveItem(game::ItemId::MagicBean);
      InventoryItemsMenu.items[(u32)game::ItemId::MagicBean - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::MagicBean);
      InventoryItemsMenu.items[(u32)game::ItemId::MagicBean - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::PowderKeg - 2):
    if (!game::HasItem(game::ItemId::PowderKeg)) {
      game::GiveItem(game::ItemId::PowderKeg);
      InventoryItemsMenu.items[(u32)game::ItemId::PowderKeg - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::PowderKeg);
      InventoryItemsMenu.items[(u32)game::ItemId::PowderKeg - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::PictographBox - 2):
    if (!game::HasItem(game::ItemId::PictographBox)) {
      game::GiveItem(game::ItemId::PictographBox);
      InventoryItemsMenu.items[(u32)game::ItemId::PictographBox - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::PictographBox);
      InventoryItemsMenu.items[(u32)game::ItemId::PictographBox - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::LensOfTruth - 2):
    if (!game::HasItem(game::ItemId::LensOfTruth)) {
      game::GiveItem(game::ItemId::LensOfTruth);
      InventoryItemsMenu.items[(u32)game::ItemId::LensOfTruth - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::LensOfTruth);
      InventoryItemsMenu.items[(u32)game::ItemId::LensOfTruth - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::Hookshot - 2):
    if (!game::HasItem(game::ItemId::Hookshot)) {
      game::GiveItem(game::ItemId::Hookshot);
      InventoryItemsMenu.items[(u32)game::ItemId::Hookshot - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Hookshot);
      InventoryItemsMenu.items[(u32)game::ItemId::Hookshot - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::GreatFairySword - 2):
    if (!game::HasItem(game::ItemId::GreatFairySword)) {
      game::GiveItem(game::ItemId::GreatFairySword);
      InventoryItemsMenu.items[(u32)game::ItemId::GreatFairySword - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::GreatFairySword);
      InventoryItemsMenu.items[(u32)game::ItemId::GreatFairySword - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle - 3):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 3].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 3].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle - 2):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 2].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 2].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle - 1):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 1].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle - 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle + 1):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle + 1].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle + 1].on = 0;
    }
    break;
  case ((u32)game::ItemId::Bottle + 2):
    if (!game::HasItem(game::ItemId::Bottle)) {
      game::GiveItem(game::ItemId::Bottle);
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle + 2].on = 1;
    } else {
      // Remove the first bottle that's not game::ItemId::None.
      for (auto i = items.begin(); i != items.end(); ++i) {
        if (game::ItemIsBottled(*i)) {
          game::RemoveItem(*i);
          break;
        }
      }
      InventoryItemsMenu.items[(u32)game::ItemId::Bottle + 2].on = 0;
    }
    break;
  default:
    if (!game::HasItem((game::ItemId)selected)) {
      game::GiveItem((game::ItemId)selected);
      InventoryItemsMenu.items[selected].on = 1;
    } else {
      game::RemoveItem((game::ItemId)selected);
      InventoryItemsMenu.items[selected].on = 0;
    }
    break;
  }
}

static void Inventory_BottlesMenuInit(void) {
  //game::CommonData& cdata = game::GetCommonData();
  for (u32 i = (u32)game::ItemId::RedPotion; i < (u32)game::ItemId::MoonTear; ++i) {
    if (game::HasItem(SelectedBottle)) {
      InventoryBottlesMenu.items[i].on = game::HasItem((game::ItemId)i);
      // Can only have one thing in a selected bottle, no need to continue.
      // break;
    }
  }
  InventoryBottlesMenu.items[BottleContents::None].on = !game::HasItem(SelectedBottle);
}

void Inventory_BottlesMenuFunc(s32 selected) {
  game::CommonData& cdata = game::GetCommonData();
  // Get the selected bottle.
  u32 bottle_number = selected - 14;
  u32 current_bottle = 0;
  // Loop through to the specific selected bottle.
  for (u32 i = cdata.save.inventory.items.size(); i < cdata.save.inventory.items.size(); i++) {
    if (game::ItemIsBottled(cdata.save.inventory.items[i])) {
      if (current_bottle != bottle_number) {
        current_bottle++;
      } else if (current_bottle == bottle_number) {
        SelectedBottle = cdata.save.inventory.items[i];
        SelectedBottleIndex = i;
        BottleNumber = current_bottle;
        break;
      } else {
        SelectedBottleIndex = 255;
        SelectedBottle = game::ItemId::None;
      }
    }
    
  }
  Inventory_BottlesMenuInit();
  ToggleMenuShow(&InventoryBottlesMenu);
}

void Inventory_BottleSelect(s32 selected) {
  game::CommonData& cdata = game::GetCommonData();
  if (selected != BottleContents::None) {  // selected a bottled content
    cdata.save.inventory.items[SelectedBottleIndex] =
        game::ItemId((u32)game::ItemId::Bottle + (u32)selected);
    InventoryBottlesMenu.items[selected].on = 1;
    InventoryItemsMenu.items[14 + BottleNumber].on = 1;
  } else {  // erase the bottle
    cdata.save.inventory.items[SelectedBottleIndex] = game::ItemId::None;
    DisableMenuToggles(&InventoryBottlesMenu);
    InventoryBottlesMenu.items[InventoryBottlesMenu.nbItems - 1].on = 1;
    InventoryItemsMenu.items[14 + BottleNumber].on = 0;
  }
}

Menu InventoryMenu = {
    .title = "Inventory",
    .nbItems = 1,
    .items = {
        {.title = "Items", .action_type = METHOD, .method = Inventory_ItemsMenuFunc},
        //{.title = "Right Side Gear", .action_type = METHOD, .method = Inventory_RightGearMenuFunc},
        //{.title = "Left Side Gear", .action_type = METHOD, .method = Inventory_LeftGearMenuFunc},
        //{.title = "Ocarina Songs", .action_type = METHOD, .method = Inventory_SongsMenuFunc},
        //{.title = "Amounts", .action_type = METHOD, .method = Inventory_AmountsMenuFunc},
    }
};

ToggleMenu InventoryItemsMenu = {
    .title="Items",
    .nbItems=21,
    .items= {
        {.on=0, .title="Ocarina", .method = Inventory_ItemsToggle},
        {.on=0, .title="Hero's Bow", .method = Inventory_ItemsToggle},
        {.on=0, .title="Fire Arrows", .method = Inventory_ItemsToggle},
        {.on=0, .title="Ice Arrows", .method = Inventory_ItemsToggle},
        {.on=0, .title="Light Arrows", .method = Inventory_ItemsToggle},
        {.on=0, .title="Bombs", .method = Inventory_ItemsToggle},
        {.on=0, .title="Bombchus", .method = Inventory_ItemsToggle},
        {.on=0, .title="Deku Sticks", .method = Inventory_ItemsToggle},
        {.on=0, .title="Deku Nuts", .method = Inventory_ItemsToggle},
        {.on=0, .title="Magic Beans", .method = Inventory_ItemsToggle},
        {.on=0, .title="Powder Keg", .method = Inventory_ItemsToggle},
        {.on=0, .title="Pictograph Box", .method = Inventory_ItemsToggle},
        {.on=0, .title="Lens Of Truth", .method = Inventory_ItemsToggle},
        {.on=0, .title="Hookshot", .method = Inventory_ItemsToggle},
        {.on=0, .title="Great Fairy Sword", .method = Inventory_ItemsToggle},
        {.on=0, .title="Bottle #1", .method = Inventory_BottlesMenuFunc},
        {.on=0, .title="Bottle #2", .method = Inventory_BottlesMenuFunc},
        {.on=0, .title="Bottle #3", .method = Inventory_BottlesMenuFunc},
        {.on=0, .title="Bottle #4", .method = Inventory_BottlesMenuFunc},
        {.on=0, .title="Bottle #5", .method = Inventory_BottlesMenuFunc},
        {.on=0, .title="Bottle #6", .method = Inventory_BottlesMenuFunc},
    }
};

ToggleMenu InventoryBottlesMenu = {
    .title="Choose Bottle Contents",
    .nbItems = 14,
    .items={
        {.on=0, .title="Empty Bottle", .method = Inventory_BottleSelect},
        {.on=0, .title="Red Potion", .method = Inventory_BottleSelect},
        {.on=0, .title="Green Potion", .method = Inventory_BottleSelect},
        {.on=0, .title="Blue Potion", .method = Inventory_BottleSelect},
        {.on=0, .title="Bottled Fairy", .method = Inventory_BottleSelect},
        {.on=0, .title="Deku Princess", .method = Inventory_BottleSelect},
        {.on=0, .title="Lon Lon Milk", .method = Inventory_BottleSelect},
        {.on=0, .title="Lon Lon Milk (Half)", .method = Inventory_BottleSelect},
        {.on=0, .title="Fish", .method = Inventory_BottleSelect},
        {.on=0, .title="Bug", .method = Inventory_BottleSelect},
        {.on=0, .title="Blue Fire", .method = Inventory_BottleSelect},
        {.on=0, .title="Poe", .method = Inventory_BottleSelect},
        {.on=0, .title="BigPoe", .method = Inventory_BottleSelect},
        {.on=0, .title="Water", .method = Inventory_BottleSelect},
        {.on=0, .title="Hot Spring Water", .method = Inventory_BottleSelect},
        {.on=0, .title="Zora Egg", .method = Inventory_BottleSelect},
        {.on=0, .title="Gold Dust", .method = Inventory_BottleSelect},
        {.on=0, .title="Magical Mushroom", .method = Inventory_BottleSelect},
        {.on=0, .title="Sea Horse", .method = Inventory_BottleSelect},
        {.on=0, .title="Chateau Romani", .method = Inventory_BottleSelect},
        {.on=0, .title="Mystery Milk", .method = Inventory_BottleSelect},
        {.on=0, .title="Mystery Milk Spoiled", .method = Inventory_BottleSelect},
        {.on=0, .title="None", .method = Inventory_BottleSelect},
    }
};
