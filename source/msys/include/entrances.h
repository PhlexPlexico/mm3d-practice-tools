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
    .nbItems = 2,
    .items = {
        {0x0000, "From East Clock Town"},
        {0x0001, "From After Couple's Mask"}
    }
};

const EntrancesByScene Entrances_Majoras_Lair = {
    .title = "Majora's Lair",
    .nbItems = 1,
    .items = {
        {0x0200, "From Moon"}
    }
};

const EntrancesByScene Entrances_Ranch = {
    .title = "Romani Ranch Buildings",
    .nbItems = 2,
    .items = {
        {0x0600, "Barn From Ranch"},
        {0x0610, "House From Ranch"}
    }
};

const EntrancesByScene Entrances_Hags_Potion_Shop = {
    .title = "Hag's Potion Shop",
    .nbItems = 1,
    .items = {
        {0x0400, "From Southern Swamp"}
    }
};

const EntrancesByScene Entrances_HoneyDarling_Potion_Shop = {
    .title = "Honey & Darling's Shop",
    .nbItems = 1,
    .items = {
        {0x0800, "From East Clock Town"}
    }
};

const EntrancesByScene Entrances_Swamp_Poison = {
    .title = "Poison Swamp Entrances",
    .nbItems = 10,
    .items = {
        {0x8400, "From Road to Southern Swamp"},
        {0x8410, "From Tourist Information"},
        {0x8420, "From Woodfall"},
        {0x8430, "Deku Palace"},
        {0x8440, "Deku Palace (Shortcut)"},
        {0x8450, "Hag's Potion Shop"},
        {0x8460, "From Starting Boat Cruise"},
        {0x8470, "From Woods of Mystery"},
        {0x8480, "from Swamp Spiderhouse"},
        {0x8490, "From Ikana Canyon"},
        {0x84A0, "From Owl Statue"}
    }
};
