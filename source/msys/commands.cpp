extern "C" {
#include <3ds/services/fs.h>
}
#include "common/context.h"
#include "common/hidstate.h"
#include "common/utils.h"
#include "game/common_data.h"
#include "game/states/state.h"
#include "game/static_context.h"
#include "msys/include/MyThread.h"
#include "msys/include/draw.h"
#include "msys/include/entrances.h"
#include "msys/include/file_functions.h"
#include "msys/include/menu.h"
#include "msys/include/menus/commands.h"
#include "msys/include/menus/debug.h"
#include "msys/include/menus/inventory.h"
#include "msys/include/menus/warps.h"
#include "msys/include/menus/watches.h"

namespace msys {
rst::AdvanceState& advState = rst::GetAdvState();
rst::Context context;
void save_test();
static game::act::Player* GetPlayer() {
  context = rst::GetContext();
  return context.gctx->GetPlayerActor();
}

static void GetContext() {
  context = rst::GetContext();
}

static void Command_OpenMenu(void) {
  MyThread* menuThread = menuCreateThread();
  MyThread_Join(menuThread, -1LL);
  advState.menuExitFlag = 1;
}

static void Command_Levitate(void) {
  game::act::Player* link = GetPlayer();
  if (link) {
    link->vel_y = 6.34375f;
  }
}

static void Command_Fall(void) {
  game::act::Player* link = GetPlayer();
  if (link) {
    link->pos.pos.y = -4096.f;
    link->pos.pos.x = -4096.f;
    link->ztarget_pos.pos.y = -4096.f;
    link->ztarget_pos.pos.x = -4096.f;
    link->vel_y = 0.0f;
    link->vel_xz = 0.0f;
    link->vel.x = 0.0f;
    link->vel.y = 0.0f;
  }
}

static void Command_RunFast(void) {
  game::act::Player* link = GetPlayer();
  if (link) {
    link->lin_vel = 27.f;
  }
}

static void Command_Reset(void) {
  GetContext();
  // Could be file select or title screen? File Select works for now since important flags seem to
  // reset?
  context.gctx->ChangeState(game::StateType::FileSelect);
}

static void Command_ReloadScene(void) {
  GetContext();
  if (!context.gctx || context.gctx->type != game::StateType::Play)
    return;

  game::CommonData& cdata = game::GetCommonData();
  msys::EntranceWarp(cdata.sub1.entrance);
}

static void Command_VoidOut(void) {
  GetContext();
  context.gctx->VoidPlayer();
}

static game::act::PosRot storedPosRot;
static u16 angle;
static void Command_StorePos(void) {
  game::act::Player* link = GetPlayer();
  if (link) {
    storedPosRot = link->pos;
    angle = link->angle;
  }
}

static void Command_LoadPos(void) {
  game::act::Player* link = GetPlayer();
  if (link) {
    link->pos = storedPosRot;
    link->initial_pos = storedPosRot;
    link->ztarget_pos = storedPosRot;
    link->angle = angle;
  }
}

// static void Command_PreviousPos(void);
// static void Command_NextPos(void);

static void Command_PauseUnpause(void) {
  advState.pauseUnpause = true;
}

static void Command_FrameAdvance(void) {
  advState.frameAdvance = true;
}

// static void Command_RecordMacro(void);
// static void Command_PlayMacro(void);
// static void Command_CollisionView(void);
// static void Command_HitboxView(void) {
//   // Possible TODO?
//   // gStaticContext.collisionDisplay = !gStaticContext.collisionDisplay;
// }

static void Command_ToggleWatches(void) {
  advState.showWatches = !advState.showWatches;
  toggleWatches();
}

static void Commands_InsertCombos(u32 curCommand, nlohmann::basic_json<>* inputs) {
  u32 i = 0;
  for (nlohmann::json::iterator it = inputs->begin(); it != inputs->end(); ++it) {
    commandList[curCommand].inputs[i] = (u32)*it;
    i++;
  }
}

static void Commands_ListInitDefaults(void) {
  if (msys::File_CheckOrCreateProfileDirectory()) {
    nlohmann::json tmpJson;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.json";
    if (R_SUCCEEDED(msys::File_ReadFromJsonFile(&tmpJson, path))) {
      commandList[0].comboLen = (u32)tmpJson["Open Menu"]["comboLength"];
      Commands_InsertCombos(0, &tmpJson["Open Menu"]["inputs"]);
      commandList[0].strict = (u32)tmpJson["Open Menu"]["strict"];

      commandList[1].comboLen = (u32)tmpJson["Levitate"]["comboLength"];
      Commands_InsertCombos(1, &tmpJson["Levitate"]["inputs"]);
      commandList[1].strict = (u32)tmpJson["Levitate"]["strict"];

      commandList[2].comboLen = (u32)tmpJson["Fast Fall"]["comboLength"];
      Commands_InsertCombos(2, &tmpJson["Fast Fall"]["inputs"]);
      commandList[2].strict = (u32)tmpJson["Fast Fall"]["strict"];

      commandList[3].comboLen = (u32)tmpJson["Run Fast"]["comboLength"];
      Commands_InsertCombos(3, &tmpJson["Run Fast"]["inputs"]);
      commandList[3].strict = (u32)tmpJson["Run Fast"]["strict"];

      commandList[4].comboLen = (u32)tmpJson["Go Back To File Select"]["comboLength"];
      Commands_InsertCombos(4, &tmpJson["Go Back To File Select"]["inputs"]);
      commandList[4].strict = (u32)tmpJson["Go Back To File Select"]["strict"];

      commandList[5].comboLen = (u32)tmpJson["Reload Scene"]["comboLength"];
      Commands_InsertCombos(5, &tmpJson["Reload Scene"]["inputs"]);
      commandList[5].strict = (u32)tmpJson["Reload Scene"]["strict"];

      commandList[6].comboLen = (u32)tmpJson["Void Out"]["comboLength"];
      Commands_InsertCombos(6, &tmpJson["Void Out"]["inputs"]);
      commandList[6].strict = (u32)tmpJson["Void Out"]["strict"];

      commandList[7].comboLen = (u32)tmpJson["Store Position"]["comboLength"];
      Commands_InsertCombos(7, &tmpJson["Store Position"]["inputs"]);
      commandList[7].strict = (u32)tmpJson["Store Position"]["strict"];

      commandList[8].comboLen = (u32)tmpJson["Load Position"]["comboLength"];
      Commands_InsertCombos(8, &tmpJson["Load Position"]["inputs"]);
      commandList[8].strict = (u32)tmpJson["Load Position"]["strict"];

      commandList[9].comboLen = (u32)tmpJson["Pause/Unpause"]["comboLength"];
      Commands_InsertCombos(9, &tmpJson["Pause/Unpause"]["inputs"]);
      commandList[9].strict = (u32)tmpJson["Pause/Unpause"]["strict"];

      commandList[10].comboLen = (u32)tmpJson["Frame Advance"]["comboLength"];
      Commands_InsertCombos(10, &tmpJson["Frame Advance"]["inputs"]);
      commandList[10].strict = (u32)tmpJson["Frame Advance"]["strict"];

      commandList[11].comboLen = (u32)tmpJson["Toggle Watches"]["comboLength"];
      Commands_InsertCombos(11, &tmpJson["Toggle Watches"]["inputs"]);
      commandList[11].strict = (u32)tmpJson["Toggle Watches"]["strict"];
    } else {
      commandList[0].comboLen = 3;  // Open Menu
      commandList[0].inputs[0] = BUTTON_L1;
      commandList[0].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[0].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_SELECT);
      commandList[0].strict = 0;

      commandList[1].comboLen = 2;  // Levitate
      commandList[1].inputs[0] = BUTTON_X;
      commandList[1].inputs[1] = (BUTTON_X | BUTTON_A);
      commandList[1].strict = 1;

      commandList[2].comboLen = 4;  // Fast Fall
      commandList[2].inputs[0] = BUTTON_L1;
      commandList[2].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[2].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN);
      commandList[2].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN | BUTTON_Y);
      commandList[2].strict = 0;

