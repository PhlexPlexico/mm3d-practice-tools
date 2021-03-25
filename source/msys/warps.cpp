#include "msys/include/menu.h"
#include "msys/include/menus/warps.h"
#include "msys/include/draw.h"
#include "msys/include/entrances.h"
#include <stdio.h>

Menu WarpsMenu = {
    .title="Warps",
    .nbItems = 2,
    .items={
        {.title = "Places", .action_type = METHOD, .method = WarpsPlacesMenuShow},
        {.title = "Manually Enter Entrance Index", .action_type = METHOD, .method = ManuallyEnterEntranceIndex}
    }
};

WarpsSceneMenu WarpsPlacesOverworldSwampMenu = {
    .title="Swamp Overworld",
    .nbItems = 12,
    .scenes={
        {"0C: Southern Swamp Clear", &Entrances_Southern_Swamp_Clear},
        {"14: Grottos", &Entrances_Lone_Peak_Shrine_And_Grottos},
        {"3E: Milk Road", &Entrances_Milk_Road},
        {"46: Fairy's Fountains", &Entrances_Fairys_Fountain},
        {"50: Deku Palace", &Entrances_Deku_Palace},
        {"54: Termina", &Entrances_Termina_Field},
        {"76: Deku King's Chamber", &Entrances_Deku_Kings_Chamber},
        {"7A: Road To Southern Swamp", &Entrances_Road_To_Southern_Swamp},
        {"84: Southern Swamp (Poison)", &Entrances_Swamp_Poison},
        {"C2: Woods Of Mystery", &Entrances_Woods_Of_Mystery},
        {"A8: Tourist Information", &Entrances_Tourist_Information},
        {"9E: Deku Shrine", &Entrances_Deku_Shrine},
    }
};

WarpsSceneMenu WarpsPlacesOverworldSnowHeadMenu = {
    .title="Snowhead Overworld",
    .nbItems = 14,
    .scenes={
        {"14: Grottos", &Entrances_Lone_Peak_Shrine_And_Grottos},
        {"32: Path To Mountain Village", &Entrances_Path_To_Mountain_Village},
        {"46: Fairy's Fountains", &Entrances_Fairys_Fountain},
        {"5E: Goron Shrine", &Entrances_Goron_Shrine},
        {"74: Goron Shop", &Entrances_Goron_Shop},
        {"8A: Goron Village (Spring)", &Entrances_Goron_Village_Spring},
        {"94: Goron Village (Winter)", &Entrances_Goron_Village_Winter},
        {"96: Goron Graveyard", &Entrances_Goron_Graveyard},
        {"9A: Mountain Village (Winter)", &Entrances_Mountain_Village_Winter},
        {"AE: Mountain Village (Spring)", &Entrances_Mountain_Village_Spring},
        {"B0: Path To Snowhead", &Entrances_Path_To_Snowhead},
        {"B4: Path To Goron Village (Winter)", &Entrances_Path_To_Goron_Village_Winter},
        {"B6: Path To Goron Village (Spring)", &Entrances_Path_To_Goron_Village_Spring},
        {"D0: Goron Racetrack", &Entrances_Goron_Racetrack},
    }
};

WarpsSceneMenu WarpsPlacesOverworldGreatBayMenu = {
    .title="Great Bay Overworld",
    .nbItems = 13,
    .scenes={
        {"14: Grottos", &Entrances_Lone_Peak_Shrine_And_Grottos},
        {"22: Pirates' Fortress Tower", &Entrances_Pirates_Fortress_Tower},
        {"40: Pirates' Fortress Sewers", &Entrances_Pirates_Fortress_Sewers},
        {"44: Pinnacle Rock", &Entrances_Pinnacle_Rock},
        {"46: Fairy's Fountains", &Entrances_Fairys_Fountain},
        {"58: Marine Research Lab", &Entrances_Marine_Research_Lab},
        {"60: Zora Hall Atrium", &Entrances_Zora_Hall_Atrium},
        {"68: Great Bay Coast", &Entrances_Great_Bay_Coast},
        {"6A: Zora Cape", &Entrances_Zora_Cape},
        {"70: Pirates' Fortress Moat", &Entrances_Pirates_Fortress_Moat},
        {"72: Fisherman's Hut", &Entrances_Fishermans_Hut},
        {"8E: Waterfall Rapids", &Entrances_Waterfall_Rapids},
        {"92: Zora Hall Rooms", &Entrances_Zora_Hall_Rooms}
    }
};

