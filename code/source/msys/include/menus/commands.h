#pragma once

#include "game/actor.h"

#include "msys/include/menu.h"

#define COMMAND_COMBO_MAX 5
#define POSITION_SLOTS 8
#define COMMAND_COMBO_TIMEOUT 3
#define COMMAND_MENU_MAX_SHOW 18
#define COMMAND_NUM_COMMANDS 15
/*
 * Reset Input is last and is excluded from the editable list -- it is the way
 * out of a binding that has locked you out, so it is not itself rebindable.
 *
 * The defaults below are set by index while saved profiles are keyed by name,
 * so inserting a command in the middle of the table silently rebinds the
 * defaults of everything after it. Append, do not insert.
 */
#define COMMAND_RESET_INDEX (COMMAND_NUM_COMMANDS - 1)

namespace msys {
  typedef enum {
    COMMAND_HOLD_TYPE,        // command works as long as combo is held
    COMMAND_PRESS_TYPE,       // command can be repeated with only the final input
    COMMAND_PRESS_ONCE_TYPE,  // command is only repeated after redoing full combo
  } commandType;

  typedef struct Command {
    const char* title;

    u32 comboLen;
    u32 curIdx;
    u32 inputs[COMMAND_COMBO_MAX];
    void (*method)(void);
    commandType type;
    u32 waiting;  // to prevent press types from re-executing. unused for other types
    u32 strict;   // whether the button combo is strict or not
  } Command;
  extern Command commandList[];

  /// A stored position. Slots are identified by index, not by name, so the file
  /// is a plain array with a used flag rather than keyed entries.
  typedef struct {
    u8 used;
    game::act::PosRot pos;
    u16 angle;
  } StoredPosition;
  extern StoredPosition storedPositions[POSITION_SLOTS];

  void Commands_ShowCommands(void);
  void Command_UpdateCommands(u32 inputs);
  /// Read the stored positions back off the SD card at startup.
  void Positions_Init(void);
  /// Transient banner reporting the last command action; call once per frame.
  void Commands_DrawToast(void);
}  // namespace msys
