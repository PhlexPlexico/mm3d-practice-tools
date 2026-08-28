/*
 * The Gear screen.
 *
 * Everything here is what the in-game gear screen shows: hearts, magic, the
 * razor sword's remaining hits, rupees, the two ammo upgrades, the notebook and
 * the two trade item slots. Lifted out of Cheats, where it sat behind "Edit
 * Link's Info", because none of it is really a cheat -- it is editing the same
 * values that screen displays.
 */

#include "msys/include/menus/gear.h"
#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/items.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"

namespace msys {

  // Defined below; the select handlers need them to mark the chosen row.
  extern ToggleMenu GearBombBagMenu;
  extern ToggleMenu GearQuiverMenu;
  extern ToggleMenu GearTradeOneMenu;
  extern ToggleMenu GearTradeTwoMenu;
  extern ToggleMenu GearNotebookMenu;
  extern ToggleMenu GearRoomKeyMenu;
  extern ToggleMenu GearDeliveryMenu;

  static const char* const GearAmountNames[] = {"max health (* by 16 for a total heart)", "magic", "razor sword hp",
                                                "current rupees", "current health (16 to a heart)"};

  static void Gear_ModifyAmount(GearData whatToModify, u16* ptrToModify) {
    const u16 step = (whatToModify == HEALTH) ? 16 : 1;
    const u16 coarse = (whatToModify == HEALTH_CURRENT) ? 16 : step * 10;
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();

      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Current %s:", GearAmountNames[whatToModify]);
      Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%-5u", *ptrToModify);
      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & (BUTTON_B | BUTTON_A)) {
        break;
      } else if (pressed & MENU_UP) {
        *ptrToModify += step;
      } else if (pressed & MENU_DOWN) {
        if (*ptrToModify < step)
          *ptrToModify = 0;
        else
          *ptrToModify -= step;
      } else if (pressed & MENU_RIGHT) {
        *ptrToModify += coarse;
      } else if (pressed & MENU_LEFT) {
        if (*ptrToModify < coarse)
          *ptrToModify = 0;
        else
          *ptrToModify -= coarse;
      }

