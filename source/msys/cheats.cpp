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
// 22 is beans
// 24 powder keg
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
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[22] = 0x63;
}

static void Cheats_PowderKegs(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.inventory.item_counts[24] = 0x63;
}

static void Cheats_Rupees(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.rupee_count = 500;
}

static void Cheats_FreezeTime(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.extra_time_speed = -2;
}

static void Cheats_NormalTime(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.extra_time_speed = 0;
}

static void Cheats_ISoTTime(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.extra_time_speed = -1;
}

static void Cheats_TimeIncreaseByOne(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.extra_time_speed++;
}

static void Cheats_TimeDecreaseByOne(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.extra_time_speed--;
}

static void Cheats_ISG(void) {
  game::GlobalContext* gctx = rst::GetContext().gctx;
  game::act::Player* player = gctx->GetPlayerActor();
  player->sword_active_timer = 0x01;
  player->sword_active = 0x01;
}

static void TimeAdvance_6AM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x4000;
}

static void TimeAdvance_12PM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x8000;
}

static void TimeAdvance_6PM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0xC000;
}

static void TimeAdvance_12AM(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.time = 0x0000;
}

static void Cheats_GoToDay0(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = 0;
}

static void Cheats_GoToDay1(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = 1;
}

static void Cheats_GoToDay2(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = 2;
}

static void Cheats_GoToDay3(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = 3;
}

static void Cheats_GoToDay4(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = 4;
  cdata.save.total_day = 5;
}

Menu CheatsMenu = {
    .title = "Cheats",
    .nbItems = 8,
    .items = {
        {.title = "Refill Health", .action_type = METHOD, .method = Cheats_Health},
        {.title = "Refill Magic", .action_type = METHOD, .method = Cheats_Magic},
        {.title = "Refill Items", .action_type = MENU, .menu = &CheatsItemsMenu},
        {.title = "Refill Rupees", .action_type = METHOD, .method = Cheats_Rupees},
        {.title = "Change Time of Day", .action_type = MENU, .menu = &TimeChangeMenu},
        {.title = "Change Flow of Time", .action_type = MENU, .menu = &TimeSpeedMenu},
        {.title = "Change Day", .action_type = MENU, .menu = &DayChangeMenu},
        {.title = "ISG", .action_type = METHOD, .method = Cheats_ISG}
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
        {.title = "Refill Beans", .action_type = METHOD, .method = Cheats_Beans},
        {.title = "Refill Powder Kegs", .action_type = METHOD, .method = Cheats_PowderKegs}
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

Menu TimeSpeedMenu = {
  .title = "Change Time Speed",
  .nbItems = 5,
  .items = {
    {.title="Freeze", .action_type = METHOD, .method = Cheats_FreezeTime},
    {.title="Normal Speed", .action_type = METHOD, .method = Cheats_NormalTime},
    {.title="Inverted Song of Time", .action_type = METHOD, .method = Cheats_ISoTTime},
    {.title="Increase Speed By One", .action_type = METHOD, .method = Cheats_TimeIncreaseByOne},
    {.title="Decrease Speed By One", .action_type = METHOD, .method = Cheats_TimeDecreaseByOne}
  }
};

Menu DayChangeMenu = {
  .title = "Change Day",
  .nbItems = 5,
  .items = {
    {.title="Day 0", .action_type = METHOD, .method = Cheats_GoToDay0},
    {.title="Day 1", .action_type = METHOD, .method = Cheats_GoToDay1},
    {.title="Day 2", .action_type = METHOD, .method = Cheats_GoToDay2},
    {.title="Day 3", .action_type = METHOD, .method = Cheats_GoToDay3},
    {.title="Day 4", .action_type = METHOD, .method = Cheats_GoToDay4}
  }
};