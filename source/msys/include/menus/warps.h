#pragma once

#include "msys/include/entrances.h"
#include "msys/include/menu.h"

namespace msys {
extern Menu WarpsMenu;
extern Menu WarpsPlacesMenu;
extern WarpsSceneMenu WarpsPlacesDungeonsMenu;
extern WarpsSceneMenu WarpsPlacesBossesMenu;
extern WarpsSceneMenu WarpsPlacesTownsMenu;
extern WarpsSceneMenu WarpsPlacesHousesMenu;
extern WarpsSceneMenu WarpsPlacesShopsMenu;
extern WarpsSceneMenu WarpsPlacesMiscMenu;
extern WarpsSceneMenu WarpsPlacesOverworldTerminaMenu;
extern WarpsSceneMenu WarpsPlacesOverworldSwampMenu;
extern WarpsSceneMenu WarpsPlacesOverworldSnowHeadMenu;
extern WarpsSceneMenu WarpsPlacesOverworldGreatBayMenu;
extern WarpsSceneMenu WarpsPlacesOverworldIkanaMenu;
extern WarpsSceneMenu WarpsSpiderHouses;
extern WarpsSceneMenu WarpsMoon;

void WarpsPlacesMenuShow(void);

enum {
  // Manual_Entrance_Menu_CsIdx,
  Manual_Entrance_Menu_EtcIdx,
  Manual_Entrance_Menu_Go,
};
}  // namespace msys