      if (whatToModify == HEALTH) {
        game::CommonData& cdata = game::GetCommonData();
        if (cdata.save.player.health_current > cdata.save.player.health_max)
          cdata.save.player.health_current = cdata.save.player.health_max;
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

  static u8 Gear_GetMagicLevel(void) {
    const game::CommonData& cdata = game::GetCommonData();
    if (!cdata.save.player.magic_acquired)
      return MAGIC_NONE;
    if (cdata.save.week_event_reg_14.WEEKEVENTREG_DRANK_CHATEAU_ROMANI)
      return MAGIC_CHATEAU;
    return cdata.save.player.magic_num_upgrades >= 1 ? MAGIC_DOUBLE : MAGIC_REGULAR;
  }

  static void Gear_SetMagicLevel(u8 level) {
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

    cdata.save.week_event_reg_14.WEEKEVENTREG_DRANK_CHATEAU_ROMANI = level == MAGIC_CHATEAU ? 1 : 0;
  }

  static void Gear_ModifyMagic_(GearData whatToModify, s8*) {
    u8 level = Gear_GetMagicLevel();

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();

      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Current %s:", GearAmountNames[whatToModify]);
      Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%-32s", MagicLevelNames[level]);

      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & (BUTTON_B | BUTTON_A)) {
        break;
      } else if (pressed & MENU_UP) {
        if (level < MAGIC_CHATEAU)
          Gear_SetMagicLevel(++level);
      } else if (pressed & MENU_DOWN) {
        if (level > MAGIC_NONE)
          Gear_SetMagicLevel(--level);
      }
    } while (true);
  }

  static void Gear_Health(void) {
    game::CommonData& cdata = game::GetCommonData();
    Gear_ModifyAmount(HEALTH, &cdata.save.player.health_max);
  }

  static void Gear_Magic(void) {
    Gear_ModifyMagic_(MAGIC, nullptr);
  }

  static void Gear_Razor(void) {
    game::CommonData& cdata = game::GetCommonData();
    Gear_ModifyAmount(RAZOR_SWORD, &cdata.save.player.razor_sword_hp);
  }

  static void Gear_Rupees(void) {
    game::CommonData& cdata = game::GetCommonData();
    Gear_ModifyAmount(RUPEE, &cdata.save.player.rupee_count);
  }

  /*
   * Pick-one lists, shown the same way as the bottle and inventory menus: every
   * choice on screen with (x) against the current one, rather than a value you
   * step through and have to read back.
   */
  static void Gear_ClearToggles(ToggleMenu* menu) {
    for (u32 i = 0; i < menu->nbItems; ++i)
      menu->items[i].on = 0;
  }

  static void Gear_SelectOne(ToggleMenu* menu, s32 selected) {
    Gear_ClearToggles(menu);
    if (selected >= 0 && (u32)selected < menu->nbItems)
      menu->items[selected].on = 1;
  }

  /*
   * Ammo upgrades. Both are three-bit fields in inventory_count_register, and the
   * enums are already sized 0-3, so the menu index is the stored value.
   */
  static u32 GetBombBag(void) {
    return (u32)game::GetCommonData().save.inventory.inventory_count_register.bomb_bag_upgrade.Value();
  }
  static void SetBombBag(u32 v) {
    game::GetCommonData().save.inventory.inventory_count_register.bomb_bag_upgrade = (game::BombBag)v;
  }
  static u32 GetQuiver(void) {
    return (u32)game::GetCommonData().save.inventory.inventory_count_register.quiver_upgrade.Value();
  }
  static void SetQuiver(u32 v) {
    game::GetCommonData().save.inventory.inventory_count_register.quiver_upgrade = (game::Quiver)v;
  }

  static void Gear_BombBagSelect(s32 selected) {
    if (selected < 0 || selected > 3)
      return;
    SetBombBag((u32)selected);
    Gear_SelectOne(&GearBombBagMenu, selected);
  }

  static void Gear_QuiverSelect(s32 selected) {
    if (selected < 0 || selected > 3)
      return;
    SetQuiver((u32)selected);
    Gear_SelectOne(&GearQuiverMenu, selected);
  }

  static void Gear_BombBag(void) {
    Gear_SelectOne(&GearBombBagMenu, (s32)GetBombBag());
    ToggleMenuShow(&GearBombBagMenu);
  }

  static void Gear_Quiver(void) {
    Gear_SelectOne(&GearQuiverMenu, (s32)GetQuiver());
    ToggleMenuShow(&GearQuiverMenu);
  }

  /// Yes/no rather than a silent toggle, so the menu shows the state it left
  /// things in.
  static void Gear_NotebookSelect(s32 selected) {
    if (selected < 0 || selected > 1)
      return;
    game::InventoryData::CollectRegister& collect = game::GetCommonData().save.inventory.collect_register;
    collect.bombers_notebook = selected;
    Gear_SelectOne(&GearNotebookMenu, selected);
  }

  static void Gear_Notebook(void) {
    const u32 has = game::GetCommonData().save.inventory.collect_register.bombers_notebook;
    Gear_SelectOne(&GearNotebookMenu, (s32)has);
    ToggleMenuShow(&GearNotebookMenu);
  }

/*
 * Trade items.
 *
 * The game keeps one slot per trade chain and swaps the contents rather than
 * stacking, which is why picking a new one here replaces what was there. The
 * slot numbers come from the game's own item-to-slot table (read through
 * get_inventory_item_by_xxx_id at 0x1F3D5C): everything in the first chain maps
 * to slot 5, and both items of the second map to slot 17.
 */
