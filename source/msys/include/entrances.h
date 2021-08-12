#pragma once

#include "../../game/scene.h"

namespace msys {
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
    .items = {{0x0000, "From East Clock Town"}, {0x0001, "From After Couple's Mask"}}};

const EntrancesByScene Entrances_Majoras_Lair = {
    .title = "Majora's Lair", .nbItems = 1, .items = {{0x0200, "From Moon"}}};

const EntrancesByScene Entrances_Ranch = {
    .title = "Romani Ranch Buildings",
    .nbItems = 2,
    .items = {{0x0600, "Barn From Ranch"}, {0x0610, "House From Ranch"}}};

const EntrancesByScene Entrances_Hags_Potion_Shop = {
    .title = "Hag's Potion Shop", .nbItems = 1, .items = {{0x0400, "From Southern Swamp"}}};

const EntrancesByScene Entrances_Swamp_Poison = {.title = "Poison Swamp Entrances",
                                                 .nbItems = 11,
                                                 .items = {{0x8400, "From Road to Southern Swamp"},
                                                           {0x8410, "From Tourist Information"},
                                                           {0x8420, "From Woodfall"},
                                                           {0x8430, "Deku Palace"},
                                                           {0x8440, "Deku Palace (Shortcut)"},
                                                           {0x8450, "Hag's Potion Shop"},
                                                           {0x8460, "From Starting Boat Cruise"},
                                                           {0x8470, "From Woods of Mystery"},
                                                           {0x8480, "from Swamp Spiderhouse"},
                                                           {0x8490, "From Ikana Canyon"},
                                                           {0x84A0, "From Owl Statue"}}};

const EntrancesByScene Entrances_Honey_And_Darlings_Shop = {
    .title = "Honey And Darling's Shop", .nbItems = 1, .items = {{0x0800, "from East Clock Town"}}};

const EntrancesByScene Entrances_Beneath_The_Graveyard_Iron_Knuckles = {
    .title = "Beneath The Graveyard Iron Knuckles",
    .nbItems = 2,
    .items = {{0x0A00, "from Night 2 grave"}, {0x0A10, "from Night 1 grave"}}};

const EntrancesByScene Entrances_Southern_Swamp_Clear = {
    .title = "Southern Swamp Clear",
    .nbItems = 11,
    .items = {{0x0C00, "from Road to Southern Swamp"},
              {0x0C10, "from Tourist Information"},
              {0x0C20, "from Woodfall"},
              {0x0C30, "from Deku Palace (front doorway)"},
              {0x0C40, "from Deku Palace (Woodfall Shortcut)"},
              {0x0C50, "from Hags' Potion Shop"},
              {0x0C60, "starting boat cruise"},
              {0x0C70, "from Woods of Mystery"},
              {0x0C80, "from Swamp Spiderhouse"},
              {0x0C90, "from Ikana Canyon"},
              {0x0CA0, "from owl statue"}}};

const EntrancesByScene Entrances_Curiosity_Shop = {
    .title = "Curiosity Shop",
    .nbItems = 4,
    .items = {{0x0E00, "from West Clock Town"},
              {0x0E10, "from Laundry Pool"},
              {0x0E20, "peeking into front room"},
              {0x0E30, "after peeking into front room"}}};

const EntrancesByScene Entrances_Test_Scene = {
    .title = "Test Scene", .nbItems = 1, .items = {{0x1000, "standing on red checkerboard"}}};

const EntrancesByScene Entrances_Lone_Peak_Shrine_And_Grottos = {
    .title = "Lone Peak Shrine And Grottos",
    .nbItems = 17,
    .items = {{0x1400, "Bay Gossips"},
              {0x1410, "Swamp Gossips"},
              {0x1420, "Canyon Gossips"},
              {0x1430, "Mountain Gossips"},
              {0x1440, "Generic Grotto"},
              {0x1450, "Hot Spring Water Grotto"},
              {0x1460, "Flat JP Grotto from Right Palace"},
              {0x1470, "Dodongo Grotto"},
              {0x1480, "Vines JP Grotto from Right Palace"},
              {0x1490, "Business Scrub Grotto"},
              {0x14A0, "Cows Grotto"},
              {0x14B0, "Bio Deku Baba Grotto"},
              {0x14C0, "Magic Bean Seller"},
              {0x14D0, "Pea Hat Grotto"},
              {0x14E0, "Flat JP Grotto from Left Palace"},
              {0x14F0, "Vines JP Grotto from Left Palace"},
              {0x1410, "Swamp Gossips"}}};

const EntrancesByScene Entrances_Cutscene_Scene = {
    .title = "Cutscene Scene",
    .nbItems = 10,
    .items = {{0x1C00, "Intro Story (black screen with white text)"},
              {0x1C10, "Epona in Lost Woods (player has control)"},
              {0x1C20, "(crash)"},
              {0x1C30, "(crash)"},
              {0x1C40, "(crash)"},
              {0x1C50, "(crash)"},
              {0x1C60, "(crash)"},
              {0x1C70, "(crash)"},
              {0x1C80, "(crash)"},
              {0x1C90, "(crash)"}}};

