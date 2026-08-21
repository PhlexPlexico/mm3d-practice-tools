/*
 * Root menu.
 *
 * Menus are plain aggregates with static storage -- there is no runtime
 * registration -- so adding a feature means defining its Menu in its own .cpp,
 * declaring it in msys/include/menus/, and listing it below.
 *
 * Warps and Watches hang off as METHOD rather than MENU: both drive their own
 * display loops rather than going through the generic Menu dispatcher.
 */

#include "msys/include/menu.h"
#include "msys/include/menus.h"

#include "msys/include/menus/cheats.h"
#include "msys/include/menus/commands.h"
#include "msys/include/menus/debug.h"
#include "msys/include/menus/equips.h"
#include "msys/include/menus/inventory.h"
#include "msys/include/menus/save.h"
#include "msys/include/menus/warps.h"
#include "msys/include/menus/watches.h"

namespace msys {

  Menu pz3DMenu = {
      .title = "MM3D Practice Menu",
      .nbItems = 8,
      .items{
          {.title = "Warps", .action_type = METHOD, .method = WarpsPlacesMenuShow},
          {.title = "Cheats", .action_type = MENU, .menu = &CheatsMenu},
          {.title = "Inventory", .action_type = MENU, .menu = &InventoryMenu},
          {.title = "Equips", .action_type = MENU, .menu = &EquipsMenu},
          {.title = "Watches", .action_type = METHOD, .method = &WatchesMenuFunc},
          {.title = "Debug", .action_type = MENU, .menu = &DebugMenu},
          {.title = "Commands", .action_type = METHOD, .method = Commands_ShowCommands},
          {.title = "SD Card Functions", .action_type = MENU, .menu = &SaveMenu},
      },
  };

}  // namespace msys
