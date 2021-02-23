#pragma once

#include "msys/include/menu.h"
#include "msys/include/entrances.h"

extern Menu WarpsMenu;
extern Menu WarpsPlacesMenu;
// extern WarpsSceneMenu WarpsPlacesDungeonsMenu;
// extern WarpsSceneMenu WarpsPlacesBossesMenu;
extern WarpsSceneMenu WarpsPlacesTownsMenu;
// extern WarpsSceneMenu WarpsPlacesHousesMenu;
// extern WarpsSceneMenu WarpsPlacesShopsMenu;
// extern WarpsSceneMenu WarpsPlacesMiscMenu;
extern WarpsSceneMenu WarpsPlacesOverworldMenu;

void WarpsPlacesMenuShow(void);

enum {
    Manual_Entrance_Menu_CsIdx,
    Manual_Entrance_Menu_EtcIdx,
    Manual_Entrance_Menu_Go,
};