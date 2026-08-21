#include "include/menus/cheats.h"
#include "common/hidstate.h"
#include "game/common_data.h"
#include "include/draw.h"
#include "include/menu.h"

namespace msys {
static const char* const LinkModifyNames[] = {"max health (* by 16 for a total heart)",
                                              "magic", "razor sword hp", "current rupees"};

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

static void Cheats_Modify_Link(LinkData whatToModify, u16* ptrToModify) {
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();

    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Current %s:", LinkModifyNames[whatToModify]);
    Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%u", *ptrToModify);

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & (BUTTON_B | BUTTON_A)) {
      break;
    } else if (pressed & MENU_UP) {
      *ptrToModify += 1;
    } else if (pressed & MENU_DOWN) {
      if (*ptrToModify < 1)
        *ptrToModify = 0;
      else
        *ptrToModify -= 1;
    } else if (pressed & MENU_RIGHT) {
      *ptrToModify += 10;
    } else if (pressed & MENU_LEFT) {
      if (*ptrToModify < 10)
        *ptrToModify = 0;
      else
        *ptrToModify -= 10;
    }

  } while (true);
}

/*
 * Magic, as the game models it.
 *
 * Granting magic (0x1710C4) sets four fields, not one: magic_acquired gates
 * whether magic can be spent at all, magic_num_upgrades is 0 for one bar and 1
 * for two, magic is the current amount, and magic_size_type is cleared. The
 * meter length is separate, in CommonData::magic_max.
 *
 * Chateau Romani is not a fourth upgrade level -- it is a week event flag that
 * makes update_magic_cost_and_reduce_magic (0x2264CC) zero the cost, so magic
 * is spent for free and the meter stays full.
 *
 * Setting only `magic`, as this used to, left the meter the wrong size and did
 * nothing for a player who had never been given magic at all.
 */
enum MagicLevel {
  MAGIC_NONE = 0,
  MAGIC_REGULAR = 1,
  MAGIC_DOUBLE = 2,
  MAGIC_CHATEAU = 3,
};

static const char* const MagicLevelNames[] = {
    "0 - none, magic items unusable",
    "1 - regular",
    "2 - double",
    "3 - Chateau Romani, free",
};

// One bar is 48 units, two are 96. Both from the grant code at 0x1710C4.
#define MAGIC_ONE_BAR 48
#define MAGIC_TWO_BARS 96

static u8 Cheats_GetMagicLevel(void) {
  const game::CommonData& cdata = game::GetCommonData();
  if (!cdata.save.player.magic_acquired)
    return MAGIC_NONE;
  if (cdata.save.week_event_reg_14.WEEKEVENTREG_DRANK_CHATEAU_ROMANI)
    return MAGIC_CHATEAU;
  return cdata.save.player.magic_num_upgrades >= 1 ? MAGIC_DOUBLE : MAGIC_REGULAR;
}

static void Cheats_SetMagicLevel(u8 level) {
  game::CommonData& cdata = game::GetCommonData();
  const bool hasMagic = level != MAGIC_NONE;
  const bool doubled = level >= MAGIC_DOUBLE;
  const s16 amount = !hasMagic ? 0 : (doubled ? MAGIC_TWO_BARS : MAGIC_ONE_BAR);

  cdata.save.player.magic_acquired = hasMagic ? 1 : 0;
  cdata.save.player.magic_num_upgrades = doubled ? 1 : 0;
  cdata.save.player.magic_size_type = 0;
  cdata.save.player.magic = (u8)amount;
  cdata.magic_max = amount;
  // Cancel any refill the game had queued, or it tops the meter back up to the
  // old size.
  cdata.magic_accumulator = 0;

  cdata.save.week_event_reg_14.WEEKEVENTREG_DRANK_CHATEAU_ROMANI =
      level == MAGIC_CHATEAU ? 1 : 0;
}

static void Cheats_Modify_Link_Magic(LinkData whatToModify, s8*) {
  u8 level = Cheats_GetMagicLevel();

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();

    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Current %s:", LinkModifyNames[whatToModify]);
    Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%-32s", MagicLevelNames[level]);

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & (BUTTON_B | BUTTON_A)) {
      break;
    } else if (pressed & MENU_UP) {
      if (level < MAGIC_CHATEAU)
        Cheats_SetMagicLevel(++level);
    } else if (pressed & MENU_DOWN) {
      if (level > MAGIC_NONE)
        Cheats_SetMagicLevel(--level);
    }
  } while (true);
}

static void Cheats_ModifyHealth(void) {
  game::CommonData& cdata = game::GetCommonData();
  Cheats_Modify_Link(HEALTH, &cdata.save.player.health_max);
}

static void Cheats_ModifyMagic(void) {
  Cheats_Modify_Link_Magic(MAGIC, nullptr);
}

static void Cheats_ModifyRazor(void) {
  game::CommonData& cdata = game::GetCommonData();
  Cheats_Modify_Link(RAZOR_SWORD, &cdata.save.player.razor_sword_hp);
}

static void Cheats_ModifyRupees(void) {
  game::CommonData& cdata = game::GetCommonData();
  Cheats_Modify_Link(RUPEE, &cdata.save.player.rupee_count);
}

Menu CheatsMenu = {
    .title = "Cheats",
    .nbItems = 9,
    .items = {
        {.title = "Refill Health", .action_type = METHOD, .method = Cheats_Health},
        {.title = "Refill Magic", .action_type = METHOD, .method = Cheats_Magic},
        {.title = "Infinite Items", .action_type = METHOD, .method = Cheats_ItemsMenuFunc},
        {.title = "Refill Rupees", .action_type = METHOD, .method = Cheats_Rupees},
        {.title = "Change Time of Day", .action_type = MENU, .menu = &TimeChangeMenu},
        {.title = "Change Flow of Time", .action_type = MENU, .menu = &TimeSpeedMenu},
        {.title = "Change Day", .action_type = MENU, .menu = &DayChangeMenu},
        {.title = "ISG", .action_type = METHOD, .method = Cheats_ISG},
        {.title = "Edit Link's Info", .action_type = MENU, .menu = &LinkAmountInfo},
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

Menu LinkAmountInfo = {
    .title = "Player Data",
    .nbItems = 4,
    .items = {
        {.title = "Total Health", .action_type = METHOD, .method = Cheats_ModifyHealth},
        {.title = "Magic Upgrades", .action_type = METHOD, .method = Cheats_ModifyMagic},
        {.title = "Razor Sword Hits Remaining",
         .action_type = METHOD,
         .method = Cheats_ModifyRazor},
        {.title = "Modify Rupee Count", .action_type = METHOD, .method = Cheats_ModifyRupees}}};
}  // namespace msys
