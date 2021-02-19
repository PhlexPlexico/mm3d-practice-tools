/*
 *   This file is a modified part of Luma3DS
 *   Copyright (C) 2016-2019 Aurora Wright, TuxSH
 *   Modified 2020 Gamestabled
 *
 *   Modified 2021 PhlexPlexico
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */


#include "msys/include/3ds/os.h"
#include "msys/include/menus.h"
#include "msys/include/menu.h"
#include "msys/include/draw.h"

#include "msys/include/menus/warps.h"
#include "msys/include/menus/scene.h"
#include "msys/include/menus/cheats.h"
#include "msys/include/menus/inventory.h"
#include "msys/include/menus/equips.h"
#include "msys/include/menus/file.h"
#include "msys/include/menus/watches.h"
#include "msys/include/menus/debug.h"
#include "msys/include/menus/commands.h"
#include "../game/common_data.h"

void pz3DMenu_Test(void){
  auto& cdata = game::GetCommonData();
  cdata.save.time = 1024;
  return;
}

Menu pz3DMenu{
    .title="MM3D Practice Menu",
    .nbItems=4,
    .items{
        { .title="Test method placeholder, change time to 6am", .action_type=METHOD, .method=&pz3DMenu_Test },
        // { .title="Warps", .action_type=MENU, .menu=&WarpsMenu },
        // { .title="Scene", .action_type=MENU, .menu=&SceneMenu },
        { .title="Cheats", .action_type=MENU, .menu=&CheatsMenu },
        // { .title="Inventory", .action_type=MENU, .menu=&InventoryMenu },
        { .title="Equips", .action_type=MENU, .menu=&EquipsMenu },
        // // { "File", .action_type=MENU, .menu=&FileMenu },
        // { .title="Watches", .action_type=METHOD, .method=&WatchesMenuFunc },
        // { .title="Debug", .action_type=MENU, .menu=&DebugMenu },
        { .title="Commands", .action_type=METHOD, .method=Commands_ShowCommands }
    }
};