WarpsSceneMenu WarpsPlacesOverworldIkanaMenu = {
    .title="Ikana Canyon Overworld",
    .nbItems = 15,
    .scenes={
        {"0A: Beneath The Graveyard Iron Knuckles", &Entrances_Beneath_The_Graveyard_Iron_Knuckles},
        {"14: Grottos", &Entrances_Lone_Peak_Shrine_And_Grottos},
        {"20: Ikana Canyon", &Entrances_Ikana_Canyon},
        {"34: Ancient Castle Of Ikana", &Entrances_Ancient_Castle_Of_Ikana},
        {"46: Fairy's Fountains", &Entrances_Fairys_Fountain},
        {"5A: Beneath The Graveyard Dampe", &Entrances_Beneath_The_Graveyard_Dampe},
        {"80: Ikana Graveyard", &Entrances_Ikana_Graveyard},
        {"90: Beneath The Well", &Entrances_Beneath_The_Well},
        {"98: Sakon's Hideout", &Entrances_Sakons_Hideout},
        {"9C: Ghost Hut", &Entrances_Ghost_Hut},
        {"A0: Road To Ikana", &Entrances_Road_To_Ikana},
        {"A4: Music Box House", &Entrances_Music_Box_House},
        {"AA: Stone Tower Upright", &Entrances_Stone_Tower_Upright},
        {"AC: Stone Tower Inverted", &Entrances_Stone_Tower_Inverted},
        {"BA: Secret Shrine", &Entrances_Secret_Shrine}
    }
};

WarpsSceneMenu WarpsPlacesOverworldTerminaMenu = {
    .title="Termina Overworld",
    .nbItems = 7,
    .scenes={
        {"06: Romani Ranch Buildings", &Entrances_Ranch},
        {"14: Grottos", &Entrances_Lone_Peak_Shrine_And_Grottos},
        {"3E: Milk Road", &Entrances_Milk_Road},
        {"4C: Observatory", &Entrances_Astral_Observatory},
        {"54: Termina", &Entrances_Termina_Field},
        {"64: Romani Ranch", &Entrances_Romani_Ranch},
        {"CE: Gorman Track", &Entrances_Gorman_Track}
    }
};

WarpsSceneMenu WarpsPlacesTownsMenu = {
    .title="Clock Town Entrances",
    .nbItems = 19,
    .scenes={
        {"00: South Clock Town", &Entrances_Mayors_Residence},
        {"08: Honey and Darling's", &Entrances_Honey_And_Darlings_Shop},
        {"0E: Curiousity Shop", &Entrances_Curiosity_Shop},
        {"24: Milk Bar", &Entrances_Milk_Bar},
        {"28: Treasure Chest Shop", &Entrances_Treasure_Chest_Shop},
        {"2C: Clock Tower Rooftop", &Entrances_Clock_Tower_Rooftop},
        {"36: Deku Playground", &Entrances_Deku_Scrub_Playground},
        {"3A: Town Shooting Gallery", &Entrances_Town_Shooting_Gallery},
        {"46: Fairy's Fountain", &Entrances_Fairys_Fountain},
        {"56: Post Office", &Entrances_Post_Office},
        {"62: Trading Post", &Entrances_Trading_Post},
        {"6C: Lottery Shop", &Entrances_Lottery_Shop},
        {"A2: Swordsman's School", &Entrances_Swordsmans_School},
        {"BC: Stock Pot Inn", &Entrances_Stock_Pot_Inn},
        {"CA: Bomb Shop", &Entrances_Bomb_Shop},
        {"D2: East Clock Town", &Entrances_East_Clock_Town},
        {"D4: West Clock Town", &Entrances_West_Clock_Town},
        {"D6: North Clock Town", &Entrances_North_Clock_Town},
        {"D8: South Clock Town", &Entrances_South_Clock_Town},
        {"DA: Laundry Pool", &Entrances_Laundry_Pool},
        {"C0: Clock Tower Inside", &Entrances_Clock_Tower_Inside},
    }
};