const EntrancesByScene Entrances_Ikana_Canyon = {
    .title = "Ikana Canyon",
    .nbItems = 16,
    .items = {{0x2000, "central room from Road to Ikana"},
              {0x2010, "central room from Ghost Hut"},
              {0x2020, "central room from Music Box House"},
              {0x2030, "central room from Stone Tower"},
              {0x2040, "central room from owl statue"},
              {0x2050, "well room from Beneath the Well"},
              {0x2060, "Business Scrub room from Sakon's Hideout"},
              {0x2070, "central room after beating Stone Tower Temple"},
              {0x2080, "central room from Ancient Castle of Ikana"},
              {0x2090, "central room after playing Song of Storms (cutscene)"},
              {0x20A0, "Sharp's cave after playing Song of Storms (cutscene)"},
              {0x20B0, "central room from Fairy's Fountain"},
              {0x20C0, "waterfall room from Secret Shrine"},
              {0x20D0, "central room from Sharp's Cave"},
              {0x20E0, "Sharp's cave from central room"},
              {0x20F0, "(table overflow)"}}};

const EntrancesByScene Entrances_Pirates_Fortress_Tower = {
    .title = "Pirates' Fortress Tower",
    .nbItems = 15,
    .items = {{0x2200, "from target platform over moat (intro)"},
              {0x2210, "from hookshot room (staircase door)"},
              {0x2220, "from hookshot room (bridge door)"},
              {0x2230, "from awkward jump stealth room"},
              {0x2240, "from awkward jump egg room"},
              {0x2250, "from jumpslash recoil stealth room"},
              {0x2260, "from jumpslash recoil egg room"},
              {0x2270, "from pirate fight stealth room"},
              {0x2280, "from pirate fight egg room"},
              {0x2290, "out of bounds near pirate fight egg room"},
              {0x22A0, "looking through sewers telescope"},
              {0x22B0, "out of bounds near target platform over moat"},
              {0x22C0, "from barrel platform over moat"},
              {0x22D0, "from target platform over moat (no intro)"},
              {0x22E0, "(crash)"}}};

const EntrancesByScene Entrances_Milk_Bar = {
    .title = "Milk Bar", .nbItems = 1, .items = {{0x2400, "from East Clock Town"}}};

const EntrancesByScene Entrances_Stone_Tower_Temple_Upright = {
    .title = "Stone Tower Temple Upright",
    .nbItems = 2,
    .items = {{0x2600, "from Stone Tower (intro)"}, {0x2610, "from Stone Tower (no intro)"}}};

const EntrancesByScene Entrances_Treasure_Chest_Shop = {
    .title = "Treasure Chest Shop",
    .nbItems = 2,
    .items = {{0x2800, "from East Clock Town"}, {0x2810, "after treasure chest game ends"}}};

const EntrancesByScene Entrances_Stone_Tower_Temple_Inverted = {
    .title = "Stone Tower Temple Inverted",
    .nbItems = 3,
    .items = {
        {0x2A00, "from Stone Tower"}, {0x2A10, "after opening boss door"}, {0x2A20, "(crash)"}}};

const EntrancesByScene Entrances_Clock_Tower_Rooftop = {
    .title = "Clock Tower Rooftop",
    .nbItems = 3,
    .items = {{0x2C00, "from South Clock Town"},
              {0x2C10, "after learning Song of Time"},
              {0x2C20, "(crash)"}}};

const EntrancesByScene Entrances_Deku_Intro_Scene = {
    .title = "Deku Intro Scene",
    .nbItems = 5,
    .items = {{0x2E00, "from Lost Woods (cutscene)"},
              {0x2E10, "from Clock Tower Interior"},
              {0x2E20, "after transforming to Deku (cutscene)"},
              {0x2E30, "after voiding in Deku Butler's son's room"},
              {0x2E40, "after first SoT (cutscene)"}}};

const EntrancesByScene Entrances_Woodfall_Temple = {
    .title = "Woodfall Temple",
    .nbItems = 3,
    .items = {{0x3000, "front room from Woodfall"},
              {0x3010, "Deku Princess's room after beating Woodfall Temple"},
              {0x3020, "Deku Princess's room from Woodfall"}}};

const EntrancesByScene Entrances_Path_To_Mountain_Village = {
    .title = "Path To Mountain Village",
    .nbItems = 2,
    .items = {{0x3200, "from Termina Field"}, {0x3210, "from Mountain Village"}}};