      commandList[3].comboLen = 2;  // Run Fast
      commandList[3].inputs[0] = BUTTON_X;
      commandList[3].inputs[1] = (BUTTON_X | BUTTON_Y);
      commandList[3].strict = 1;

      commandList[4].comboLen = 2;  // Goto File Select
      commandList[4].inputs[0] = BUTTON_Y;
      commandList[4].inputs[1] = (BUTTON_Y | BUTTON_A);
      commandList[4].strict = 1;

      commandList[5].comboLen = 4;  // Reload Scene
      commandList[5].inputs[0] = BUTTON_L1;
      commandList[5].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[5].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN);
      commandList[5].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN | BUTTON_A);
      commandList[5].strict = 0;

      commandList[6].comboLen = 4;  // Void Out
      commandList[6].inputs[0] = BUTTON_L1;
      commandList[6].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[6].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN);
      commandList[6].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN | BUTTON_B);
      commandList[6].strict = 0;

      commandList[7].comboLen = 3;  // Store Pos
      commandList[7].inputs[0] = BUTTON_L1;
      commandList[7].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[7].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_LEFT);
      commandList[7].strict = 0;

      commandList[8].comboLen = 3;  // Load Pos
      commandList[8].inputs[0] = BUTTON_L1;
      commandList[8].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[8].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_RIGHT);
      commandList[8].strict = 0;

      commandList[9].comboLen = 3;  // Pause/Unpause
      commandList[9].inputs[0] = BUTTON_L1;
      commandList[9].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[9].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_UP);
      commandList[9].strict = 0;

      commandList[10].comboLen = 1;  // Frame Advance
      commandList[10].inputs[0] = BUTTON_UP;
      commandList[10].strict = 0;

      commandList[11].comboLen = 3;  // Toggle Watches
      commandList[11].inputs[0] = BUTTON_L1;
      commandList[11].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[11].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_START);
      commandList[11].strict = 0;
    }
    rst::util::Print("%s: Reset combo coming up!", __func__);
    commandList[12].comboLen = 5;  // Reset inputs.
    commandList[12].inputs[0] = BUTTON_L1;
    commandList[12].inputs[1] = (BUTTON_L1 | BUTTON_R1);
    commandList[12].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X);
    commandList[12].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X | BUTTON_B);
    commandList[12].inputs[4] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X | BUTTON_B | BUTTON_LEFT);
    commandList[12].strict = 0;
  }
}

