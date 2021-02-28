#include "msys/include/menus/commands.h"
#include "msys/include/entrances.h"
#include "common/context.h"
#include "common/hidstate.h"
#include "common/utils.h"
#include "game/common_data.h"
#include "game/states/state.h"
#include "msys/include/MyThread.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"
#include "msys/include/menus/warps.h"
#include "msys/include/menus/watches.h"
#include "msys/include/menus/inventory.h"

rst::AdvanceState& advState = rst::GetAdvState();
rst::Context context;

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

static void Command_Fall(void) {  // TODO: Doesn't work
  game::act::Player* link = GetPlayer();
  if (link) {
    link->pos.pos.y = -4096.f;
    link->ztarget_pos.pos.y = -4096.f;
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
  // Could be file select or title screen? File Select works for now since important flags seem to reset?
  context.gctx->ChangeState(game::StateType::FileSelect);
}

static void Command_ReloadScene(void) {
  GetContext();
  if (!context.gctx || context.gctx->type != game::StateType::Play)
    return;
  
  game::CommonData& cdata = game::GetCommonData();
  EntranceWarp(cdata.sub1.entrance);

}

static void Command_VoidOut(void) {
  GetContext();
  context.gctx->VoidPlayer();
}

// static void Command_SaveState(void);
// static void Command_LoadState(void);

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
static void Command_HitboxView(void) {
  // Possible TODO?
  // gStaticContext.collisionDisplay = !gStaticContext.collisionDisplay;
}

static void Command_ToggleWatches(void) {
  advState.showWatches = !advState.showWatches;
  toggleWatches();
}

static void Command_ToggleFreeze(void) {
  advState.timeFreeze = !advState.timeFreeze;
}

static Command commandList[] = {
    {"Open Menu", 0, 0, {0}, Command_OpenMenu, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Levitate", 0, 0, {0}, Command_Levitate, COMMAND_HOLD_TYPE, 0, 0},
    {"Fall (TODO)", 0, 0, {0}, Command_Fall, COMMAND_HOLD_TYPE, 0, 0},
    {"Run Fast", 0, 0, {0}, Command_RunFast, COMMAND_HOLD_TYPE, 0, 0},
    {"Go Back To File Select", 0, 0, {0}, Command_Reset, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Reload Scene", 0, 0, {0}, Command_ReloadScene, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Void Out", 0, 0, {0}, Command_VoidOut, COMMAND_PRESS_ONCE_TYPE, 0, 0},
    {"Store Position", 0, 0, {0}, Command_StorePos, COMMAND_PRESS_TYPE, 0, 0},
    {"Load Position", 0, 0, {0}, Command_LoadPos, COMMAND_PRESS_TYPE, 0, 0},
    // {"Previous Position", 0, 0, { 0 }, Command_PreviousPos, COMMAND_PRESS_TYPE, 0},
    // {"Next Position", 0, 0, { 0 }, Command_NextPos, COMMAND_PRESS_TYPE, 0},
    {"Pause/Unpause", 0, 0, {0}, Command_PauseUnpause, COMMAND_PRESS_TYPE, 0, 0},
    {"Frame Advance", 0, 0, {0}, Command_FrameAdvance, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Hitbox View (TODO)", 0, 0, {0}, Command_HitboxView, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Watches", 0, 0, {0}, Command_ToggleWatches, COMMAND_PRESS_TYPE, 0, 0},
    {"Toggle Freeze Time", 0, 0, {0}, Command_ToggleFreeze, COMMAND_PRESS_ONCE_TYPE, 0, 0},
};

static void Commands_ListInitDefaults(void) {
  commandList[0].comboLen = 3;  // Open Menu
  commandList[0].inputs[0] = BUTTON_L1;
  commandList[0].inputs[1] = (BUTTON_L1 | BUTTON_R1);
  commandList[0].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_SELECT);
  commandList[0].strict = 0;

  commandList[1].comboLen = 2;  // Levitate
  commandList[1].inputs[0] = BUTTON_X;
  commandList[1].inputs[1] = (BUTTON_X | BUTTON_A);
  commandList[1].strict = 0;

  commandList[3].comboLen = 1;  // Run Fast
  commandList[3].inputs[0] = BUTTON_Y;
  commandList[3].strict = 0;

  commandList[4].comboLen = 2;  // Goto File Select
  commandList[4].inputs[0] = BUTTON_Y;
  commandList[4].inputs[1] = (BUTTON_Y | BUTTON_A);
  commandList[4].strict = 0;

  commandList[7].comboLen = 2;  // Store Pos
  commandList[7].inputs[0] = BUTTON_L1;
  commandList[7].inputs[1] = BUTTON_LEFT;
  commandList[7].strict = 0;

  commandList[8].comboLen = 1;  // Load Pos
  commandList[8].inputs[0] = BUTTON_RIGHT;
  commandList[8].strict = 0;

  commandList[9].comboLen = 1;  // Pause/Unpause
  commandList[9].inputs[0] = BUTTON_UP;
  commandList[9].strict = 0;

  commandList[10].comboLen = 1;  // Frame Advance
  commandList[10].inputs[0] = BUTTON_DOWN;
  commandList[10].strict = 0;

  commandList[13].comboLen = 2;  // Freeze/resume time.
  commandList[13].inputs[0] = BUTTON_LEFT;
  commandList[13].inputs[1] = (BUTTON_LEFT | BUTTON_A);
  commandList[13].strict = 0;

  for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
    if (i != 0 && i != 1 && i != 3 && i != 4 && i != 7 && i != 8 && i != 9 && i != 10 && i != 13) {
      commandList[i].comboLen = 0;
      commandList[i].strict = 0;
    }
  }
}

static u32 commandInit = 0;
// TODO - reference the inputted commands from restoration?
// Even better - grab a new shared HID handle and use that on the thread. Safer?
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
         i < COMMAND_MENU_MAX_SHOW && page * COMMAND_MENU_MAX_SHOW + i < COMMAND_NUM_COMMANDS;
         ++i) {
      char comboString[COMMAND_COMBO_MAX + 1];
      s32 j = page * COMMAND_MENU_MAX_SHOW + i;
      Commands_ComboToString(comboString, j);
      Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s: %c  %c  %c  %c",
                               commandList[j].title,
                               commandList[j].comboLen >= 1 ? comboString[0] : ' ',
                               commandList[j].comboLen >= 2 ? comboString[1] : ' ',
                               commandList[j].comboLen >= 3 ? comboString[2] : ' ',
                               commandList[j].comboLen >= 4 ? comboString[3] : ' ');
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
        selected = COMMAND_NUM_COMMANDS - 1;
    } else if (pressed & BUTTON_START) {
      Commands_ListInitDefaults();
    }

    if (selected < 0)
      selected = COMMAND_NUM_COMMANDS - 1;
    else if (selected >= COMMAND_NUM_COMMANDS)
      selected = 0;

    pagePrev = page;
    page = selected / COMMAND_MENU_MAX_SHOW;
  } while (true);
}