const EntrancesByScene Entrances_Ancient_Castle_Of_Ikana = {
    .title = "Ancient Castle Of Ikana",
    .nbItems = 7,
    .items = {{0x3400, "courtyard from Beneath the Well"},
              {0x3410, "courtyard from Ikana Canyon"},
              {0x3420, "courtyard from front doorway"},
              {0x3430, "inside from front doorwary"},
              {0x3440, "inside from powder keg hole"},
              {0x3450, "inside from elegy block hole"},
              {0x3460, "inside from Igos du Ikana's Lair"}}};

const EntrancesByScene Entrances_Deku_Scrub_Playground = {
    .title = "Deku Scrub Playground",
    .nbItems = 2,
    .items = {{0x3600, "from North Clock Town"}, {0x3610, "after Deku Playground game ends"}}};

const EntrancesByScene Entrances_Odolwas_Lair = {
    .title = "Odolwa's Lair", .nbItems = 1, .items = {{0x3800, "from Woodfall Temple"}}};

const EntrancesByScene Entrances_Town_Shooting_Gallery = {
    .title = "Town Shooting Gallery",
    .nbItems = 2,
    .items = {{0x3A00, "from East Clock Town (with title card)"},
              {0x3A10, "from East Clock Town (no title card)"}}};

const EntrancesByScene Entrances_Snowhead_Temple = {
    .title = "Snowhead Temple",
    .nbItems = 2,
    .items = {{0x3C00, "from Snowhead (intro)"}, {0x3C10, "from Snowhead (no intro)"}}};

const EntrancesByScene Entrances_Milk_Road = {
    .title = "Milk Road",
    .nbItems = 7,
    .items = {{0x3E00, "from Termina Field"},
              {0x3E10, "from Romani Ranch"},
              {0x3E20, "from Gorman Track rear (fence)"},
              {0x3E30, "from Gorman Track front"},
              {0x3E40, "from owl statue"},
              {0x3E50, "from Romani Ranch after cart ride"},
              {0x3E60, "from Gorman Track after cart ride"}}};

const EntrancesByScene Entrances_Pirates_Fortress_Sewers = {
    .title = "Pirates' Fortress Sewers",
    .nbItems = 16,
    .items = {
        {0x4000, "hookshot room (chest floor)"},
        {0x4010, "hookshot room (overlook)"},
        {0x4020, "awkward jump stealth room"},
        {0x4030, "awkward jump egg room"},
        {0x4040, "jumpslash recoil stealth room"},
        {0x4050, "jumpslash recoil egg room"},
        {0x4060, "pirate fight stealth room"},
        {0x4070, "pirate fight egg room"},
        {0x4080, "after looking through sewers telescope"},
        {0x4090, "sewers from underwater gate"},
        {0x40A0, "sewers from hookshot target platform door"},
        {0x40B0, "hookshot room (chest floor) with jumpslash recoil fight room (room 0) loaded"},
        {0x40C0, "(crash)"},
        {0x40D0, "(crash)"},
        {0x40E0, "(crash)"},
        {0x40F0, "(crash)"}}};

const EntrancesByScene Entrances_Swamp_Shooting_Gallery = {
    .title = "Swamp Shooting Gallery", .nbItems = 1, .items = {{0x4200, "from Southern Swamp"}}};

const EntrancesByScene Entrances_Pinnacle_Rock = {
    .title = "Pinnacle Rock",
    .nbItems = 2,
    .items = {{0x4400, "from Great Bay Coast"}, {0x4410, "from swimming in murky water"}}};

const EntrancesByScene Entrances_Fairys_Fountain = {
    .title = "Fairy's Fountain",
    .nbItems = 10,
    .items = {{0x4600, "from North Clock Town"},
              {0x4610, "from Woodfall"},
              {0x4620, "from Snowhead"},
              {0x4630, "from Zora Cape"},
              {0x4640, "from Ikana Canyon"},
              {0x4650, "after Magic Power"},
              {0x4660, "after Spin Attack"},
              {0x4670, "after double Magic Power"},
              {0x4680, "after double defense"},
              {0x4690, "after Great Fairy's Sword"}}};

const EntrancesByScene Entrances_Swamp_Spider_House = {
    .title = "Swamp Spider House", .nbItems = 1, .items = {{0x4800, "from Southern Swamp"}}};

const EntrancesByScene Entrances_Oceanside_Spider_House = {
    .title = "Oceanside Spider House", .nbItems = 1, .items = {{0x4A00, "from Great Bay Coast"}}};

const EntrancesByScene Entrances_Astral_Observatory = {
    .title = "Astral Observatory",
    .nbItems = 3,
    .items = {{0x4C00, "from East Clock Town"},
              {0x4C10, "from Termina Field"},
              {0x4C20, "after looking through observatory telescope"}}};

const EntrancesByScene Entrances_Deku_Trial = {
    .title = "Deku Trial", .nbItems = 1, .items = {{0x4E00, "from The Moon"}}};

