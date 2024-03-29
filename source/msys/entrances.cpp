#include "msys/include/entrances.h"
#include "../common/context.h"
#include "../game/common_data.h"
#include "../game/scene.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"

#define ENTRANCE_MENU_MAX_SHOW 15
#define SCENE_MENU_MAX_SHOW 18

namespace msys {
rst::Context warpCtx;

static void GetContext() {
  warpCtx = rst::GetContext();
}

void EntranceWarp(u16 EntranceIndex) {
  GetContext();
  game::CommonData& cdata = game::GetCommonData();
  warpCtx.gctx->next_entrance = EntranceIndex;
  cdata.sub13s[0].entrance_index = EntranceIndex;
  warpCtx.gctx->field_C529_one_to_clear_input = 0x14;
}

void EntranceSelectMenuShow(const EntrancesByScene* entrances) {
  s32 selected = 0, page = 0, pagePrev = 0;

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    if (page != pagePrev) {
      Draw_ClearFramebuffer();
    }
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, entrances->title);
    for (u32 i = 0;
         i < ENTRANCE_MENU_MAX_SHOW && page * ENTRANCE_MENU_MAX_SHOW + i < entrances->nbItems;
         ++i) {
      s32 j = page * ENTRANCE_MENU_MAX_SHOW + i;
      Draw_DrawString(30, 30 + (i)*SPACING_Y, COLOR_WHITE, entrances->items[j].title);
      Draw_DrawCharacter(10, 30 + (i)*SPACING_Y, COLOR_TITLE, selected == (j) ? '>' : ' ');
    }

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    else if (pressed & BUTTON_A) {
      EntranceWarp(entrances->items[selected].entranceIndex);
      svcExitThread();
      break;
    } else if (pressed & BUTTON_DOWN) {
      selected++;
    } else if (pressed & BUTTON_UP) {
      selected--;
    }
    if (selected < 0)
      selected = entrances->nbItems - 1;
    else if (selected >= (int)entrances->nbItems)
      selected = 0;

    pagePrev = page;
    page = selected >= ENTRANCE_MENU_MAX_SHOW ? 1 : 0;
  } while (true);
}

void WarpsSceneMenuShow(const WarpsSceneMenu* menu) {
  s32 selected = 0, page = 0, pagePrev = 0;

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    if (page != pagePrev) {
      Draw_ClearFramebuffer();
    }
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

    for (u32 i = 0; i < SCENE_MENU_MAX_SHOW && page * SCENE_MENU_MAX_SHOW + i < menu->nbItems;
         ++i) {
      s32 j = page * SCENE_MENU_MAX_SHOW + i;
      Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, menu->scenes[j].title);
      Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
    }

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    if (pressed & BUTTON_A) {
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_FlushFramebuffer();
      Draw_Unlock();

      EntranceSelectMenuShow(menu->scenes[selected].entrances);

      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_FlushFramebuffer();
      Draw_Unlock();
    } else if (pressed & BUTTON_DOWN) {
      selected++;
    } else if (pressed & BUTTON_UP) {
      selected--;
    } else if (pressed & BUTTON_LEFT) {
      selected -= SCENE_MENU_MAX_SHOW;
    } else if (pressed & BUTTON_RIGHT) {
      if ((u32)selected + (u32)SCENE_MENU_MAX_SHOW < menu->nbItems)
        selected += SCENE_MENU_MAX_SHOW;
      else if ((menu->nbItems - 1) / SCENE_MENU_MAX_SHOW == (u32)page)
        selected %= SCENE_MENU_MAX_SHOW;
      else
        selected = menu->nbItems - 1;
    }

    if (selected < 0)
      selected = menu->nbItems - 1;
    else if ((u32)selected >= menu->nbItems)
      selected = 0;

    pagePrev = page;
    page = selected / SCENE_MENU_MAX_SHOW;
  } while (true);
}
}  // namespace msys
