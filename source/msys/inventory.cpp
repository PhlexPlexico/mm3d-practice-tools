#include "include/menus/inventory.h"
#include "game/common_data.h"
#include "common/context.h"
#include "game/items.h"
#include "msys/include/menu.h"



static game::ItemId SelectedBottle;
static u32 SelectedBottleIndex;
static u32 BottleNumber;

void RemoveItemFromButtons(game::ItemId item_id) {
  game::EquipmentData& equips = game::GetCommonData().save.equipment;
  for (u64 button = 0; button < equips.data[0].item_btns.size(); button++) {
    if (item_id == equips.data[0].item_btns[button]) {
      equips.data[0].item_btns[button] = game::ItemId::None;
      break;
    }
  }
}


static void DisableMenuToggles(ToggleMenu* menu) {
    for (u32 i = 0; i < menu->nbItems - 1; ++i) {
        menu->items[i].on = 0;
    }
}

static void Inventory_ItemsMenuInit(void) {
  //game::InventoryData& inventory = game::GetCommonData().save.inventory;
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
  // u32 numBottles =
  //     std::count_if(inventory.items.begin(), inventory.items.end(), game::ItemIsBottled);
  // for (u32 i = 0; i < numBottles; i++) {
  //   InventoryItemsMenu.items[(u32)game::ItemId::Bottle + i - 3].on = true;
  // }
}

static void Inventory_SongsMenuInit(void) {
  game::InventoryData& inventory = game::GetCommonData().save.inventory;
  InventorySongsMenu.items[0].on = inventory.collect_register.sonata_of_awakening;
  InventorySongsMenu.items[1].on = inventory.collect_register.goron_lullaby;
  InventorySongsMenu.items[2].on = inventory.collect_register.new_wave_bossa_nova;
  InventorySongsMenu.items[3].on = inventory.collect_register.elegy_of_emptiness;
  InventorySongsMenu.items[4].on = inventory.collect_register.oath_to_order;
  InventorySongsMenu.items[5].on = inventory.collect_register.sarias_song;
  InventorySongsMenu.items[6].on = inventory.collect_register.song_of_time;
  InventorySongsMenu.items[7].on = inventory.collect_register.song_of_healing;
  InventorySongsMenu.items[8].on = inventory.collect_register.eponas_song;
  InventorySongsMenu.items[9].on = inventory.collect_register.song_of_soaring;
  InventorySongsMenu.items[10].on = inventory.collect_register.song_of_storms;
  InventorySongsMenu.items[11].on = inventory.collect_register.suns_song;
  InventorySongsMenu.items[12].on = inventory.collect_register.lullaby_intro;
}

static void Inventory_MasksMenuInit(void) {
  InventoryMasksMenu.items[0].on = game::HasMask(game::ItemId::DekuMask);
  InventoryMasksMenu.items[1].on = game::HasMask(game::ItemId::GoronMask);
  InventoryMasksMenu.items[2].on = game::HasMask(game::ItemId::ZoraMask);
  InventoryMasksMenu.items[3].on = game::HasMask(game::ItemId::FierceDeityMask);
  InventoryMasksMenu.items[4].on = game::HasMask(game::ItemId::MaskOfTruth);
  InventoryMasksMenu.items[5].on = game::HasMask(game::ItemId::KafeiMask);
  InventoryMasksMenu.items[6].on = game::HasMask(game::ItemId::AllNightMask);
  InventoryMasksMenu.items[7].on = game::HasMask(game::ItemId::BunnyHood);
  InventoryMasksMenu.items[8].on = game::HasMask(game::ItemId::KeatonMask);
  InventoryMasksMenu.items[9].on = game::HasMask(game::ItemId::GaroMask);
  InventoryMasksMenu.items[10].on = game::HasMask(game::ItemId::RomaniMask);
  InventoryMasksMenu.items[11].on = game::HasMask(game::ItemId::CircusLeaderMask);
  InventoryMasksMenu.items[12].on = game::HasMask(game::ItemId::PostmanHat);
  InventoryMasksMenu.items[13].on = game::HasMask(game::ItemId::CoupleMask);
  InventoryMasksMenu.items[14].on = game::HasMask(game::ItemId::GreatFairyMask);
  InventoryMasksMenu.items[15].on = game::HasMask(game::ItemId::GibdoMask);
  InventoryMasksMenu.items[16].on = game::HasMask(game::ItemId::DonGeroMask);
  InventoryMasksMenu.items[17].on = game::HasMask(game::ItemId::KamaroMask);
  InventoryMasksMenu.items[18].on = game::HasMask(game::ItemId::CaptainHat);
  InventoryMasksMenu.items[19].on = game::HasMask(game::ItemId::StoneMask);
  InventoryMasksMenu.items[20].on = game::HasMask(game::ItemId::BremenMask);
  InventoryMasksMenu.items[21].on = game::HasMask(game::ItemId::BlastMask);
  InventoryMasksMenu.items[22].on = game::HasMask(game::ItemId::MaskOfScents);
  InventoryMasksMenu.items[23].on = game::HasMask(game::ItemId::GiantMask);
}

