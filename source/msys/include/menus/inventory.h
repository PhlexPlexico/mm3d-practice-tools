#pragma once

#include "msys/include/menu.h"

extern Menu InventoryMenu;
extern ToggleMenu InventoryItemsMenu;
extern ToggleMenu InventoryBottlesMenu;
extern ToggleMenu InventoryMasksMenu;
extern ToggleMenu InventorySongsMenu;
extern ToggleMenu InventoryRemainsMenu;
extern ToggleMenu InventorySwordsMenu;
extern ToggleMenu InventoryShieldsMenu;
extern AmountMenu InventoryAmountsMenu;

//void RemoveItemFromButtons(ItemId);
//void Inventory_ItemsToggle(s32);
//void Inventory_MasksToggle(s32);
// void Inventory_BottleSelect(s32);
enum BottleContents { //Bottle Choices
    Empty_Bottle = 0,
    Red_Potion,
    Green_Potion,
    Blue_Potion,
    Bottled_Fairy,
    Deku_Princess,
    Lon_Lon_Milk,
    Lon_Lon_Milk_Half,
    Fish,
    Bug,
    Blue_Fire,
    Poe,
    Big_Poe,
    Water,
    Hot_Spring_Water,
    Zora_Egg,
    Gold_Dust,
    Magical_Mushroom,
    Sea_Horse,
    Chateau_Romani,
    Mystery_Milk,
    Myster_Milk_Spoiled,
    None
};

enum { //Gear Menu Choices
    Gear_Menu_Kokiri_Sword = 0,
    Gear_Menu_Gided_Sword,
    Gear_Menu_Razor_Sword, 
    Gear_Menu_Hero_Shield,
    Gear_Menu_Mirror_Shield, 
    Gear_Menu_Quiver_30,
    Gear_Menu_Quiver_40,
    Gear_Menu_Quiver_50,
    Gear_Menu_Bomb_Bag_20,
    Gear_Menu_Bomb_Bag_30,
    Gear_Menu_Bomb_Bag_40,
    Gear_Menu_Adults_Wallet,
    Gear_Menu_Giants_Wallet,
    Gear_Menu_No_Wallet,
    Gear_Menu_Bombers_Notebook, // in bitfield elsewhere
    Gear_Menu_Fishing_Passes, // TODO - Find these.
    Gear_Menu_Moons_Tear,
    Gear_Menu_CT_Title_Deed,
    Gear_Menu_Swamp_Title_Deed,
    Gear_Menu_Mopuntain_Title_Deed,
    Gear_Menu_Ocean_Title_Deed,
    Gear_Menu_Room_Key,
    Gear_Menu_Letter_To_Mama,
    Gear_Menu_Letter_To_Kafei,
    Gear_Menu_Pendant_Of_Memories,
    //Gear_Menu_Fishing_Passes
};

enum { //Mask Gear Menu Choices
    Gear_Menu_Odolwa_Mask,
    Gear_Menu_Goht_Mask,
    Gear_Menu_Gyorg_Mask,
    Gear_Menu_Twinmold_Mask,
};

enum { //Songs Menu Choices
    Songs_Menu_Song_Of_Time,
    Songs_Menu_Song_Of_Healing,
    Songs_Menu_Eponas_Song,
    Songs_Menu_Song_Of_Soaring,
    Songs_Menu_Song_of_Storms,
    Songs_Menu_Lullaby,
    Songs_Menu_Bossa,
    Songs_Menu_Elegy,
    Songs_Menu_Oath,
    Songs_Menu_Inverted,
    Songs_Menu_Double,
};