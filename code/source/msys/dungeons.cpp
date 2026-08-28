#include "msys/include/menus/dungeons.h"
#include "game/common_data.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"

namespace msys {
#define DUNGEON_KEYS_MAX 9

  enum DungeonRow { ROW_KEYS = 0, ROW_MAP, ROW_COMPASS, ROW_BOSS_KEY, ROW_COUNT };

  typedef struct {
    const char* title;
    game::InventoryData::DungeonItems* (*items)(void);
    u8* (*keys)(void);
  } Dungeon;

  static game::InventoryData& Inv(void) {
    return game::GetCommonData().save.inventory;
  }

  // Each dungeon's two fields are separate members rather than arrays, so they
  // are reached through a pair of accessors instead of an index.
  static game::InventoryData::DungeonItems* WoodfallItems(void) {
    return &Inv().woodfall_dungeon_items;
  }
  static game::InventoryData::DungeonItems* SnowheadItems(void) {
    return &Inv().snowhead_dungeon_items;
  }
  static game::InventoryData::DungeonItems* GreatBayItems(void) {
    return &Inv().great_bay_dungeon_items;
  }
  static game::InventoryData::DungeonItems* StoneTowerItems(void) {
    return &Inv().stone_tower_dungeon_items;
  }

  static u8* WoodfallKeys(void) {
    return &Inv().woodfall_temple_keys;
  }
  static u8* SnowheadKeys(void) {
    return &Inv().snowhead_temple_keys;
  }
  static u8* GreatBayKeys(void) {
    return &Inv().great_bay_temple_keys;
  }
  static u8* StoneTowerKeys(void) {
    return &Inv().stone_tower_temple_keys;
  }

  static const Dungeon Dungeons[] = {
      {"Woodfall Temple", WoodfallItems, WoodfallKeys},
      {"Snowhead Temple", SnowheadItems, SnowheadKeys},
      {"Great Bay Temple", GreatBayItems, GreatBayKeys},
      {"Stone Tower Temple", StoneTowerItems, StoneTowerKeys},
  };

  static void Dungeons_Show(u32 index) {
    const Dungeon& dungeon = Dungeons[index];
    s32 selected = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      game::InventoryData::DungeonItems* items = dungeon.items();
      u8* keys = dungeon.keys();

      Draw_Lock();
      Draw_DrawString(10, 10, COLOR_TITLE, dungeon.title);

      Draw_DrawFormattedString(30, 30 + ROW_KEYS * SPACING_Y, COLOR_WHITE, "Small Keys: %u  ", *keys);
      const struct {
        const char* title;
        u32 on;
      } rows[] = {
          {"Map", items->map},
          {"Compass", items->compass},
          {"Boss Key", items->boss_key},
      };
      for (u32 i = 0; i < 3; ++i) {
        Draw_DrawFormattedString(30, 30 + (ROW_MAP + i) * SPACING_Y, COLOR_WHITE, "%s%s", rows[i].on ? "(x) " : "( ) ",
                                 rows[i].title);
      }
      for (u32 i = 0; i < ROW_COUNT; ++i)
        Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, selected == (s32)i ? '>' : ' ');

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "A toggles. Left/Right for keys.");
      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B) {
        break;
      } else if (pressed & BUTTON_A) {
        switch (selected) {
        case ROW_MAP:
          items->map = items->map ? 0 : 1;
          break;
        case ROW_COMPASS:
          items->compass = items->compass ? 0 : 1;
          break;
        case ROW_BOSS_KEY:
          items->boss_key = items->boss_key ? 0 : 1;
          break;
        default:
          break;
        }
      } else if (pressed & MENU_RIGHT) {
        if (selected == ROW_KEYS && *keys < DUNGEON_KEYS_MAX)
          ++*keys;
      } else if (pressed & MENU_LEFT) {
        if (selected == ROW_KEYS && *keys > 0)
          --*keys;
      } else if (pressed & MENU_DOWN) {
        selected++;
      } else if (pressed & MENU_UP) {
        selected--;
      }

      if (selected < 0)
        selected = ROW_COUNT - 1;
      else if (selected >= ROW_COUNT)
        selected = 0;
    } while (true);

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
  }

  static void Dungeons_Woodfall(void) {
    Dungeons_Show(0);
  }
  static void Dungeons_Snowhead(void) {
    Dungeons_Show(1);
  }
  static void Dungeons_GreatBay(void) {
    Dungeons_Show(2);
  }
  static void Dungeons_StoneTower(void) {
    Dungeons_Show(3);
  }

  Menu DungeonsMenu = {.title = "Dungeons",
                       .nbItems = 4,
                       .items = {
                           {.title = "Woodfall Temple", .action_type = METHOD, .method = Dungeons_Woodfall},
                           {.title = "Snowhead Temple", .action_type = METHOD, .method = Dungeons_Snowhead},
                           {.title = "Great Bay Temple", .action_type = METHOD, .method = Dungeons_GreatBay},
                           {.title = "Stone Tower Temple", .action_type = METHOD, .method = Dungeons_StoneTower},
                       }};

}  // namespace msys