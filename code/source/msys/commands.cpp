extern "C" {
#include <3ds/services/fs.h>
#include <string.h>
}
#include <stdarg.h>
#include "common/advanced_context.h"
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

// Five steps, each up to "cs-right" plus a separator, and room to spare.
#define COMBO_STRING_MAX 64
// Fixed columns, so a long title cannot shove the others off screen. The
// longest title ends at x=186 and the screen is 320 wide at 6px per character,
// which leaves the list view 18 characters for a combo -- enough for the short
// names, not the long ones.
#define COMBO_COLUMN_X 190
#define STRICT_COLUMN_X 302
  rnd::AdvanceState& advState = rnd::GetAdvState();
  rnd::Context context;
  void save_test();
  static game::act::Player* GetPlayer() {
    context = rnd::GetContext();
    return context.gctx->GetPlayerActor();
  }

  static void GetContext() {
    context = rnd::GetContext();
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

/*
 * Stored positions, and the transient banner that reports what just happened.
 *
 * One slot was never enough to compare two approaches to the same trick, so
 * there are several and the active one is cycled with its own commands. Which
 * slot is current is only visible when it changes, so the banner says so for a
 * couple of seconds rather than taking up screen permanently.
 */
#define TOAST_FRAMES 120

#define SLOT_REPEAT_FRAMES 8

  static u32 slotCooldown = 0;

  StoredPosition storedPositions[POSITION_SLOTS];
  static u32 currentSlot = 0;

  static char toastText[40];
  static u32 toastFrames = 0;

  static void Toast(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(toastText, sizeof(toastText), fmt, args);
    va_end(args);
    toastFrames = TOAST_FRAMES;
  }

  /*
   * Drawn where PAUSED goes, which is free whenever this has anything to say:
   * pausing stops the render hook this is called from, so the two never compete
   * for the line. Counts down as it draws, so a frozen game holds the message
   * rather than expiring it unseen.
   */
  void Commands_DrawToast(void) {
    if (toastFrames == 0)
      return;
    --toastFrames;
    Draw_DrawFormattedStringTop(20, 20, COLOR_WHITE, "%-34s", toastText);
    Draw_FlushFramebufferTop();
  }

  void Positions_Init(void) {
    if (File_CheckOrCreateProfileDirectory())
      File_LoadPositions(storedPositions);
  }

  static void Command_StorePos(void) {
    game::act::Player* link = GetPlayer();
    if (!link)
      return;
    storedPositions[currentSlot].pos = link->pos;
    storedPositions[currentSlot].angle = link->actor_shape.rot.y;
    storedPositions[currentSlot].used = 1;
    // Written through rather than left for the SD menu: a stored position is no
    // use if it only survives until the console is turned off, and storing is a
    // deliberate press, so the write happens where a brief pause is expected.
    const bool saved = R_SUCCEEDED(File_SavePositions(storedPositions));
    Toast("Stored position %u%s", currentSlot + 1, saved ? "" : " (not saved)");
  }

  static void Command_LoadPos(void) {
    game::act::Player* link = GetPlayer();
    if (!link)
      return;
    if (!storedPositions[currentSlot].used) {
      Toast("Position %u is empty", currentSlot + 1);
      return;
    }
    link->pos = storedPositions[currentSlot].pos;
    link->initial_pos = storedPositions[currentSlot].pos;
    link->ztarget_pos = storedPositions[currentSlot].pos;
    link->actor_shape.rot.y = storedPositions[currentSlot].angle;
    Toast("Loaded position %u", currentSlot + 1);
  }

  static void Command_CycleSlot(s32 by) {
    if (slotCooldown)
      return;
    slotCooldown = SLOT_REPEAT_FRAMES;
    currentSlot = (currentSlot + POSITION_SLOTS + by) % POSITION_SLOTS;
    Toast("Position %u%s", currentSlot + 1, storedPositions[currentSlot].used ? "" : " (empty)");
  }

  static void Command_PreviousPos(void) {
    Command_CycleSlot(-1);
  }

  static void Command_NextPos(void) {
    Command_CycleSlot(1);
  }

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

  static void Commands_ListInitDefaults(void) {
    if (msys::File_CheckOrCreateProfileDirectory()) {
      /*
       * Was thirteen near-identical blocks indexing a JSON object by command
       * title. The binary profile keeps that name-keyed behaviour -- so
       * reordering commandList cannot rebind anyone's controls -- but the
       * matching now happens once inside File_LoadProfile.
       */
      if (!R_SUCCEEDED(msys::File_LoadProfile(commandList))) {
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

        // Not L+R+X: that is the third step of the Reset Input combo, so a
        // three-step command ending there fires partway through a reset.
        commandList[12].comboLen = 4;  // Previous Position
        commandList[12].inputs[0] = BUTTON_L1;
        commandList[12].inputs[1] = (BUTTON_L1 | BUTTON_R1);
        commandList[12].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN);
        commandList[12].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN | BUTTON_LEFT);
        commandList[12].strict = 0;

        commandList[13].comboLen = 4;  // Next Position
        commandList[13].inputs[0] = BUTTON_L1;
        commandList[13].inputs[1] = (BUTTON_L1 | BUTTON_R1);
        commandList[13].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN);
        commandList[13].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_DOWN | BUTTON_RIGHT);
        commandList[13].strict = 0;
      }
      rnd::util::Print("%s: Reset combo coming up!\n", __func__);
      // Always reset this one, whatever the profile said -- it is the way back
      // out of a broken binding. COMMAND_RESET_INDEX rather than a literal, since
      // it has to track the end of the table.
      commandList[COMMAND_RESET_INDEX].comboLen = 5;
      commandList[COMMAND_RESET_INDEX].inputs[0] = BUTTON_L1;
      commandList[COMMAND_RESET_INDEX].inputs[1] = (BUTTON_L1 | BUTTON_R1);
      commandList[COMMAND_RESET_INDEX].inputs[2] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X);
      commandList[COMMAND_RESET_INDEX].inputs[3] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X | BUTTON_B);
      commandList[COMMAND_RESET_INDEX].inputs[4] = (BUTTON_L1 | BUTTON_R1 | BUTTON_X | BUTTON_B | BUTTON_LEFT);
      commandList[COMMAND_RESET_INDEX].strict = 0;
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
      {"Pause/Unpause", 0, 0, {0}, Command_PauseUnpause, COMMAND_PRESS_TYPE, 0, 0},
      {"Frame Advance", 0, 0, {0}, Command_FrameAdvance, COMMAND_PRESS_TYPE, 0, 0},
      //{"Toggle Hitbox View (TODO)", 0, 0, {0}, Command_HitboxView, COMMAND_PRESS_TYPE, 0, 0},
      {"Toggle Watches", 0, 0, {0}, Command_ToggleWatches, COMMAND_PRESS_TYPE, 0, 0},
      {"Previous Position", 0, 0, {0}, Command_PreviousPos, COMMAND_PRESS_ONCE_TYPE, 0, 0},
      {"Next Position", 0, 0, {0}, Command_NextPos, COMMAND_PRESS_ONCE_TYPE, 0, 0},
      {"Reset Input", 0, 0, {0}, Commands_ListInitDefaults, COMMAND_PRESS_TYPE, 0, 0},
  };

  static u32 commandInit = 0;
  void Command_UpdateCommands(u32 curInputs) {  // curInputs should be all the held and pressed
                                                // buttons
    if (!commandInit) {
      Commands_ListInitDefaults();
      commandInit = 1;
    }

    if (slotCooldown)
      --slotCooldown;

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
                 ((commandList[i].strict && curInputs == commandList[i].inputs[commandList[i].curIdx - 1]) ||
                  (!commandList[i].strict &&
                   (curInputs & commandList[i].inputs[commandList[i].curIdx - 1]) ==
                       commandList[i].inputs[commandList[i].curIdx - 1]))) {  // case where inputs still held

        commandList[i].waiting = 0;
      } else {  // case where command resets
        commandList[i].curIdx = 0;
        commandList[i].waiting = 0;
      }
    }
  }

  /// Names for every input that can appear in a combo. The short form is for the
  /// list, where a long title leaves 18 characters; the long form is for the
  /// editor, which has a line to itself.
  static const struct {
    u32 mask;
    const char* shortName;
    const char* longName;
  } kInputNames[] = {
      {BUTTON_A, "A", "A"},           {BUTTON_B, "B", "B"},
      {BUTTON_X, "X", "X"},           {BUTTON_Y, "Y", "Y"},
      {BUTTON_L1, "L", "L"},          {BUTTON_R1, "R", "R"},
      {BUTTON_ZL, "ZL", "ZL"},        {BUTTON_ZR, "ZR", "ZR"},
      {BUTTON_START, "St", "Start"},  {BUTTON_SELECT, "Se", "Select"},
      {BUTTON_UP, "^", "Up"},         {BUTTON_DOWN, "v", "Down"},
      {BUTTON_LEFT, "<", "Left"},     {BUTTON_RIGHT, ">", "Right"},
      {CPAD_UP, "c^", "cp-up"},       {CPAD_DOWN, "cv", "cp-down"},
      {CPAD_LEFT, "c<", "cp-left"},   {CPAD_RIGHT, "c>", "cp-right"},
      {CSTICK_UP, "s^", "cs-up"},     {CSTICK_DOWN, "sv", "cs-down"},
      {CSTICK_LEFT, "s<", "cs-left"}, {CSTICK_RIGHT, "s>", "cs-right"},
  };

  /// Append as much of `text` as still fits, always leaving room for the NUL.
  static void AppendBounded(char* buf, u32 len, const char* text) {
    u32 at = strlen(buf);
    while (*text && at + 1 < len)
      buf[at++] = *text++;
    buf[at] = '\0';
  }

  /*
   * Render a combo, naming only what each step adds: "L, R, Select" long, or
   * "L R Se" short. Steps that add two inputs at once are joined with '+'.
   *
   * This used to be one character per step, which showed a circle pad direction
   * as a numpad digit with no way to say which way it went. It also meant the
   * fifth step was never displayed at all -- both format strings had four %c.
   */
  static void Commands_ComboToString(char* buf, u32 len, u32 commandIdx, bool verbose) {
    u32 prevInput = 0;
    buf[0] = '\0';

    for (u32 i = 0; i < commandList[commandIdx].comboLen && i < COMMAND_COMBO_MAX; ++i) {
      const u32 newInput = commandList[commandIdx].inputs[i] & ~prevInput;
      prevInput = commandList[commandIdx].inputs[i];

      if (i)
        AppendBounded(buf, len, verbose ? ", " : " ");

      bool first = true;
      for (u32 k = 0; k < sizeof(kInputNames) / sizeof(kInputNames[0]); ++k) {
        if (!(newInput & kInputNames[k].mask))
          continue;
        if (!first)
          AppendBounded(buf, len, "+");
        AppendBounded(buf, len, verbose ? kInputNames[k].longName : kInputNames[k].shortName);
        first = false;
      }
      // An input with no name, rather than a silently empty step.
      if (first)
        AppendBounded(buf, len, "?");
    }
  }

  static void Commands_EditCommand(u32 commandIndex) {
    u32 selected = 0;
    u32 editing = 0;
    u32 curColor = COLOR_WHITE;
    char comboString[COMBO_STRING_MAX];

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Edit Command: %s", commandList[commandIndex].title);

      Commands_ComboToString(comboString, sizeof(comboString), commandIndex, true);
      Draw_DrawFormattedString(30, 30, curColor, "Combo: %-41s", comboString);
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
        } else if (pressed & (MENU_DOWN | MENU_UP)) {
          selected = (selected + 1) % 2;
        }
      } else {
        for (u32 secs = COMMAND_COMBO_TIMEOUT; secs > 0; --secs) {
          Draw_Lock();
          Draw_DrawFormattedString(300, 10, COLOR_RED, "%u", secs);
          Draw_FlushFramebuffer();
          Draw_Unlock();

          // No repeat here: each step is one press, and a held input must not
          // record a new step every 75 ms.
          u32 pressed = waitInputNoRepeat(1000);
          if (!pressed) {
            editing = (secs > 1);
            curColor = (editing ? COLOR_RED : COLOR_WHITE);
            continue;
          }
          u32 len = commandList[commandIndex].comboLen;
          if (len >= COMMAND_COMBO_MAX)
            break;
          const u32 combined = len > 0 ? (pressed | commandList[commandIndex].inputs[len - 1]) : pressed;
          // A step that adds nothing is not a step. It would render as '?' and
          // consume one of the five slots.
          if (len > 0 && combined == commandList[commandIndex].inputs[len - 1])
            continue;
          commandList[commandIndex].inputs[len] = combined;
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
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Commands   S=strict  START=defaults");
      for (s32 i = 0; i < COMMAND_MENU_MAX_SHOW && page * COMMAND_MENU_MAX_SHOW + i < (COMMAND_NUM_COMMANDS - 1); ++i) {
        char comboString[COMBO_STRING_MAX];
        s32 j = page * COMMAND_MENU_MAX_SHOW + i;
        Commands_ComboToString(comboString, sizeof(comboString), j, false);
        Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s:", commandList[j].title);
        Draw_DrawString(COMBO_COLUMN_X, 30 + i * SPACING_Y, COLOR_WHITE, comboString);
        Draw_DrawCharacter(STRICT_COLUMN_X, 30 + i * SPACING_Y, COLOR_WHITE, commandList[j].strict ? 'S' : 'R');
        Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
      }

      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B)
        break;
      if (pressed & BUTTON_A) {
        Commands_EditCommand(selected);
      } else if (pressed & MENU_DOWN) {
        selected++;
      } else if (pressed & MENU_UP) {
        selected--;
      } else if (pressed & MENU_LEFT) {
        selected -= COMMAND_MENU_MAX_SHOW;
      } else if (pressed & MENU_RIGHT) {
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