WarpsSceneMenu WarpsPlacesDungeonsMenu = {
    .title="Dungeons",
    .nbItems = 5,
    .scenes={
        {"26: Stone Tower Temple Upright", &Entrances_Stone_Tower_Temple_Upright},
        {"2A: Stone Tower Temple Inverted", &Entrances_Stone_Tower_Temple_Inverted},
        {"30: Woodfall Temple", &Entrances_Woodfall_Temple},
        {"3C: Snowhead Temple", &Entrances_Snowhead_Temple},
        {"8C: Great Bay Temple", &Entrances_Great_Bay_Temple},   
    }
};

WarpsSceneMenu WarpsPlacesBossesMenu = {
    .title="Boss Rooms",
    .nbItems = 6,
    .scenes={
         {"01: Majora's Lair", &Entrances_Majoras_Lair},
         {"38: Odolwa's Lair", &Entrances_Odolwas_Lair},
         {"66: Twinmold's Lair", &Entrances_Twinmolds_Lair},
         {"82: Goht's Lair", &Entrances_Gohts_Lair},
         {"A6: Igos Du Ikana's Lair", &Entrances_Igos_Du_Ikanas_Lair},
         {"B8: Gyorg's Lair", &Entrances_Gyorgs_Lair},
    }
};

WarpsSceneMenu WarpsPlacesShopsMenu = {
    .title="Shops",
    .nbItems = 9,
    .scenes={
        {"02: Hag's Potion Shop", &Entrances_Hags_Potion_Shop},
        {"04: Honey & Darling's Shop", &Entrances_Honey_And_Darlings_Shop},
        {"0E: Curiosity Shop", &Entrances_Curiosity_Shop},
        {"28: Treasure Chest Shop", &Entrances_Treasure_Chest_Shop},
        {"42: Swamp Shooting Gallery", &Entrances_Swamp_Shooting_Gallery},
        {"52: Mountain Smithy", &Entrances_Mountain_Smithy},
        {"6C: Lottery Shop", &Entrances_Lottery_Shop},
        {"74: Goron Shop", &Entrances_Goron_Shop},
        {"CA: Bomb Shop", &Entrances_Bomb_Shop},
    }
};

WarpsSceneMenu WarpsPlacesHousesMenu = {
    .title="Houses",
    .nbItems = 6,
    .scenes={
        {"00: Mayor's House", &Entrances_Mayors_Residence},
        {"03: Mama's House & Barn", &Entrances_Ranch},
        {"72: Fisherman's Hut", &Entrances_Fishermans_Hut},
        {"7C: Doggy Racetrack", &Entrances_Doggy_Racetrack},
        {"7E: Cucco Shack", &Entrances_Cucco_Shack},
        {"A4: Music Box House", &Entrances_Music_Box_House},
    }
};

WarpsSceneMenu WarpsPlacesMiscMenu = {
    .title="Misc Places/Cutscenes",
    .nbItems = 6,
    .scenes={
       {"10: Test Scenes", &Entrances_Test_Scene},
       {"1C: Cutscenes", &Entrances_Cutscene_Scene},
       {"2E: Deku Intro Scene", &Entrances_Deku_Intro_Scene},
       {"BE: Pirates Cutscene Scene", &Entrances_Pirates_Cutscene_Scene},
       {"C4: Lost Woods", &Entrances_Lost_Woods},
       {"CC: Giants' Chamber", &Entrances_Giants_Chamber},
    }
};

WarpsSceneMenu WarpsSpiderHouses = {
    .title="Spider Houses",
    .nbItems = 2,
    .scenes={
       {"48: Swamp Spider House", &Entrances_Swamp_Spider_House},
       {"4A: Oceanside Spider House", &Entrances_Oceanside_Spider_House},
    }
};

WarpsSceneMenu WarpsMoon = {
    .title="Moon Trials",
    .nbItems = 6,
    .scenes={
       {"01: Majora's Lair", &Entrances_Majoras_Lair},
       {"4E: Deku Trial", &Entrances_Deku_Trial},
       {"78: Goron Trial", &Entrances_Goron_Trial},
       {"88: Zora Trial", &Entrances_Zora_Trial},
       {"C6: Link Trial", &Entrances_Link_Trial},
       {"C8: The Moon", &Entrances_The_Moon},
    }
};

