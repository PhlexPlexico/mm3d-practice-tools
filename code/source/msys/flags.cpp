/*
 * Week event flags.
 *
 * The game keeps 140 single-byte registers of event state, contiguous in the
 * save from week_event_reg_00. Two levels: pick a register, then toggle its
 * eight bits.
 *
 * Laid out as a list rather than the grid OoT3D's menu uses, because a register
 * is only eight bits wide -- they all fit on screen with room for a name beside
 * each, which a grid of numbered columns cannot show.
 *
 * Only 172 of the 1117 bits have a meaningful name in weekeventreg.h; the rest
 * are placeholders that repeat the register and bit number. Those are rendered
 * as "bit N" instead, and only the real names are carried in the table --
 * see tools/genflags.py.
 */

#include "msys/include/menus/flags.h"
#include "game/common_data.h"
#include "game/weekeventreg_names.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"

#include <stdio.h>
#include <string.h>

namespace msys {

#define FLAG_REG_MENU_MAX_SHOW 15
#define FLAG_NAME_MAX 40

  extern ToggleMenu FlagBitsMenu;

  /*
   * Indexing them as a flat byte array only holds because they are laid out
   * contiguously. The game's offsets say they are; assert it, so a header edit
   * cannot quietly move every flag by one.
   */
  static_assert(offsetof(game::SaveData, week_event_reg_35) - offsetof(game::SaveData, week_event_reg_00) == 35);
  static_assert(offsetof(game::SaveData, week_event_reg_131) - offsetof(game::SaveData, week_event_reg_00) == 131);

  /// The registers are consecutive bytes, so one pointer indexes all of them.
  static u8* WeekEventRegs(void) {
    return reinterpret_cast<u8*>(&game::GetCommonData().save.week_event_reg_00);
  }

  /// Binary search the generated table; null when the bit has no real name.
  static const char* FlagName(u32 reg, u32 bit) {
    const u16 want = (u16)(reg * 8 + bit);
    u32 lo = 0, hi = sizeof(game::kWeekEventFlagNames) / sizeof(game::kWeekEventFlagNames[0]);
    while (lo < hi) {
      const u32 mid = (lo + hi) / 2;
      if (game::kWeekEventFlagNames[mid].index == want)
        return game::kWeekEventFlagNames[mid].name;
      if (game::kWeekEventFlagNames[mid].index < want)
        lo = mid + 1;
      else
        hi = mid;
    }
    return nullptr;
  }

  // The bit menu's titles change with the register, so they point at these
  // rather than at string literals.
  static char BitTitles[8][FLAG_NAME_MAX + 1];

  /// Which register the bit menu is editing. Tracked here rather than read
  /// back off the screen.
  static u32 FlagSelectedReg = 0;
  static char FlagMenuTitle[24];

  static void Flags_BitToggle(s32 selected) {
    if (selected < 0 || selected > 7)
      return;
    u8& reg = WeekEventRegs()[FlagSelectedReg];
    reg ^= (u8)(1u << selected);
    FlagBitsMenu.items[selected].on = (reg >> selected) & 1;
  }

  static void Flags_ShowRegister(u32 reg) {
    FlagSelectedReg = reg;
    const u8 value = WeekEventRegs()[reg];
    snprintf(FlagMenuTitle, sizeof(FlagMenuTitle), "week_event_reg_%02u", (u8)reg);
    FlagBitsMenu.title = FlagMenuTitle;

    for (u32 bit = 0; bit < 8; ++bit) {
      const char* name = FlagName(reg, bit);
      if (name)
        snprintf(BitTitles[bit], sizeof(BitTitles[bit]), "%u %s", (u8)bit, name);
      else
        snprintf(BitTitles[bit], sizeof(BitTitles[bit]), "%u  bit %u", (u8)bit, (u8)bit);
      FlagBitsMenu.items[bit].title = BitTitles[bit];
      FlagBitsMenu.items[bit].on = (value >> bit) & 1;
    }
    ToggleMenuShow(&FlagBitsMenu);
  }

  void Flags_WeekEventMenuShow(void) {
    s32 selected = 0, page = 0, pagePrev = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      if (page != pagePrev)
        Draw_ClearFramebuffer();

      Draw_DrawString(10, 10, COLOR_TITLE, "Week Event Flags");
      const u8* regs = WeekEventRegs();
      for (u32 i = 0; i < FLAG_REG_MENU_MAX_SHOW; ++i) {
        const u32 j = page * FLAG_REG_MENU_MAX_SHOW + i;
        if (j >= game::kWeekEventRegCount)
          break;
        // The byte itself, so a register with anything set stands out without
        // having to open it.
        char bits[9];
        for (u32 b = 0; b < 8; ++b)
          bits[b] = ((regs[j] >> b) & 1) ? '1' : '0';
        bits[8] = '\0';
        Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "reg %03u  %s  %02X", j, bits, regs[j]);
        Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, selected == (s32)j ? '>' : ' ');
      }

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "A to open. Left/Right to page.");
      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B) {
        break;
      } else if (pressed & BUTTON_A) {
        Flags_ShowRegister((u32)selected);
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();
      } else if (pressed & MENU_DOWN) {
        selected++;
      } else if (pressed & MENU_UP) {
        selected--;
      } else if (pressed & MENU_RIGHT) {
        selected += FLAG_REG_MENU_MAX_SHOW;
      } else if (pressed & MENU_LEFT) {
        selected -= FLAG_REG_MENU_MAX_SHOW;
      }

      if (selected < 0)
        selected = (s32)game::kWeekEventRegCount - 1;
      else if (selected >= (s32)game::kWeekEventRegCount)
        selected = 0;

      pagePrev = page;
      page = selected / FLAG_REG_MENU_MAX_SHOW;
    } while (true);
  }

  ToggleMenu FlagBitsMenu = {.title = "",
                             .nbItems = 8,
                             .items = {{.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle},
                                       {.on = 0, .title = "", .method = Flags_BitToggle}}};

}  // namespace msys