#define TRADE_SLOT_ONE 5
#define TRADE_SLOT_TWO 17
#define TRADE_SLOT_ROOM_KEY 58
#define TRADE_SLOT_DELIVERY 59

  /*
   * The game's item-to-slot table is a byte offset from items[0], not an index
   * into items[] -- 0..23 are the item grid, 24..47 the masks, 48 onwards the
   * bottles, and the quest slots sit past those. Room Key and the Special
   * Delivery to Mama are at 58 and 59, well outside the 24-element array, so
   * they are reached the way the game reaches them rather than by indexing
   * items[] out of bounds.
   */
  static game::ItemId& QuestSlot(u32 slot) {
    return reinterpret_cast<game::ItemId*>(&game::GetCommonData().save.inventory.items[0])[slot];
  }

  static const game::ItemId TradeSlotOne[] = {
      game::ItemId::None,           game::ItemId::MoonTear,          game::ItemId::LandTitleDeed,
      game::ItemId::SwampTitleDeed, game::ItemId::MountainTitleDeed, game::ItemId::OceanTitleDeed,
  };

  static const game::ItemId TradeSlotTwo[] = {
      game::ItemId::None,
      game::ItemId::LetterToKafei,
      game::ItemId::PendantOfMemories,
  };

  static void Gear_TradeSelect(ToggleMenu* menu, u32 slot, const game::ItemId* ids, s32 selected) {
    if (selected < 0 || (u32)selected >= menu->nbItems)
      return;
    QuestSlot(slot) = ids[selected];
    Gear_SelectOne(menu, selected);
  }

  static void Gear_TradeOneSelect(s32 selected) {
    Gear_TradeSelect(&GearTradeOneMenu, TRADE_SLOT_ONE, TradeSlotOne, selected);
  }

  static void Gear_TradeTwoSelect(s32 selected) {
    Gear_TradeSelect(&GearTradeTwoMenu, TRADE_SLOT_TWO, TradeSlotTwo, selected);
  }

  /// Mark whichever entry matches what the slot currently holds.
  static void Gear_TradeShow(ToggleMenu* menu, u32 slot, const game::ItemId* ids) {
    const game::ItemId held = QuestSlot(slot);
    s32 selected = 0;
    for (u32 i = 0; i < menu->nbItems; ++i) {
      if (ids[i] == held) {
        selected = (s32)i;
        break;
      }
    }
    Gear_SelectOne(menu, selected);
    ToggleMenuShow(menu);
  }

  static const game::ItemId RoomKeySlot[] = {game::ItemId::None, game::ItemId::RoomKey};
  static const game::ItemId DeliverySlot[] = {game::ItemId::None, game::ItemId::LetterToMama};

  static void Gear_RoomKeySelect(s32 selected) {
    Gear_TradeSelect(&GearRoomKeyMenu, TRADE_SLOT_ROOM_KEY, RoomKeySlot, selected);
  }

  static void Gear_DeliverySelect(s32 selected) {
    Gear_TradeSelect(&GearDeliveryMenu, TRADE_SLOT_DELIVERY, DeliverySlot, selected);
  }

  static void Gear_RoomKey(void) {
    Gear_TradeShow(&GearRoomKeyMenu, TRADE_SLOT_ROOM_KEY, RoomKeySlot);
  }

  static void Gear_Delivery(void) {
    Gear_TradeShow(&GearDeliveryMenu, TRADE_SLOT_DELIVERY, DeliverySlot);
  }

  static void Gear_TradeOne(void) {
    Gear_TradeShow(&GearTradeOneMenu, TRADE_SLOT_ONE, TradeSlotOne);
  }

  static void Gear_TradeTwo(void) {
    Gear_TradeShow(&GearTradeTwoMenu, TRADE_SLOT_TWO, TradeSlotTwo);
  }

  static void Gear_HealthCurrent(void) {
    game::CommonData& cdata = game::GetCommonData();
    Gear_ModifyAmount(HEALTH_CURRENT, &cdata.save.player.health_current);
  }

  ToggleMenu GearBombBagMenu = {.title = "Bomb Bag",
                                .nbItems = 4,
                                .items = {{.on = 0, .title = "None", .method = Gear_BombBagSelect},
                                          {.on = 0, .title = "Bomb Bag (20)", .method = Gear_BombBagSelect},
                                          {.on = 0, .title = "Big Bomb Bag (30)", .method = Gear_BombBagSelect},
                                          {.on = 0, .title = "Biggest Bomb Bag (40)", .method = Gear_BombBagSelect}}};

  ToggleMenu GearQuiverMenu = {.title = "Quiver",
                               .nbItems = 4,
                               .items = {{.on = 0, .title = "None", .method = Gear_QuiverSelect},
                                         {.on = 0, .title = "Quiver (30)", .method = Gear_QuiverSelect},
                                         {.on = 0, .title = "Big Quiver (40)", .method = Gear_QuiverSelect},
                                         {.on = 0, .title = "Biggest Quiver (50)", .method = Gear_QuiverSelect}}};

  ToggleMenu GearNotebookMenu = {.title = "Bomber's Notebook",
                                 .nbItems = 2,
                                 .items = {{.on = 0, .title = "No", .method = Gear_NotebookSelect},
                                           {.on = 0, .title = "Yes", .method = Gear_NotebookSelect}}};

  ToggleMenu GearRoomKeyMenu = {.title = "Room Key",
                                .nbItems = 2,
                                .items = {{.on = 0, .title = "Empty", .method = Gear_RoomKeySelect},
                                          {.on = 0, .title = "Room Key", .method = Gear_RoomKeySelect}}};

  ToggleMenu GearDeliveryMenu = {
      .title = "Special Delivery to Mama",
      .nbItems = 2,
      .items = {{.on = 0, .title = "Empty", .method = Gear_DeliverySelect},
                {.on = 0, .title = "Special Delivery to Mama", .method = Gear_DeliverySelect}}};

  ToggleMenu GearTradeOneMenu = {.title = "Trade Item 1",
                                 .nbItems = 6,
                                 .items = {{.on = 0, .title = "Empty", .method = Gear_TradeOneSelect},
                                           {.on = 0, .title = "Moon's Tear", .method = Gear_TradeOneSelect},
                                           {.on = 0, .title = "Land Title Deed", .method = Gear_TradeOneSelect},
                                           {.on = 0, .title = "Swamp Title Deed", .method = Gear_TradeOneSelect},
                                           {.on = 0, .title = "Mountain Title Deed", .method = Gear_TradeOneSelect},
                                           {.on = 0, .title = "Ocean Title Deed", .method = Gear_TradeOneSelect}}};

  ToggleMenu GearTradeTwoMenu = {.title = "Trade Item 2",
                                 .nbItems = 3,
                                 .items = {{.on = 0, .title = "Empty", .method = Gear_TradeTwoSelect},
                                           {.on = 0, .title = "Kafei's Letter", .method = Gear_TradeTwoSelect},
                                           {.on = 0, .title = "Pendant of Memories", .method = Gear_TradeTwoSelect}}};

  Menu GearMenu = {.title = "Gear",
                   .nbItems = 12,
                   .items = {
                       {.title = "Total Health", .action_type = METHOD, .method = Gear_Health},
                       {.title = "Current Health", .action_type = METHOD, .method = Gear_HealthCurrent},
                       {.title = "Magic", .action_type = METHOD, .method = Gear_Magic},
                       {.title = "Razor Sword Hits Remaining", .action_type = METHOD, .method = Gear_Razor},
                       {.title = "Rupee Count", .action_type = METHOD, .method = Gear_Rupees},
                       {.title = "Bomb Bag", .action_type = METHOD, .method = Gear_BombBag},
                       {.title = "Quiver", .action_type = METHOD, .method = Gear_Quiver},
                       {.title = "Bomber's Notebook", .action_type = METHOD, .method = Gear_Notebook},
                       {.title = "Trade Item 1", .action_type = METHOD, .method = Gear_TradeOne},
                       {.title = "Trade Item 2", .action_type = METHOD, .method = Gear_TradeTwo},
                       {.title = "Room Key", .action_type = METHOD, .method = Gear_RoomKey},
                       {.title = "Special Delivery to Mama", .action_type = METHOD, .method = Gear_Delivery},
                   }};

}  // namespace msys