Command commandList[] = {
    {"Open Menu", 0, 0, {0}, Command_OpenMenu, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Levitate", 0, 0, {0}, Command_Levitate, COMMAND_HOLD_TYPE, 0, 1},
    {"Fast Fall", 0, 0, {0}, Command_Fall, COMMAND_HOLD_TYPE, 0, 0},
    {"Run Fast", 0, 0, {0}, Command_RunFast, COMMAND_HOLD_TYPE, 0, 1},
    {"Go Back To File Select", 0, 0, {0}, Command_Reset, COMMAND_PRESS_ONCE_TYPE, 0, 1},
    {"Reload Scene", 0, 0, {0}, Command_ReloadScene, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Void Out", 0, 0, {0}, Command_VoidOut, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Store Position", 0, 0, {0}, Command_StorePos, COMMAND_PRESS_TYPE, 0, 0},
    {"Load Position", 0, 0, {0}, Command_LoadPos, COMMAND_PRESS_TYPE, 0, 0},
    // {"Previous Position", 0, 0, { 0 }, Command_PreviousPos, COMMAND_PRESS_TYPE, 0},
    // {"Next Position", 0, 0, { 0 }, Command_NextPos, COMMAND_PRESS_TYPE, 0},
    {"Pause/Unpause", 0, 0, {0}, Command_PauseUnpause, COMMAND_PRESS_TYPE, 0, 0},
    {"Frame Advance", 0, 0, {0}, Command_FrameAdvance, COMMAND_PRESS_TYPE, 0, 0},
    //{"Toggle Hitbox View (TODO)", 0, 0, {0}, Command_HitboxView, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Watches", 0, 0, {0}, Command_ToggleWatches, COMMAND_PRESS_TYPE, 0, 0},
    {"Reset Input", 0, 0, {0}, Commands_ListInitDefaults, COMMAND_PRESS_TYPE, 0, 0},
};

static u32 commandInit = 0;
void Command_UpdateCommands(u32 curInputs) {  // curInputs should be all the held and pressed
                                              // buttons
  if (!commandInit) {
    Commands_ListInitDefaults();
    commandInit = 1;
  }

  for (int i = 0; i < COMMAND_NUM_COMMANDS; i++) {
    if (commandList[i].comboLen == 0)
      continue;
    if ((commandList[i].strict && curInputs == commandList[i].inputs[commandList[i].curIdx]) ||
        (!commandList[i].strict &&
         (curInputs & commandList[i].inputs[commandList[i].curIdx]) ==
             commandList[i].inputs[commandList[i].curIdx])) {  // case where we hit the new button

      commandList[i].curIdx++;
      if (commandList[i].curIdx == commandList[i].comboLen) {  // time to execute the command
        if (commandList[i].type == COMMAND_HOLD_TYPE) {
          commandList[i].method();
          commandList[i].curIdx = commandList[i].comboLen - 1;
        } else if (commandList[i].type == COMMAND_PRESS_ONCE_TYPE) {
          commandList[i].method();
          commandList[i].curIdx = 0;
        } else if (commandList[i].type == COMMAND_PRESS_TYPE) {
          if (commandList[i].waiting == 0) {
            commandList[i].method();
            commandList[i].waiting = 1;
          }
          commandList[i].curIdx = commandList[i].comboLen - 1;
        }
      }
    } else if (commandList[i].curIdx > 0 &&
               ((commandList[i].strict &&
                 curInputs == commandList[i].inputs[commandList[i].curIdx - 1]) ||
                (!commandList[i].strict &&
                 (curInputs & commandList[i].inputs[commandList[i].curIdx - 1]) ==
                     commandList[i]
                         .inputs[commandList[i].curIdx - 1]))) {  // case where inputs still held

      commandList[i].waiting = 0;
    } else {  // case where command resets
      commandList[i].curIdx = 0;
      commandList[i].waiting = 0;
    }
  }
}

static void Commands_ComboToString(char* buf, u32 commandIdx) {
  u32 prevInput = 0;

  for (u32 i = 0; i < commandList[commandIdx].comboLen; ++i) {
    u32 newInput = commandList[commandIdx].inputs[i] & ~prevInput;
    switch (newInput) {
    case (BUTTON_A):
      buf[i] = 'A';
      break;
    case (BUTTON_B):
      buf[i] = 'B';
      break;
    case (BUTTON_X):
      buf[i] = 'X';
      break;
    case (BUTTON_Y):
      buf[i] = 'Y';
      break;
    case (BUTTON_START):
      buf[i] = 'S';
      break;
    case (BUTTON_SELECT):
      buf[i] = 's';
      break;
    case (BUTTON_UP):
      buf[i] = '^';
      break;
    case (BUTTON_DOWN):
      buf[i] = 'v';
      break;
    case (BUTTON_LEFT):
      buf[i] = '<';
      break;
    case (BUTTON_RIGHT):
      buf[i] = '>';
      break;
    case (BUTTON_L1):
      buf[i] = 'L';
      break;
    case (BUTTON_R1):
      buf[i] = 'R';
      break;
    }
    prevInput = commandList[commandIdx].inputs[i];
  }
}

static void Commands_EditCommand(u32 commandIndex) {
  u32 selected = 0;
  u32 editing = 0;
  u32 curColor = COLOR_WHITE;
  char comboString[COMMAND_COMBO_MAX + 1];

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Edit Command: %s",
                             commandList[commandIndex].title);

    Commands_ComboToString(comboString, commandIndex);
    Draw_DrawFormattedString(30, 30, curColor, "Combo: %c  %c  %c  %c",
                             commandList[commandIndex].comboLen >= 1 ? comboString[0] : ' ',
                             commandList[commandIndex].comboLen >= 2 ? comboString[1] : ' ',
                             commandList[commandIndex].comboLen >= 3 ? comboString[2] : ' ',
                             commandList[commandIndex].comboLen >= 4 ? comboString[3] : ' ');
    Draw_DrawCharacter(10, 30, COLOR_TITLE, selected == 0 ? '>' : ' ');

    Draw_DrawFormattedString(30, 30 + SPACING_Y, COLOR_WHITE, "Type: %s",
                             commandList[commandIndex].strict ? "Strict " : "Relaxed");
    Draw_DrawCharacter(10, 30 + SPACING_Y, COLOR_TITLE, selected == 1 ? '>' : ' ');

    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Use X to clear the command");

    Draw_FlushFramebuffer();
    Draw_Unlock();

    if (!editing) {
      Draw_Lock();
      Draw_DrawCharacter(300, 10, COLOR_WHITE, ' ');
      Draw_FlushFramebuffer();
      Draw_Unlock();
      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_A) {
        if (selected == 1) {
          commandList[commandIndex].strict = !commandList[commandIndex].strict;
        } else if (selected == 0) {
          editing = 1;
          curColor = COLOR_RED;
          commandList[commandIndex].comboLen = 0;
        }
      } else if (pressed & BUTTON_X) {
        commandList[commandIndex].comboLen = 0;
      } else if (pressed & BUTTON_B) {
        break;
      } else if (pressed & (BUTTON_DOWN | BUTTON_UP)) {
        selected = (selected + 1) % 2;
      }
    } else {
      for (u32 secs = COMMAND_COMBO_TIMEOUT; secs > 0; --secs) {
        Draw_Lock();
        Draw_DrawFormattedString(300, 10, COLOR_RED, "%u", secs);
        Draw_FlushFramebuffer();
        Draw_Unlock();

        u32 pressed = waitInputWithTimeout(1000);
        if (!pressed) {
          editing = (secs > 1);
          curColor = (editing ? COLOR_RED : COLOR_WHITE);
          continue;
        }
        if (commandList[commandIndex].comboLen > 0) {
          commandList[commandIndex].inputs[commandList[commandIndex].comboLen] =
              pressed | commandList[commandIndex].inputs[commandList[commandIndex].comboLen - 1];
        } else {
          commandList[commandIndex].inputs[0] = pressed;
        }
        commandList[commandIndex].comboLen++;

        if (commandList[commandIndex].comboLen >= COMMAND_COMBO_MAX) {
          editing = 0;
          curColor = COLOR_WHITE;
        }
        break;
      }
    }

  } while (true);
}

