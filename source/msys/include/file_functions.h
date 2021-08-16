extern "C" {
  #include <3ds/services/fs.h>
  #include <3ds/result.h>
}
#include <nlohmann/json.hpp>
#include <stdio.h>
#include "common/utils.h"
#include "common/debug.h"
#include "game/common_data.h"
#include "game/actor.h"
#include "menus/commands.h"
#include "menus/watches.h"

namespace msys {
  using json = nlohmann::json;

  #define MAX_SAVED_PROFILES 3
  #define PZ3D_MEMFILE_MAX 3

  typedef struct {
    game::CommonData file;
    //game::act::DayTimerActor daytime;
    u8 evening;
    u8 unk_1F9;
    u16 time;
    u16 unk_1FE;
    u32 daytimer_calc;
    u32 unk_208;
  } MemFileT;

  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
  Result File_SaveProfile(Command*);
  Result File_SaveWatches(Watch*);
  Result File_SaveContextToSD(game::CommonData*, game::act::DayTimerActor*, s32);
  json File_WriteCommandListToJson(Command*);
  json File_WriteWatchesToJson(Watch*);
  Result File_WriteStringFileToSd(const char*, char[]);
  Result File_WriteMemFileToSd(MemFileT*, const char*);
  Result File_ReadFromJsonFile(json*, char[]);
  Result File_ReadMemFileFromSd(MemFileT*, const char*);
  Result File_DeleteFileFromSd(char[]);
}