const WarpsPlacesMenuEntry placesMenuEntries[] = {
    {"Dungeons", &WarpsPlacesDungeonsMenu},
    {"Bosses", &WarpsPlacesBossesMenu},
    {"Towns", &WarpsPlacesTownsMenu},
    {"Houses", &WarpsPlacesHousesMenu},
    {"Shops", &WarpsPlacesShopsMenu},
    {"Misc", &WarpsPlacesMiscMenu},
    {"Termina Overworld", &WarpsPlacesOverworldTerminaMenu},
    {"Swamp Overworld", &WarpsPlacesOverworldSwampMenu},
    {"Snowhead Overworld", &WarpsPlacesOverworldSnowHeadMenu},
    {"Great Nay Overworld", &WarpsPlacesOverworldGreatBayMenu},
    {"Ikana Overworld", &WarpsPlacesOverworldIkanaMenu},
    {"Spider Houses", &WarpsSpiderHouses},
    {"Moon", &WarpsMoon},
};

const s32 WarpsPlacesMenuSize = 13;

void WarpsPlacesMenuShow(void){
    s32 selected = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Places");

        for (s32 i = 0; i < WarpsPlacesMenuSize; ++i)
        {

            Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, placesMenuEntries[i].title);
            Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, i == selected ? '>' : ' ');
        }

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & BUTTON_B)
            break;
        if(pressed & BUTTON_A)
        {
            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();

            WarpsSceneMenuShow(placesMenuEntries[selected].menu);

            Draw_Lock();
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            Draw_Unlock();
        }
        else if(pressed & BUTTON_DOWN)
        {
            selected++;
        }
        else if(pressed & BUTTON_UP)
        {
            selected--;
        }

        if(selected < 0)
            selected = WarpsPlacesMenuSize - 1;
        else if(selected >= WarpsPlacesMenuSize) selected = 0;

    } while(true);
}


void ManuallyEnterEntranceIndex(void){
    s32 selected = 0;
    u16 chosenIndex = 0x0000;
    u32 chosen = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do
    {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Manually Enter Entrance Index");

        //Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_CsIdx, COLOR_TITLE, selected == Manual_Entrance_Menu_CsIdx ? '>' : ' ');

        Draw_DrawFormattedString(30, 30 + SPACING_Y * Manual_Entrance_Menu_EtcIdx, COLOR_WHITE,
            "Entrance Index: 0x%04X", chosenIndex);
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_EtcIdx, COLOR_TITLE, selected == Manual_Entrance_Menu_EtcIdx ? '>' : ' ');

        Draw_DrawString(30, 30 + SPACING_Y * Manual_Entrance_Menu_Go, COLOR_WHITE, "Go");
        Draw_DrawCharacter(10, 30 + SPACING_Y * Manual_Entrance_Menu_Go, COLOR_TITLE, selected == Manual_Entrance_Menu_Go ? '>' : ' ');

        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if(pressed & BUTTON_B && !chosen)
            break;
        else if(pressed & BUTTON_B && chosen)
        {
            chosen = 0;
        }
        else if(pressed & BUTTON_A && !chosen)
        {
            if(selected == Manual_Entrance_Menu_EtcIdx){
                chosen = 1;
            }
            else if(selected == Manual_Entrance_Menu_Go){
                EntranceWarp(chosenIndex);
                svcExitThread();
                break;
            }
        }
        else if(pressed & BUTTON_A && chosen)
        {
            chosen = 0;
        }
        else if(pressed & BUTTON_DOWN && !chosen)
        {
            selected++;
        }
        else if(pressed & BUTTON_DOWN && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex--;
        }
        else if(pressed & BUTTON_UP && !chosen)
        {
            selected--;
        }
        else if(pressed & BUTTON_UP && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex++;
        }
        else if(pressed & BUTTON_LEFT && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex -= 16;
        }
        else if(pressed & BUTTON_RIGHT && chosen && selected == Manual_Entrance_Menu_EtcIdx){
            chosenIndex += 16;
        }
        if(selected < 0)
            selected = Manual_Entrance_Menu_Go;

    } while(true);
}

// void ClearCutscenePointer(void){
//     static u32 nullCS[] = { 0, 0 };
//     gGlobalContext->csCtx.segment = &nullCS;
// }