#include "include/menus/cheats.h"
#include "common/hidstate.h"
#include "game/common_data.h"
#include "include/draw.h"
#include "include/menu.h"

namespace msys {


static void Cheats_Health(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.health_current = cdata.save.player.health_max;
}

static void Cheats_Magic(void) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.player.magic = cdata.magic_max;
}

// 6 = arrow
// 11 = bombs
// 12 bombchus
// 13 is sticks!!!
// 14 is nuts
// 15 is beans
// 17 powder keg
/*
 * Consumables, held full rather than topped up once.
 *
 * Indices into InventoryData::item_counts. Powder kegs are index 17, one past
 * the 17-element array, so the write lands in the field that follows -- which
 * is what the game itself does; the array bound in our header is the thing
 * that is wrong. Going through a byte pointer keeps that explicit instead of
 * relying on an out-of-range std::array index.
 */
enum InfiniteItem {
  INF_STICKS = 0,
  INF_NUTS,
  INF_BOMBS,
  INF_ARROWS,
  INF_BOMBCHUS,
  INF_BEANS,
  INF_POWDER_KEGS,
  INF_COUNT,
};

static const u8 ItemCountSlot[INF_COUNT] = {13, 14, 11, 6, 12, 15, 17};
#define ITEM_COUNT_FULL 0x63

/// Called every frame, so a consumable is full before the next use rather than
/// only at the moment the menu was opened.
void Cheats_ApplyInfiniteItems(void) {
  const rnd::AdvanceState& advState = rnd::GetAdvState();
  if (!advState.infiniteItems)
    return;
  game::CommonData& cdata = game::GetCommonData();
  u8* counts = &cdata.save.inventory.item_counts[0];
  for (u32 i = 0; i < INF_COUNT; ++i) {
    if (advState.infiniteItems & (1u << i))
      counts[ItemCountSlot[i]] = ITEM_COUNT_FULL;
  }
}

static void Cheats_ToggleInfinite(s32 selected) {
  rnd::AdvanceState& advState = rnd::GetAdvState();
  if (selected < 0 || selected >= INF_COUNT)
    return;
  advState.infiniteItems ^= (1u << selected);
  CheatsItemsMenu.items[selected].on = (advState.infiniteItems >> selected) & 1;
}

static void Cheats_ItemsMenuFunc(void) {
  const rnd::AdvanceState& advState = rnd::GetAdvState();
  for (u32 i = 0; i < INF_COUNT; ++i)
    CheatsItemsMenu.items[i].on = (advState.infiniteItems >> i) & 1;
  ToggleMenuShow(&CheatsItemsMenu);
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
  rnd::AdvanceState& advState = rnd::GetAdvState();
  advState.useISG = !advState.useISG;
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

/*
 * day and total_day move together. The dawn transition (0x138C78) increments
 * both by one, the game's own final-day setup (0x1BFE28) writes 4 to each, and
 * resetCycleFlags zeroes both at the start of a cycle.
 *
 * Setting day alone left total_day stale -- and going to day 4 set it to 5,
 * which nothing in the game does -- so the next dawn counted from the wrong
 * base.
 */
static void Cheats_SetDay(int day) {
  game::CommonData& cdata = game::GetCommonData();
  cdata.save.day = day;
  cdata.save.total_day = day;
}

static void Cheats_GoToDay0(void) {
  Cheats_SetDay(0);
}

static void Cheats_GoToDay1(void) {
  Cheats_SetDay(1);
}

static void Cheats_GoToDay2(void) {
  Cheats_SetDay(2);
}

static void Cheats_GoToDay3(void) {
  Cheats_SetDay(3);
}

static void Cheats_GoToDay4(void) {
  Cheats_SetDay(4);
}



















Menu CheatsMenu = {
    .title = "Cheats",
    .nbItems = 8,
    .items = {
        {.title = "Refill Health", .action_type = METHOD, .method = Cheats_Health},
        {.title = "Refill Magic", .action_type = METHOD, .method = Cheats_Magic},
        {.title = "Infinite Items", .action_type = METHOD, .method = Cheats_ItemsMenuFunc},
        {.title = "Refill Rupees", .action_type = METHOD, .method = Cheats_Rupees},
        {.title = "Change Time of Day", .action_type = MENU, .menu = &TimeChangeMenu},
        {.title = "Change Flow of Time", .action_type = MENU, .menu = &TimeSpeedMenu},
        {.title = "Change Day", .action_type = MENU, .menu = &DayChangeMenu},
        {.title = "ISG", .action_type = METHOD, .method = Cheats_ISG},
    }};

ToggleMenu CheatsItemsMenu = {
    .title = "Infinite Items",
    .nbItems = INF_COUNT,
    .items = {{.on = 0, .title = "Deku Sticks", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Deku Nuts", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Bombs", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Arrows", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Bombchus", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Magic Beans", .method = Cheats_ToggleInfinite},
              {.on = 0, .title = "Powder Kegs", .method = Cheats_ToggleInfinite}}};

Menu TimeChangeMenu = {
    .title = "Change Time of Day",
    .nbItems = 4,
    .items = {{.title = "6AM", .action_type = METHOD, .method = TimeAdvance_6AM},
              {.title = "12PM", .action_type = METHOD, .method = TimeAdvance_12PM},
              {.title = "6PM", .action_type = METHOD, .method = TimeAdvance_6PM},
              {.title = "12AM", .action_type = METHOD, .method = TimeAdvance_12AM}}};

Menu TimeSpeedMenu = {
    .title = "Change Time Speed",
    .nbItems = 5,
    .items = {{.title = "Freeze", .action_type = METHOD, .method = Cheats_FreezeTime},
              {.title = "Normal Speed", .action_type = METHOD, .method = Cheats_NormalTime},
              {.title = "Inverted Song of Time", .action_type = METHOD, .method = Cheats_ISoTTime},
              {.title = "Increase Speed By One",
               .action_type = METHOD,
               .method = Cheats_TimeIncreaseByOne},
              {.title = "Decrease Speed By One",
               .action_type = METHOD,
               .method = Cheats_TimeDecreaseByOne}}};

Menu DayChangeMenu = {
    .title = "Change Day",
    .nbItems = 5,
    .items = {{.title = "Day 0", .action_type = METHOD, .method = Cheats_GoToDay0},
              {.title = "Day 1", .action_type = METHOD, .method = Cheats_GoToDay1},
              {.title = "Day 2", .action_type = METHOD, .method = Cheats_GoToDay2},
              {.title = "Day 3", .action_type = METHOD, .method = Cheats_GoToDay3},
              {.title = "Day 4", .action_type = METHOD, .method = Cheats_GoToDay4}}};


}  // namespace msys
