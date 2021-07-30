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
  bool check_or_create_profile_directory();
  Handle get_handle();
  void close_handle();
  bool save_file(Command*);
  json write_to_json(Command*);
}
