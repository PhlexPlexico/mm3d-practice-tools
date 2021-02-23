#pragma once

#include "../../game/scene.h"

typedef struct EntrancesBySceneEntry {
    u16 entranceIndex;
    const char* title;
} EntrancesBySceneEntry;

typedef struct EntrancesByScene {
    const char* title;

    u32 nbItems;
    EntrancesBySceneEntry items[0x20];
} EntrancesByScene;

typedef struct SceneMenuEntry {
    const char* title;
    const EntrancesByScene* entrances;
} WarpsSceneMenuEntry;

typedef struct SceneMenu {
    const char* title;

    u32 nbItems;
    WarpsSceneMenuEntry scenes[0x20];
} WarpsSceneMenu;

typedef struct WarpsPlacesMenuEntry {
    const char* title;
    const WarpsSceneMenu* menu;
} WarpsPlacesMenuEntry;

void EntranceSelectMenuShow(const EntrancesByScene* entrances);
void EntranceWarp(u16 EntranceIndex);
void WarpsSceneMenuShow(const WarpsSceneMenu* menu);

void ManuallyEnterEntranceIndex(void);

const EntrancesByScene Entrances_Mayors_Residence = {
    .title = "Mayor's Residence",
    .nbItems = 3,
    .items = {
        {0x0000, "From East Clock Town"},
        {0x0001, "From After Couple's Mask"},
        {0x0002, "Crash"}
    }
};

const EntrancesByScene Entrances_Swamp_Poison = {
    .title = "Poison Swamp Entrances",
    .nbItems = 10,
    .items = {
        {0x8400, "From Road to Southern Swamp"},
        {0x8401, "From Tourist Information"},
        {0x8402, "From Woodfall"},
        {0x8403, "Deku Palace"},
        {0x8404, "Deku Palace (Shortcut)"},
        {0x8405, "Hag's Potion Shop"},
        {0x8406, "From Starting Boat Cruise"},
        {0x8407, "From Woods of Mystery"},
        {0x8408, "from Swamp Spiderhouse"},
        {0x8409, "From Ikana Canyon"},
        {0x840A, "From Owl Statue"}
    }
};



enum {
    Entrance_Select_Menu_CsIdx,
    Entrance_Select_Menu_Etcs,
};