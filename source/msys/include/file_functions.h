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
    game::SaveData save;
    game::PlayerData playerdata;
    game::EquipmentData equipdata;
    game::InventoryData inventory;
    game::CommonDataSub1 csub1;
    game::CommonDataSub3 csub3;
    game::CommonDataSub4 csub4;
    game::CommonDataSub5 csub5;
    game::CommonDataSub6 csub6;
    game::CommonDataSub7 csub7;
    game::CommonDataSub8 csub8;
    game::CommonDataSub9 csub9;
    game::CommonDataSub10 csub10;
    game::CommonDataSub11 csub11;
    game::CommonDataSub12 csub12;
    game::RespawnData respawn;
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