const EntrancesByScene Entrances_Deku_Palace = {
    .title = "Deku Palace",
    .nbItems = 11,
    .items = {{0x5000, "from Southern Swamp (front doorway)"},
              {0x5010, "being thrown out"},
              {0x5020, "from Deku King's Chamber (king's quarters)"},
              {0x5030, "from Deku King's Chamber (monkey cell)"},
              {0x5040, "from Deku Shrine"},
              {0x5050, "from Southern Swamp (Woodfall Shortcut)"},
              {0x5060, "left palace from JP Vines Grotto"},
              {0x5070, "left palace from JP Flat Grotto"},
              {0x5080, "right palace from JP Flat Grotto"},
              {0x5090, "from Magic Bean Seller's Grotto"},
              {0x50A0, "right palace from JP Vines Grotto"}}};

const EntrancesByScene Entrances_Mountain_Smithy = {
    .title = "Mountain Smithy", .nbItems = 1, .items = {{0x5200, "from Mountain Village"}}};

const EntrancesByScene Entrances_Termina_Field = {
    .title = "Termina Field",
    .nbItems = 15,
    .items = {{0x5400, "from West Clock Town"},
              {0x5410, "from Road to Southern Swamp"},
              {0x5420, "from Great Bay Coast"},
              {0x5430, "from Path to Mountain Village"},
              {0x5440, "from Road to Ikana"},
              {0x5450, "from Milk Road"},
              {0x5460, "from South Clock Town"},
              {0x5470, "from East Clock Town"},
              {0x5480, "from North Clock Town"},
              {0x5490, "from Astral Observatory"},
              {0x54A0, "looking through observatory telescope"},
              {0x54B0, "north of Road to Ikana"},
              {0x54C0, "moon crashing"},
              {0x54D0, "after Cremia cart ride"},
              {0x54E0, "after Skull Kid cutscene"}}};

const EntrancesByScene Entrances_Post_Office = {
    .title = "Post Office", .nbItems = 1, .items = {{0x5600, "from West Clock Town"}}};

const EntrancesByScene Entrances_Marine_Research_Lab = {
    .title = "Marine Research Lab", .nbItems = 1, .items = {{0x5800, "from Great Bay Coast"}}};

const EntrancesByScene Entrances_Beneath_The_Graveyard_Dampe = {
    .title = "Beneath The Graveyard Dampe",
    .nbItems = 2,
    .items = {{0x5A00, "from Night 3 Grave"}, {0x5A10, "from Dampe's door"}}};

const EntrancesByScene Entrances_Goron_Shrine = {
    .title = "Goron Shrine",
    .nbItems = 4,
    .items = {{0x5E00, "from Goron Village (intro)"},
              {0x5E10, "from Goron Shop"},
              {0x5E20, "after learning Lullaby"},
              {0x5E30, "from Goron Village (no intro)"}}};

const EntrancesByScene Entrances_Zora_Hall_Atrium = {
    .title = "Zora Hall Atrium",
    .nbItems = 9,
    .items = {{0x6000, "from Zora Cape underwater mouth"},
              {0x6010, "from Zora Cape turtle platform"},
              {0x6020, "from Zora shop"},
              {0x6030, "from Lulu's room"},
              {0x6040, "from Evan's room"},
              {0x6050, "from Japas' room"},
              {0x6060, "from Mikau and Tijo's room"},
              {0x6070, "in front of stage"},
              {0x6080, "after rehearsal"}}};

const EntrancesByScene Entrances_Trading_Post = {
    .title = "Trading Post",
    .nbItems = 2,
    .items = {{0x6200, "from West Clock Town (with title card)"},
              {0x6210, "from West Clock Town (no title card)"}}};

const EntrancesByScene Entrances_Romani_Ranch = {
    .title = "Romani Ranch",
    .nbItems = 12,
    .items = {{0x6400, "from Milk Road"},
              {0x6410, "getting Epona's Song"},
              {0x6420, "from Barn"},
              {0x6430, "from Mama's House"},
              {0x6440, "from Cucco Shack"},
              {0x6450, "from Doggy Racetrack"},
              {0x6460, "after defeating the aliens"},
              {0x6470, "after milk bottle"},
              {0x6480, "after the Gorman Bros. break Cremia's milk"},
              {0x6490, "after the aliens abduct the cows"},
              {0x64A0, "after Romani talking about the aliens cutscene"},
              {0x64B0, "after starting the Cremia cart ride"}}};

const EntrancesByScene Entrances_Twinmolds_Lair = {.title = "Twinmold's Lair",
                                                   .nbItems = 5,
                                                   .items = {{0x6600, "from Stone Tower Temple"},
                                                             {0x6610, "from center of arena"},
                                                             {0x6620, "(crash)"},
                                                             {0x6630, "(crash)"},
                                                             {0x6640, "(crash)"}}};

