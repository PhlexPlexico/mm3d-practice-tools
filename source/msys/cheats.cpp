#include "include/menus/cheats.h"
#include "common/context.h"
#include "game/common_data.h"
#include "include/menu.h"


static void Cheats_Health(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.health_current = cdata.save.player.health_max;
}

static void Cheats_Magic(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.magic = cdata.magic_max;
}

// 13 = arrow
// 18 = bombs
// 19 bombchus
// 20 is sticks!!!
// 21 is nuts
static void Cheats_Sticks(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[20] = 0x63;
}

static void Cheats_Nuts(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[21] = 0x63;
}

static void Cheats_Bombs(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[18] = 0x63;
}

static void Cheats_Arrows(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[13] = 0x63;
}

static void Cheats_Bombchus(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[19] = 0x63;
}

static void Cheats_Beans(void) {
  // TODO: Get beans id.
  // gSaveContext.ammo[ItemSlots[ITEM_MAGIC_BEANS]] = 10;
}

static void Cheats_Rupees(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.rupee_count = 500;
}

static void Cheats_FreezeTime(void) {
  // TODO
}

static void Cheats_UseItemsEverywhere(void) {
  // TODO
}

static void TimeAdvance_6AM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x4000;
  cdata.save.is_night = false;
}

static void TimeAdvance_12PM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x8000;
  cdata.save.is_night = false;
}

static void TimeAdvance_6PM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0xC000;
  cdata.save.is_night = false;
}

static void TimeAdvance_12AM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x0000;
  cdata.save.is_night = false;
}

Menu CheatsMenu = {
    .title = "Cheats",
    .nbItems = 6,
    .items = {
        {.title = "Refill Health", .action_type = METHOD, .method = Cheats_Health},
        {.title = "Refill Magic", .action_type = METHOD, .method = Cheats_Magic},
        {.title = "Refill Items", .action_type = MENU, .menu = &CheatsItemsMenu},
        {.title = "Refill Rupees", .action_type = METHOD, .method = Cheats_Rupees},
        {.title = "Change Time of Day", .action_type = MENU, .menu = &TimeChangeMenu},
        {.title = "Usable Items (TODO)",
         .action_type = METHOD,
         .method = Cheats_UseItemsEverywhere
         }
    }
};

Menu CheatsItemsMenu = {
    .title = "Items",
    .nbItems = 6,
    .items = {
        {.title = "Refill Deku Sticks", .action_type = METHOD, .method = Cheats_Sticks},
        {.title = "Refill Deku Nuts", .action_type = METHOD, .method = Cheats_Nuts},
        {.title = "Refill Bombs", .action_type = METHOD, .method = Cheats_Bombs},
        {.title = "Refill Arrows", .action_type = METHOD, .method = Cheats_Arrows},
        {.title = "Refill Bombchus", .action_type = METHOD, .method = Cheats_Bombchus},
        {.title = "Refill Beans (TODO)", .action_type = METHOD, .method = Cheats_Beans},
    }
};

Menu TimeChangeMenu = {
  .title = "Change Time of Day",
  .nbItems = 4,
  .items = {
    {.title="6AM", .action_type = METHOD, .method = TimeAdvance_6AM},
    {.title="12PM", .action_type = METHOD, .method = TimeAdvance_12PM},
    {.title="6PM", .action_type = METHOD, .method = TimeAdvance_6PM},
    {.title="12AM", .action_type = METHOD, .method = TimeAdvance_12AM}
  }
};