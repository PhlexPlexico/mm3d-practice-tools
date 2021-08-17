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
  #define PZ3D_VERSION 1
  typedef struct {
    u8 pzversion;
    game::SaveData save;
    game::CommonDataSub1 csub1;
    game::RespawnData respawn;
    game::act::PosRot linkcoords;
    u16 angle;
  } MemFileT;

  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
  Result File_SaveProfile(Command*);
  Result File_SaveWatches(Watch*);
  Result File_SaveContextToSD(game::CommonData*, game::act::Player*, s32);
  json File_WriteCommandListToJson(Command*);
  json File_WriteWatchesToJson(Watch*);
  Result File_WriteStringFileToSd(const char*, char[]);
  Result File_WriteMemFileToSd(MemFileT*, const char*);
  Result File_ReadFromJsonFile(json*, char[]);
  Result File_ReadMemFileFromSd(MemFileT*, const char*);
  Result File_DeleteFileFromSd(char[]);
}