const EntrancesByScene Entrances_Great_Bay_Coast = {
    .title = "Great Bay Coast",
    .nbItems = 14,
    .items = {{0x6800, "from Termina Field"},
              {0x6810, "from Zora Cape"},
              {0x6820, "(crash)"},
              {0x6830, "from Pinnacle Rock"},
              {0x6840, "from Fisherman's Hut"},
              {0x6850, "from Pirate's Fortress"},
              {0x6860, "from swimming in murky water between Pinnacle Rock and Pirates' Fortress"},
              {0x6870, "from Marine Research Lab"},
              {0x6880, "from Oceanside Spiderhouse"},
              {0x6890, "getting Zora Mask"},
              {0x68A0, "bowing in front of Mikau's grave"},
              {0x68B0, "from owl statue"},
              {0x68C0, "being thrown out of Pirates' Fortress"},
              {0x68D0, "after jumping game ends"}}};

const EntrancesByScene Entrances_Zora_Cape = {.title = "Zora Cape",
                                              .nbItems = 10,
                                              .items = {{0x6A00, "from Great Bay Coast"},
                                                        {0x6A10, "underwater mouth from Zora Hall"},
                                                        {0x6A20, "turtle platform from Zora Hall"},
                                                        {0x6A30, "from swimming in murky water"},
                                                        {0x6A40, "from Waterfall Rapids"},
                                                        {0x6A50, "from Fairy's Fountain"},
                                                        {0x6A60, "from owl statue"},
                                                        {0x6A70, "from Great Bay Temple"},
                                                        {0x6A80, "after beating Great Bay Temple"},
                                                        {0x6A90, "falling onto turtle platform"}}};

const EntrancesByScene Entrances_Lottery_Shop = {
    .title = "Lottery Shop", .nbItems = 1, .items = {{0x6C00, "from West Clock Town"}}};

const EntrancesByScene Entrances_Pirates_Fortress_Moat = {
    .title = "Pirates' Fortress Moat",
    .nbItems = 7,
    .items = {{0x7000, "from Great Bay Coast"},
              {0x7010, "on hookshot target platform from Pirates' Fortress (tower)"},
              {0x7020, "from sewers underwater gate"},
              {0x7030, "from sewers underwater jet (one-way)"},
              {0x7040, "being thrown out"},
              {0x7050, "on barrel platform from Pirate's Fortress (tower)"},
              {0x7060, "from sewers door"}}};

const EntrancesByScene Entrances_Fishermans_Hut = {
    .title = "Fisherman's Hut", .nbItems = 1, .items = {{0x7200, "from Great Bay Coast"}}};

const EntrancesByScene Entrances_Goron_Shop = {
    .title = "Goron Shop", .nbItems = 1, .items = {{0x7400, "from Goron Shrine"}}};

const EntrancesByScene Entrances_Deku_Kings_Chamber = {
    .title = "Deku King's Chamber",
    .nbItems = 4,
    .items = {{0x7600, "king's quarters from Deku Palace"},
              {0x7610, "monkey cell from Deku Palace"},
              {0x7620, "princess apologizes to monkey (cutscene)"},
              {0x7630, "after princess apologizes to monkey"}}};

const EntrancesByScene Entrances_Goron_Trial = {
    .title = "Goron Trial", .nbItems = 1, .items = {{0x7800, "from moon"}}};

const EntrancesByScene Entrances_Road_To_Southern_Swamp = {
    .title = "Road To Southern Swamp",
    .nbItems = 3,
    .items = {{0x7A00, "from Termina Field"},
              {0x7A10, "from Southern Swamp"},
              {0x7A20, "from Swamp Shooting Gallery"}}};

const EntrancesByScene Entrances_Doggy_Racetrack = {
    .title = "Doggy Racetrack",
    .nbItems = 2,
    .items = {{0x7C00, "from Romani Ranch"}, {0x7C10, "after dog race"}}};

const EntrancesByScene Entrances_Cucco_Shack = {
    .title = "Cucco Shack",
    .nbItems = 2,
    .items = {{0x7E00, "from Romani Ranch"}, {0x7E10, "getting Bunny Hood"}}};

const EntrancesByScene Entrances_Ikana_Graveyard = {
    .title = "Ikana Graveyard",
    .nbItems = 6,
    .items = {{0x8000, "from Road to Ikana"},
              {0x8010, "from Night 3 grave"},
              {0x8020, "from Night 2 grave"},
              {0x8030, "from Night 1 grave"},
              {0x8040, "from Dampe's door"},
              {0x8050, "after defeating Captain Keeta (cutscene)"}}};

const EntrancesByScene Entrances_Gohts_Lair = {
    .title = "Goht's Lair", .nbItems = 1, .items = {{0x8200, "from Snowhead Temple"}}};

const EntrancesByScene Entrances_Woodfall = {
    .title = "Woodfall",
    .nbItems = 5,
    .items = {{0x8600, "from Southern Swamp"},
              {0x8610, "from Woodfall Temple (front room)"},
              {0x8620, "from Fairy's Fountain"},
              {0x8630, "from Woodfall Temple (deku princess's cell)"},
              {0x8640, "from owl statue"}}};