void Commands_ShowCommands(void) {
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
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Commands. Press START to restore defaults");
    for (s32 i = 0;
         i < COMMAND_MENU_MAX_SHOW && page * COMMAND_MENU_MAX_SHOW + i < (COMMAND_NUM_COMMANDS - 1);
         ++i) {
      char comboString[COMMAND_COMBO_MAX + 1];
      s32 j = page * COMMAND_MENU_MAX_SHOW + i;
      Commands_ComboToString(comboString, j);
      Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s: %c  %c  %c  %c",
                               commandList[j].title,
                               commandList[j].comboLen >= 1 ? comboString[0] : ' ',
                               commandList[j].comboLen >= 2 ? comboString[1] : ' ',
                               commandList[j].comboLen >= 3 ? comboString[2] : ' ',
                               commandList[j].comboLen >= 4 ? comboString[3] : ' ',
                               commandList[j].comboLen >= 5 ? comboString[4] : ' ');
      Draw_DrawString(200, 30 + i * SPACING_Y, COLOR_WHITE,
                      commandList[j].strict ? "Strict " : "Relaxed");
      Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
    }

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    if (pressed & BUTTON_A) {
      Commands_EditCommand(selected);
    } else if (pressed & BUTTON_DOWN) {
      selected++;
    } else if (pressed & BUTTON_UP) {
      selected--;
    } else if (pressed & BUTTON_LEFT) {
      selected -= COMMAND_MENU_MAX_SHOW;
    } else if (pressed & BUTTON_RIGHT) {
      if (selected + COMMAND_MENU_MAX_SHOW < COMMAND_NUM_COMMANDS)
        selected += COMMAND_MENU_MAX_SHOW;
      else if ((COMMAND_NUM_COMMANDS - 1) / COMMAND_MENU_MAX_SHOW == page)
        selected %= COMMAND_MENU_MAX_SHOW;
      else
        selected = COMMAND_NUM_COMMANDS - 2;
    } else if (pressed & BUTTON_START) {
      Commands_ListInitDefaults();
    }

    if (selected < 0)
      selected = COMMAND_NUM_COMMANDS - 2;
    else if (selected >= COMMAND_NUM_COMMANDS)
      selected = 0;

    pagePrev = page;
    page = selected / COMMAND_MENU_MAX_SHOW;
  } while (true);
}
}  // namespace msys
