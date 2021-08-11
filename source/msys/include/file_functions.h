extern "C" {
  #include <3ds/services/fs.h>
  #include <3ds/result.h>
}
#include <nlohmann/json.hpp>
#include <stdio.h>
#include "common/utils.h"
#include "common/debug.h"
#include "menus/commands.h"
#include "menus/watches.h"
namespace msys {
  using json = nlohmann::json;

  #define MAX_SAVED_PROFILES 3

  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
  Result File_SaveProfile(Command*);
  Result File_SaveWatches(Watch*);
  json File_WriteCommandListToJson(Command*);
  json File_WriteWatchesToJson(Watch*);
  Result File_WriteStringFileToSd(const char*, char[]);
  Result File_ReadCommandListFromJson(json*, char[]);
}