const EntrancesByScene Entrances_Zora_Trial = {
    .title = "Zora Trial",
    .nbItems = 2,
    .items = {{0x8800, "from The Moon"}, {0x8810, "from taking a wrong turn"}}};

const EntrancesByScene Entrances_Goron_Village_Spring = {
    .title = "Goron Village Spring",
    .nbItems = 5,
    .items = {{0x8A00, "from Path to Goron Village"},
              {0x8A10, "falling in front of business scrub"},
              {0x8A20, "from Goron Shrine"},
              {0x8A30, "from Lone Peak Shrine"},
              {0x8A40, "from voiding by ice platforms"}}};

const EntrancesByScene Entrances_Great_Bay_Temple = {
    .title = "Great Bay Temple",
    .nbItems = 3,
    .items = {
        {0x8C00, "from Zora Cape"}, {0x8C10, "from Pirates Cutscene Scene"}, {0x8C20, "(crash)"}}};

const EntrancesByScene Entrances_Waterfall_Rapids = {.title = "Waterfall Rapids",
                                                     .nbItems = 4,
                                                     .items = {{0x8E00, "from Zora Cape"},
                                                               {0x8E10, "beaver race starting"},
                                                               {0x8E20, "beaver race ending"},
                                                               {0x8E30, "after beaver race"}}};

const EntrancesByScene Entrances_Beneath_The_Well = {
    .title = "Beneath The Well",
    .nbItems = 2,
    .items = {{0x9000, "from Ikana Canyon"}, {0x9010, "from Ancient Castle of Ikana"}}};

const EntrancesByScene Entrances_Zora_Hall_Rooms = {.title = "Zora Hall Rooms",
                                                    .nbItems = 7,
                                                    .items = {{0x9200, "Mikau and Tijo's room"},
                                                              {0x9210, "Japas' room"},
                                                              {0x9220, "Lulu's room"},
                                                              {0x9230, "Evan's room"},
                                                              {0x9240, "after jam session"},
                                                              {0x9250, "Zora shop"},
                                                              {0x9260, "getting Evan HP"}}};

const EntrancesByScene Entrances_Goron_Village_Winter = {
    .title = "Goron Village Winter",
    .nbItems = 5,
    .items = {{0x9400, "from Path to Goron Village"},
              {0x9410, "standing in front of business scrub"},
              {0x9420, "from Goron Shrine"},
              {0x9430, "from Lone Peak Shrine"},
              {0x9440, "from voiding by ice platforms"}}};

const EntrancesByScene Entrances_Goron_Graveyard = {
    .title = "Goron Graveyard",
    .nbItems = 2,
    .items = {{0x9600, "from Mountain Village"}, {0x9610, "getting Goron Mask"}}};

const EntrancesByScene Entrances_Sakons_Hideout = {
    .title = "Sakon's Hideout", .nbItems = 1, .items = {{0x9800, "from Ikana Canyon"}}};

const EntrancesByScene Entrances_Mountain_Village_Winter = {
    .title = "Mountain Village Winter",
    .nbItems = 9,
    .items = {{0x9A00, "after beating Snowhead Temple"},
              {0x9A10, "from Mountain Smithy"},
              {0x9A20, "from Path to Goron Village"},
              {0x9A30, "from Goron Graveyard"},
              {0x9A40, "from Path to Snowhead"},
              {0x9A50, "from hungry goron"},
              {0x9A60, "from Path to Mountain Village"},
              {0x9A70, "between hungry goron and Path to Snowhead"},
              {0x9A80, "from owl statue"}}};

const EntrancesByScene Entrances_Ghost_Hut = {.title = "Ghost Hut",
                                              .nbItems = 3,
                                              .items = {{0x9C00, "from Ikana Canyon"},
                                                        {0x9C10, "from poe killing game"},
                                                        {0x9C20, "after beating the poes"}}};

const EntrancesByScene Entrances_Deku_Shrine = {
    .title = "Deku Shrine",
    .nbItems = 3,
    .items = {{0x9E00, "from Deku Palace (with title card)"},
              {0x9E10, "from Deku Palace (no title card)"},
              {0x9E20, "(crash)"}}};

const EntrancesByScene Entrances_Road_To_Ikana = {.title = "Road To Ikana",
                                                  .nbItems = 3,
                                                  .items = {{0xA000, "from Termina Field"},
                                                            {0xA010, "from Ikana Canyon"},
                                                            {0xA020, "from Ikana Graveyard"},
                                                            {0xA030, "from Quill Statue"}}};

const EntrancesByScene Entrances_Swordsmans_School = {
    .title = "Swordsman's School", .nbItems = 1, .items = {{0xA200, "from East Clock Town"}}};