void Inventory_ItemsMenuFunc(void) {
  Inventory_ItemsMenuInit();
  ToggleMenuShow(&InventoryItemsMenu);
}

void Inventory_SongsMenuFunc(void) {
  Inventory_SongsMenuInit();
  ToggleMenuShow(&InventorySongsMenu);
}

void Inventory_MasksMenuFunc(void) {
  Inventory_MasksMenuInit();
  ToggleMenuShow(&InventoryMasksMenu);
}

void Inventory_ItemsToggle(s32 selected) {
  game::InventoryData& inventory = game::GetCommonData().save.inventory;
  std::array<game::ItemId, 24> items = inventory.items;
  switch (selected) {
  case ((s32)game::ItemId::Bomb - 1):
    if (!game::HasItem(game::ItemId::Bomb)) {
      game::GiveItem(game::ItemId::BombBag);
      game::GiveItem(game::ItemId::Bomb);
      InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Bomb);
      InventoryItemsMenu.items[(u32)game::ItemId::Bomb - 1].on = 0;
      RemoveItemFromButtons(game::ItemId::Bomb);
    }
    break;
  case ((u32)game::ItemId::Bombchu - 1):
    if (!game::HasItem(game::ItemId::Bombchu)) {
      game::GiveItem(game::ItemId::Bombchu);
      InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Bombchu);
      inventory.item_counts[(u32)game::ItemId::Bombchu] = 0x00;
      InventoryItemsMenu.items[(u32)game::ItemId::Bombchu - 1].on = 0;
      RemoveItemFromButtons(game::ItemId::Bombchu);
    }
    break;
  case ((u32)game::ItemId::DekuStick - 1):
    if (!game::HasItem(game::ItemId::DekuStick)) {
      game::GiveItem(game::ItemId::DekuStick);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuStick - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::DekuStick);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuStick - 1].on = 0;
      RemoveItemFromButtons(game::ItemId::DekuStick);
    }
    break;
  case ((u32)game::ItemId::DekuNuts - 1):
    if (!game::HasItem(game::ItemId::DekuNuts)) {
      game::GiveItem(game::ItemId::DekuNuts);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuNuts - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::DekuNuts);
      InventoryItemsMenu.items[(u32)game::ItemId::DekuNuts - 1].on = 0;
      RemoveItemFromButtons(game::ItemId::DekuNuts);
    }
    break;
  case ((u32)game::ItemId::MagicBean - 1):
    if (!game::HasItem(game::ItemId::MagicBean)) {
      game::GiveItem(game::ItemId::MagicBean);
      InventoryItemsMenu.items[(u32)game::ItemId::MagicBean - 1].on = 1;
    } else {
      game::RemoveItem(game::ItemId::MagicBean);
      InventoryItemsMenu.items[(u32)game::ItemId::MagicBean - 1].on = 0;
      RemoveItemFromButtons(game::ItemId::MagicBean);
    }
    break;
  case ((u32)game::ItemId::PowderKeg - 2):
    if (!game::HasItem(game::ItemId::PowderKeg)) {
      game::GiveItem(game::ItemId::PowderKeg);
      InventoryItemsMenu.items[(u32)game::ItemId::PowderKeg - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::PowderKeg);
      InventoryItemsMenu.items[(u32)game::ItemId::PowderKeg - 2].on = 0;
      RemoveItemFromButtons(game::ItemId::PowderKeg);
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
      RemoveItemFromButtons(game::ItemId::LensOfTruth);
    }
    break;
  case ((u32)game::ItemId::Hookshot - 2):
    if (!game::HasItem(game::ItemId::Hookshot)) {
      game::GiveItem(game::ItemId::Hookshot);
      InventoryItemsMenu.items[(u32)game::ItemId::Hookshot - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::Hookshot);
      InventoryItemsMenu.items[(u32)game::ItemId::Hookshot - 2].on = 0;
      RemoveItemFromButtons(game::ItemId::Hookshot);
    }
    break;
  case ((u32)game::ItemId::GreatFairySword - 2):
    if (!game::HasItem(game::ItemId::GreatFairySword)) {
      game::GiveItem(game::ItemId::GreatFairySword);
      InventoryItemsMenu.items[(u32)game::ItemId::GreatFairySword - 2].on = 1;
    } else {
      game::RemoveItem(game::ItemId::GreatFairySword);
      InventoryItemsMenu.items[(u32)game::ItemId::GreatFairySword - 2].on = 0;
      RemoveItemFromButtons(game::ItemId::GreatFairySword);
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
      RemoveItemFromButtons((game::ItemId)selected);
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

void Inventory_SongsToggle(s32 selected) {
  game::InventoryData::CollectRegister& song_list = game::GetCommonData().save.inventory.collect_register;
  switch (selected) {
    case (0):
      song_list.sonata_of_awakening = !song_list.sonata_of_awakening;
      break;
    case (1):
      song_list.goron_lullaby = !song_list.goron_lullaby;
      break;
    case (2):
      song_list.new_wave_bossa_nova = !song_list.new_wave_bossa_nova;
      break;
    case (3):
      song_list.elegy_of_emptiness = !song_list.elegy_of_emptiness;
      break;
    case (4):
      song_list.oath_to_order = !song_list.oath_to_order;
      break;
    case (5):
      song_list.sarias_song = !song_list.sarias_song;
      break;
    case (6):
      song_list.song_of_time = !song_list.song_of_time;
      break;
    case (7):
      song_list.song_of_healing = !song_list.song_of_healing;
      break;
    case (8):
      song_list.eponas_song = !song_list.eponas_song;
      break;
    case (9):
      song_list.song_of_soaring = !song_list.song_of_soaring;
      break;
    case (10):
      song_list.song_of_storms = !song_list.song_of_storms;
      break;
    case (11):
      song_list.suns_song = !song_list.suns_song;
      break;
    case (12):
      song_list.lullaby_intro = !song_list.lullaby_intro;
      if(song_list.lullaby_intro && song_list.goron_lullaby) {
        song_list.goron_lullaby = 0;
        InventorySongsMenu.items[1].on = 0;
      }
      break;    
  }
  InventorySongsMenu.items[selected].on = !InventorySongsMenu.items[selected].on;
}

void Inventory_MasksToggle(s32 selected) {
  u32 selectedMask = game::MaskSlotsOrdered[selected];
  if (!game::HasMask(game::MaskSlots[selectedMask])) {
    game::GiveMask(game::MaskSlots[selectedMask]);
    InventoryMasksMenu.items[selected].on = 1;
  } else {
    game::RemoveMask(selectedMask);
    InventoryMasksMenu.items[selected].on = 0;
    RemoveItemFromButtons(game::MaskSlots[selectedMask]);
  }
}

void Inventory_RemainsMenuFunc() {
  game::InventoryData::CollectRegister& remains = game::GetCommonData().save.inventory.collect_register;
  InventoryRemainsMenu.items[0].on = remains.odolwas_remains;
  InventoryRemainsMenu.items[1].on = remains.gohts_remains;
  InventoryRemainsMenu.items[2].on = remains.gyorgs_remains;
  InventoryRemainsMenu.items[3].on = remains.twinmolds_remains;
  ToggleMenuShow(&InventoryRemainsMenu);
}

void Inventory_RemainsToggle(s32 selected) {
  game::InventoryData::CollectRegister& remains = game::GetCommonData().save.inventory.collect_register;
  switch (selected) {
    case 0:
      remains.odolwas_remains = !remains.odolwas_remains;
      break;
    case 1:
      remains.gohts_remains = !remains.gohts_remains;
      break;
    case 2:
      remains.gyorgs_remains = !remains.gyorgs_remains;
      break;
    case 3:
      remains.twinmolds_remains = !remains.twinmolds_remains;
      break;
  }
  InventoryRemainsMenu.items[selected].on = !InventoryRemainsMenu.items[selected].on;
}

void Inventory_SwordMenuFunc() {
  game::EquipmentData::SwordShield& swordShield = game::GetCommonData().save.equipment.sword_shield;
  InventorySwordsMenu.items[0].on = swordShield.sword == game::SwordType::NoSword ? 1 : 0;
  InventorySwordsMenu.items[1].on = swordShield.sword == game::SwordType::KokiriSword ? 1 : 0;
  InventorySwordsMenu.items[2].on = swordShield.sword == game::SwordType::RazorSword ? 1 : 0;
  InventorySwordsMenu.items[3].on = swordShield.sword == game::SwordType::GildedSword ? 1 : 0;
  ToggleMenuShow(&InventorySwordsMenu);
}

void Inventory_SwordsToggle(s32 selected) {
  game::EquipmentData::SwordShield& swordShield = game::GetCommonData().save.equipment.sword_shield;
  switch (selected) {
    case 0:
      swordShield.sword = game::SwordType::NoSword;
      InventorySwordsMenu.items[1].on = 0;
      InventorySwordsMenu.items[2].on = 0;
      InventorySwordsMenu.items[3].on = 0;
      break;
    case 1:
      swordShield.sword = game::SwordType::KokiriSword;
      InventorySwordsMenu.items[0].on = 0;
      InventorySwordsMenu.items[2].on = 0;
      InventorySwordsMenu.items[3].on = 0;
      break;
    case 2:
      swordShield.sword = game::SwordType::RazorSword;
      InventorySwordsMenu.items[0].on = 0;
      InventorySwordsMenu.items[1].on = 0;
      InventorySwordsMenu.items[3].on = 0;
      break;
    case 3:
      swordShield.sword = game::SwordType::GildedSword;
      InventorySwordsMenu.items[0].on = 0;
      InventorySwordsMenu.items[1].on = 0;
      InventorySwordsMenu.items[2].on = 0;
      break;
  }
  InventorySwordsMenu.items[selected].on = !InventorySwordsMenu.items[selected].on;
}

void Inventory_ShieldMenuFunc() {
  game::EquipmentData::SwordShield& swordShield = game::GetCommonData().save.equipment.sword_shield;
  InventoryShieldsMenu.items[0].on = swordShield.shield == game::ShieldType::NoShield ? 1 : 0;
  InventoryShieldsMenu.items[1].on = swordShield.shield == game::ShieldType::HeroShield ? 1 : 0;
  InventoryShieldsMenu.items[2].on = swordShield.shield == game::ShieldType::MirrorShield ? 1 : 0;
  ToggleMenuShow(&InventoryShieldsMenu);
}

void Inventory_ShieldsToggle(s32 selected) {
  game::EquipmentData::SwordShield& swordShield = game::GetCommonData().save.equipment.sword_shield;
  // TODO: Get player actor change shield animation type.
  switch (selected) {
    case 0:
      swordShield.shield = game::ShieldType::NoShield;
      InventoryShieldsMenu.items[1].on = 0;
      InventoryShieldsMenu.items[2].on = 0;
      break;
    case 1:
      swordShield.shield = game::ShieldType::HeroShield;
      InventoryShieldsMenu.items[0].on = 0;
      InventoryShieldsMenu.items[2].on = 0;
      break;
    case 2:
      swordShield.shield = game::ShieldType::MirrorShield;
      InventoryShieldsMenu.items[0].on = 0;
      InventoryShieldsMenu.items[1].on = 0;
      break;
  }
  InventoryShieldsMenu.items[selected].on = !InventoryShieldsMenu.items[selected].on;
}

Menu InventoryMenu = {
    .title = "Inventory",
    .nbItems = 6,
    .items = {
        {.title = "Items", .action_type = METHOD, .method = Inventory_ItemsMenuFunc},
        {.title = "Masks", .action_type = METHOD, .method = Inventory_MasksMenuFunc},
        {.title = "Shield", .action_type = METHOD, .method = Inventory_ShieldMenuFunc},
        {.title = "Sword", .action_type = METHOD, .method = Inventory_SwordMenuFunc},
        {.title = "Remains", .action_type = METHOD, .method = Inventory_RemainsMenuFunc},
        {.title = "Ocarina Songs", .action_type = METHOD, .method = Inventory_SongsMenuFunc},
        //{.title = "Amounts", .action_type = METHOD, .method = Inventory_AmountsMenuFunc},
    }
};

ToggleMenu InventoryItemsMenu = {
    .title="Items",
    .nbItems=15,
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

ToggleMenu InventoryMasksMenu = {
    .title="Masks",
    .nbItems=24,
    .items= {
        {.on=0, .title="Deku Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Goron Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Zora Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Fierce Deity Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Mask Of Truth", .method = Inventory_MasksToggle},
        {.on=0, .title="Kafei Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="All Night Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Bunny Hood", .method = Inventory_MasksToggle},
        {.on=0, .title="Keaton Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Garo Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Romani's Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Circus Leader Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Postman Hat", .method = Inventory_MasksToggle},
        {.on=0, .title="Couple's Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Great Fairy Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Gibdo Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Don Gero Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Kamaro Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Captain Hat", .method = Inventory_MasksToggle},
        {.on=0, .title="Stone Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Bremen Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Blast Mask", .method = Inventory_MasksToggle},
        {.on=0, .title="Mask Of Scents", .method = Inventory_MasksToggle},
        {.on=0, .title="Giant's Mask", .method = Inventory_MasksToggle},
    }
};

ToggleMenu InventorySongsMenu = {
    .title="Songs",
    .nbItems=13,
    .items= {
        {.on=0, .title="Sonata Of Awakening", .method = Inventory_SongsToggle},
        {.on=0, .title="Goron Lullaby", .method = Inventory_SongsToggle},
        {.on=0, .title="New Wave Bossa Nova", .method = Inventory_SongsToggle},
        {.on=0, .title="Elegy of Emptiness", .method = Inventory_SongsToggle},
        {.on=0, .title="Oath To Order", .method = Inventory_SongsToggle},
        {.on=0, .title="Sarias Song (does nothing)", .method = Inventory_SongsToggle},
        {.on=0, .title="Song of Time", .method = Inventory_SongsToggle},
        {.on=0, .title="Song of Healing", .method = Inventory_SongsToggle},
        {.on=0, .title="Epona's Song", .method = Inventory_SongsToggle},
        {.on=0, .title="Song of Soaring", .method = Inventory_SongsToggle},
        {.on=0, .title="Song of Storms", .method = Inventory_SongsToggle},
        {.on=0, .title="Suns Song (does nothing)", .method = Inventory_SongsToggle},
        {.on=0, .title="Lullaby Intro", .method = Inventory_SongsToggle}
    }
};

ToggleMenu InventoryRemainsMenu = {
    .title="Remains",
    .nbItems=4,
    .items= {
        {.on=0, .title="Odolwa's Remains", .method = Inventory_RemainsToggle},
        {.on=0, .title="Goht's Remains", .method = Inventory_RemainsToggle},
        {.on=0, .title="Gyorg's Remains", .method = Inventory_RemainsToggle},
        {.on=0, .title="Twinmold's Remains", .method = Inventory_RemainsToggle}
    }
};

ToggleMenu InventorySwordsMenu = {
    .title="Swords",
    .nbItems=4,
    .items= {
        {.on=0, .title="No Sword", .method = Inventory_SwordsToggle},
        {.on=0, .title="Kokiri Sword", .method = Inventory_SwordsToggle},
        {.on=0, .title="Razor Sword", .method = Inventory_SwordsToggle},
        {.on=0, .title="Gilded Sword", .method = Inventory_SwordsToggle}
    }
};

ToggleMenu InventoryShieldsMenu = {
    .title="Swords",
    .nbItems=3,
    .items= {
        {.on=0, .title="No Shield", .method = Inventory_ShieldsToggle},
        {.on=0, .title="Hero's Shield", .method = Inventory_ShieldsToggle},
        {.on=0, .title="Mirror Shield", .method = Inventory_ShieldsToggle},
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
