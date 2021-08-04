extern "C" {
  #include <3ds/services/fs.h>
  #include <3ds/result.h>
}
#include <nlohmann/json.hpp>
#include "common/utils.h"
#include "menus/commands.h"
#include "common/debug.h"
namespace msys {
  using json = nlohmann::json;
  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
  bool File_SaveProfile(Command*);
  json File_WriteCommandListToJson(Command*);
  bool File_WriteStringFileToSd(const char*, char[]);
  Result File_ReadCommandListFromJson(json*, char[]);
}