const EntrancesByScene Entrances_Music_Box_House = {
    .title = "Music Box House", .nbItems = 1, .items = {{0xA400, "from Ikana Canyon"}}};

const EntrancesByScene Entrances_Igos_Du_Ikanas_Lair = {
    .title = "Igos Du Ikana's Lair",
    .nbItems = 1,
    .items = {{0xA600, "from Ancient Castle of Ikana"}}};

const EntrancesByScene Entrances_Tourist_Information = {
    .title = "Tourist Information",
    .nbItems = 3,
    .items = {{0xA800, "from Southern Swamp"},
              {0xA810, "after boat cruise"},
              {0xA820, "after turning in pictograph"}}};

const EntrancesByScene Entrances_Stone_Tower_Upright = {
    .title = "Stone Tower Upright",
    .nbItems = 4,
    .items = {{0xAA00, "from Ikana Canyon"},
              {0xAA10, "after uninverting Stone Tower"},
              {0xAA20, "from Stone Tower Temple"},
              {0xAA30, "from owl statue"}}};

const EntrancesByScene Entrances_Stone_Tower_Inverted = {
    .title = "Stone Tower Inverted",
    .nbItems = 2,
    .items = {{0xAC00, "after inverting Stone Tower"}, {0xAC10, "from Stone Tower Temple"}}};

const EntrancesByScene Entrances_Mountain_Village_Spring = {
    .title = "Mountain Village Spring",
    .nbItems = 9,
    .items = {{0xAE00, "after beating Snowhead Temple"},
              {0xAE10, "from Mountain Smithy"},
              {0xAE20, "from Path to Goron Village (winter)"},
              {0xAE30, "from Goron Graveyard"},
              {0xAE40, "from Path to Snowhead"},
              {0xAE50, "behind waterfall"},
              {0xAE60, "from Path to Mountain Village"},
              {0xAE70, "falling after beating Snowhead Temple"},
              {0xAE80, "from owl statue"}}};

const EntrancesByScene Entrances_Path_To_Snowhead = {
    .title = "Path To Snowhead",
    .nbItems = 2,
    .items = {{0xB000, "from Mountain Village"}, {0xB010, "from Snowhead"}}};

const EntrancesByScene Entrances_Snowhead = {.title = "Snowhead",
                                             .nbItems = 4,
                                             .items = {{0xB200, "from Path to Snowhead"},
                                                       {0xB210, "from Snowhead Temple"},
                                                       {0xB220, "from Fairy's Fountain"},
                                                       {0xB230, "from owl statue"}}};

const EntrancesByScene Entrances_Path_To_Goron_Village_Winter = {
    .title = "Path To Goron Village Winter",
    .nbItems = 3,
    .items = {{0xB400, "from Mountain Village"},
              {0xB410, "from Goron Village"},
              {0xB420, "from Goron Racetrack"}}};

const EntrancesByScene Entrances_Path_To_Goron_Village_Spring = {
    .title = "Path To Goron Village Spring",
    .nbItems = 3,
    .items = {{0xB600, "from Mountain Village"},
              {0xB610, "from Goron Village"},
              {0xB620, "from Goron Racetrack"}}};

const EntrancesByScene Entrances_Gyorgs_Lair = {
    .title = "Gyorg's Lair",
    .nbItems = 2,
    .items = {{0xB800, "from Great Bay Temple"}, {0xB810, "falling cutscene"}}};

const EntrancesByScene Entrances_Secret_Shrine = {
    .title = "Secret Shrine", .nbItems = 1, .items = {{0xBA00, "from Ikana Canyon"}}};

const EntrancesByScene Entrances_Stock_Pot_Inn = {
    .title = "Stock Pot Inn",
    .nbItems = 6,
    .items = {{0xBC00, "from East Clock Town (front door)"},
              {0xBC10, "from East Clock Town (balcony door)"},
              {0xBC20, "after grandma's story"},
              {0xBC30, "after midnight meeting"},
              {0xBC40, "eavesdropping cutscene"},
              {0xBC50, "after eavesdropping"}}};

const EntrancesByScene Entrances_Pirates_Cutscene_Scene = {
    .title = "Pirates Cutscene Scene", .nbItems = 1, .items = {{0xBE00, "from Zora Cape"}}};

const EntrancesByScene Entrances_Clock_Tower_Inside = {
    .title = "Clock Tower Inside",
    .nbItems = 7,
    .items = {{0xC000, "from Deku Intro Scene"},
              {0xC010, "from South Clock Town"},
              {0xC020, "getting Deku Mask"},
              {0xC030, "after moon crash"},
              {0xC040, "after first SoT (cutscene)"},
              {0xC050, "in front of metal doors"},
              {0xC060, "after Majora's Mask cutscene"}}};

const EntrancesByScene Entrances_Woods_Of_Mystery = {
    .title = "Woods Of Mystery", .nbItems = 1, .items = {{0xC200, "from Southern Swamp"}}};

