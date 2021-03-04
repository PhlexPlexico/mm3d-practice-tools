#include "msys/include/menus/debug.h"
#include <stdio.h>
#include "common/context.h"
#include "common/hidstate.h"
#include "game/actor.h"
#include "game/player.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"


#define ACTOR_LIST_MAX_SHOW 15

typedef struct {
  game::act::Actor* instance;
  game::act::Id id;
  s16 params;
} ShowActor_Info;


static const char* const ActorTypeNames[] = {
    "SWITCH",  // 0x0
    "BG",         "PLAYER", "EXPLOSIVES", "NPC",  "ENEMY", "PROP",
    "ITEMACTION", "MISC",   "BOSS",       "DOOR", "CHEST",
    "ALL",  // 0xC
};

/* give type 0xC for "all" */
s32 PopulateActorList(ShowActor_Info* list, game::act::Type type) {
  s32 i = 0;
  game::GlobalContext* gctx = rst::GetContext().gctx;
  for (size_t actSize = 0; actSize < gctx->actors.lists.size(); ++actSize) {
    game::ActorList& actorList = gctx->actors.lists[actSize];
    for (game::act::Actor* actor = actorList.first; actor; actor = actor->next) {
      if (type == (game::act::Type)0xC || actor->actor_type == type) {
        list[i].instance = actor;
        list[i].id = actor->id;
        list[i].params = actor->params;
        ++i;
      }
    }
  }
  return i;
}

static void DebugActors_ShowMoreInfo(game::act::Actor* actor) {
  rst::Context context = rst::GetContext();
  game::act::Player* player = context.gctx->GetPlayerActor();
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    Draw_DrawString(10, 10, COLOR_TITLE, "Actor Details");
    Draw_DrawFormattedString(30, 30, COLOR_WHITE, "ID:              %04X", actor->id);
    Draw_DrawFormattedString(30, 30 + SPACING_Y, COLOR_WHITE, "Type:            %s",
                             ActorTypeNames[(s32)actor->actor_type]);
    Draw_DrawFormattedString(30, 30 + 2 * SPACING_Y, COLOR_WHITE, "Params:          %04X",
                             actor->params & 0xFFFF);
    Draw_DrawFormattedString(30, 30 + 3 * SPACING_Y, COLOR_WHITE,
                             "Pos:             x:%05.2f  y:%05.2f  z:%05.2f", actor->pos.pos.x,
                             actor->pos.pos.y, actor->pos.pos.z);
    Draw_DrawFormattedString(30, 30 + 4 * SPACING_Y, COLOR_WHITE,
                             "Rot:             x:%04X  y:%04X  z:%04X", actor->pos.rot.x & 0xFFFF,
                             actor->pos.rot.y & 0xFFFF, actor->pos.rot.z & 0xFFFF);
    Draw_DrawFormattedString(30, 30 + 5 * SPACING_Y, COLOR_WHITE,
                             "Vel:             x:%05.2f  y:%05.2f  z:%05.2f", actor->vel.x,
                             actor->vel.y, actor->vel.z);
    // Draw_DrawFormattedString(30, 30 + 6 * SPACING_Y, COLOR_WHITE, "Floor:           %08X",
    // actor->floorPoly);
    Draw_DrawFormattedString(30, 30 + 7 * SPACING_Y, COLOR_WHITE,
                             "Dist. from Link: xz:%05.2f  y:%05.2f", actor->distance_to_link,
                             actor->height_diff_to_link);
    Draw_DrawFormattedString(30, 30 + 8 * SPACING_Y, COLOR_WHITE, "Text ID:         %04X",
                             actor->text_id_maybe & 0xFFFF);
    Draw_DrawFormattedString(30, 30 + 9 * SPACING_Y, COLOR_WHITE, "Held By:         %08X",
                             actor->child_actor);
    Draw_DrawFormattedString(30, 30 + 10 * SPACING_Y, COLOR_WHITE, "Holding:         %08X",
                             actor->parent_actor);

    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press START to bring actor to Link");

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    else if (pressed & BUTTON_START) {
      actor->pos.pos = player->pos.pos;
      actor->pos.rot = player->pos.rot;
    }

  } while (true);
}

static void DebugActors_ShowActors(void) {
  static ShowActor_Info actorList[200];
  s32 selected = 0, page = 0, pagePrev = 0;
  s32 type = 0xC;
  s32 listSize = 0;

  listSize = PopulateActorList(actorList, (game::act::Type)0xC);

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    if (page != pagePrev) {
      Draw_ClearFramebuffer();
    }
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Currently Loaded Actors");
    Draw_DrawFormattedString(30, 30, COLOR_RED, "Filter by type (R/L to move): %s",
                             ActorTypeNames[type]);

    for (s32 i = 0; i < ACTOR_LIST_MAX_SHOW && page * ACTOR_LIST_MAX_SHOW + i < listSize; ++i) {
      s32 j = page * ACTOR_LIST_MAX_SHOW + i;
      Draw_DrawFormattedString(30, 30 + (1 + i) * SPACING_Y, COLOR_WHITE, "Addr: %08X  ID: %04X",
                               actorList[j].instance, actorList[j].id);
      Draw_DrawCharacter(10, 30 + (1 + i) * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
    }

    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                    "Select with A to show more details, X to delete");

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    if (pressed & BUTTON_A) {
      DebugActors_ShowMoreInfo(actorList[selected].instance);
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_FlushFramebuffer();
      Draw_Unlock();
    }
    // else if(pressed & BUTTON_X)
    // {
    //     Actor_Kill(actorList[selected].instance);
    // }
    else if (pressed & BUTTON_DOWN) {
      selected++;
    } else if (pressed & BUTTON_UP) {
      selected--;
    } else if (pressed & BUTTON_LEFT) {
      selected -= ACTOR_LIST_MAX_SHOW;
    } else if (pressed & BUTTON_RIGHT) {
      selected += ACTOR_LIST_MAX_SHOW;
    } else if (pressed & BUTTON_R1) {
      type++;
      if (type > 0xC)
        type = 0;
      selected = 0;
      page = 0;
      pagePrev = -1;
      listSize = PopulateActorList(actorList, (game::act::Type)type);
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_FlushFramebuffer();
      Draw_Unlock();
      continue;
    } else if (pressed & BUTTON_L1) {
      type--;
      if (type < 0)
        type = 0xC;
      selected = 0;
      page = 0;
      pagePrev = -1;
      listSize = PopulateActorList(actorList, (game::act::Type)type);
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_FlushFramebuffer();
      Draw_Unlock();
      continue;
    }

    if (selected < 0) {
      selected = listSize - 1;
    } else if (selected >= listSize) {
      selected = 0;
    }

    pagePrev = page;
    page = selected / ACTOR_LIST_MAX_SHOW;

  } while (true);
}

Menu DebugMenu = {
  .title="Debug",
  .nbItems = 1,
  .items = {
    {.title = "Actors", .action_type = METHOD, .method = DebugActors_ShowActors},
  }
};