const EntrancesByScene Entrances_Lost_Woods = {.title = "Lost Woods",
                                               .nbItems = 3,
                                               .items = {{0xC400, "after Skull Kid steals Epona"},
                                                         {0xC410, "after first SoT (cutscene)"},
                                                         {0xC420, "(crash)"}}};

const EntrancesByScene Entrances_Link_Trial = {
    .title = "Link Trial", .nbItems = 1, .items = {{0xC600, "from moon"}}};

const EntrancesByScene Entrances_The_Moon = {
    .title = "The Moon", .nbItems = 1, .items = {{0xC800, "from Clock Tower (rooftop)"}}};

const EntrancesByScene Entrances_Bomb_Shop = {
    .title = "Bomb Shop",
    .nbItems = 2,
    .items = {{0xCA00, "from West Clock Town (with title card)"},
              {0xCA10, "from West Clock Town (no title card)"}}};

const EntrancesByScene Entrances_Giants_Chamber = {
    .title = "Giants' Chamber", .nbItems = 1, .items = {{0xCC00, "from boss lair"}}};

const EntrancesByScene Entrances_Gorman_Track = {
    .title = "Gorman Track",
    .nbItems = 6,
    .items = {{0xCE00, "from Milk Road (front)"},
              {0xCE10, "between the Gorman brothers"},
              {0xCE20, "after Gorman race"},
              {0xCE30, "from Milk Road (back) (with intro)"},
              {0xCE40, "from Milk Road (back) (no intro)"},
              {0xCE50, "on the track"}}};

const EntrancesByScene Entrances_Goron_Racetrack = {
    .title = "Goron Racetrack",
    .nbItems = 3,
    .items = {{0xD000, "from Path to Goron Village"},
              {0xD010, "starting Goron race"},
              {0xD020, "after Goron race"}}};

const EntrancesByScene Entrances_East_Clock_Town = {
    .title = "East Clock Town",
    .nbItems = 13,
    .items = {{0xD200, "from Termina Field"},
              {0xD210, "from South Clock Town (south)"},
              {0xD220, "from Astral Observatory"},
              {0xD230, "from South Clock Town (north)"},
              {0xD240, "from Treasure Chest Shop"},
              {0xD250, "from North Clock Town"},
              {0xD260, "from Honey & Darling's Shop"},
              {0xD270, "from The Mayor's Residence"},
              {0xD280, "from Town Shooting Gallery"},
              {0xD290, "from Stock Pot Inn (downstairs door)"},
              {0xD2A0, "from Stock Pot Inn (upstairs door)"},
              {0xD2B0, "from Milk Bar"},
              {0xD2C0, "(crash)"}}};

const EntrancesByScene Entrances_West_Clock_Town = {
    .title = "West Clock Town",
    .nbItems = 10,
    .items = {{0xD400, "from Termina Field"},
              {0xD410, "from South Clock Town (south)"},
              {0xD420, "from South Clock Town (north)"},
              {0xD430, "from Swordsman's School"},
              {0xD440, "from Curiosity Shop"},
              {0xD450, "from Trading Post"},
              {0xD460, "from Bomb Shop"},
              {0xD470, "from Post Office"},
              {0xD480, "from Lottery Shop"},
              {0xD490, "from Termina Field (again)"}}};

const EntrancesByScene Entrances_North_Clock_Town = {
    .title = "North Clock Town",
    .nbItems = 8,
    .items = {{0xD600, "from Termina Field"},
              {0xD610, "from East Clock Town"},
              {0xD620, "from South Clock Town"},
              {0xD630, "from Fairy's Fountain"},
              {0xD640, "from Deku Playground"},
              {0xD650, "after ending hide-and-seek"},
              {0xD660, "after starting hide-and-seek"},
              {0xD670, "after Sakon leaves"}}};

const EntrancesByScene Entrances_South_Clock_Town = {
    .title = "South Clock Town",
    .nbItems = 11,
    .items = {{0xD800, "from Clock Tower (inside)"},
              {0xD810, "from Termina Field"},
              {0xD820, "from East Clock Town (north)"},
              {0xD830, "from West Clock Town (north)"},
              {0xD840, "from North Clock Town"},
              {0xD850, "from West Clock Town (south)"},
              {0xD860, "from Laundry Pool"},
              {0xD870, "from East Clock Town (south)"},
              {0xD880, "from Clock Tower (rooftop)"},
              {0xD890, "from owl statue"},
              {0xD8A0, "after first SoT"}}};

const EntrancesByScene Entrances_Laundry_Pool = {.title = "Laundry Pool",
                                                 .nbItems = 3,
                                                 .items = {{0xDA00, "from South Clock Town"},
                                                           {0xDA10, "from Curiosity Shop"},
                                                           {0xDA20, "(crash)"}}};

}  // namespace msys
