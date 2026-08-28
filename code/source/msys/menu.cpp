/*
 *   This file is a modified part of Luma3DS
 *   Copyright (C) 2016-2019 Aurora Wright, TuxSH
 *   Modified 2020 Gamestabled
 *   Modified 2021 PhlexPlexico
 *
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
// clang-format off
extern "C" {
#include <3ds/types.h>
#include <3ds/srv.h>
}
// clang-format on
#include "msys/include/draw.h"
#include "msys/include/menu.h"
#include "msys/include/menus.h"
#include "msys/include/utils.h"

#include <stdio.h>
#include <string.h>

namespace msys {
  static u32 waitInputInternal(u32 msec, bool allowRepeat) {
    bool pressedKey = false;
    u32 key = 0;
    u32 n = 0;

    const bool isDirectionHeld = allowRepeat && (HID_PAD & (MENU_UP | MENU_DOWN | MENU_LEFT | MENU_RIGHT)) != 0;

    // A held direction repeats rather than requiring a release, so the cursor
    // scrolls at a steady pace. The circle pad counts too, or it would have to be
    // returned to centre between every step.
    if (isDirectionHeld) {
      // By default wait 75 milliseconds before moving the cursor so that
      // we don't scroll the menu too fast.
      svcSleepThread(75 * 1000 * 1000LL);
    } else {
      // Wait for no keys to be pressed in the event that up and down are not pressed.
      while (HID_PAD && (msec == 0 || n <= msec)) {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
      }
    }

    if (msec != 0 && n >= msec)
      return 0;

    do {
      // Wait for a key to be pressed
      while (!HID_PAD && (msec == 0 || n < msec)) {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
      }

      if (msec != 0 && n >= msec)
        return 0;

      key = HID_PAD;

      // Make sure it's pressed
      for (u32 i = 0x26000; i > 0; i--) {
        if (key != HID_PAD)
          break;
        if (i == 1)
          pressedKey = true;
      }
    } while (!pressedKey);

    return key;
  }

  u32 waitInputWithTimeout(u32 msec) {
    return waitInputInternal(msec, true);
  }

  /*
   * Same, but a held input is never reported twice.
   *
   * Menus want the repeat so the cursor scrolls while a direction is held. Code
   * that records what was pressed does not: it would log a fresh entry every
   * 75 ms for as long as the input is held.
   */
  u32 waitInputNoRepeat(u32 msec) {
    return waitInputInternal(msec, false);
  }

  u32 waitInput(void) {
    return waitInputWithTimeout(0);
  }

  static MyThread menuThread;
  static u8 ALIGN(8) menuThreadStack[0x3000];

  MyThread* menuCreateThread(void) {
    if (R_FAILED(MyThread_Create(&menuThread, menuThreadMain, menuThreadStack, 0x3000, 52, CORE_DEFAULT)))
      svcBreak(USERBREAK_PANIC);
    return &menuThread;
  }

  void menuThreadMain(void) {
    menuEnter();
    menuShow(&pz3DMenu);
    svcSleepThread(1000 * 1000 * 300LL);  // wait 300 milliseconds for users to buffer inputs
  }

  void menuEnter(void) {
    Draw_ClearFramebuffer();
  }

  static void menuDraw(Menu* menu, u32 selected) {
    Draw_DrawString(10, 10, COLOR_TITLE, menu->title);

    for (u32 i = 0; i < 15; i++) {
      if (i >= menu->nbItems)
        break;
      Draw_DrawString(30, 30 + i * SPACING_Y, COLOR_WHITE, menu->items[i].title);
      Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, i == selected ? '>' : ' ');
    }

    Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - 4 * SPACING_X, SCREEN_BOT_HEIGHT - 20, COLOR_WHITE, "    ");
    Draw_FlushFramebuffer();
  }

  void menuShow(Menu* root) {
    u32 selectedItem = 0;
    Menu* currentMenu = root;
    u32 nbPreviousMenus = 0;
    Menu* previousMenus[0x80];
    u32 previousSelectedItems[0x80];

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    menuDraw(currentMenu, selectedItem);
    Draw_Unlock();

    do {
      u32 pressed = waitInputWithTimeout(1000);

      if (pressed & BUTTON_A) {
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();

        switch (currentMenu->items[selectedItem].action_type) {
        case METHOD:
          if (currentMenu->items[selectedItem].method != NULL)
            currentMenu->items[selectedItem].method();
          break;
        case MENU:
          previousSelectedItems[nbPreviousMenus] = selectedItem;
          previousMenus[nbPreviousMenus++] = currentMenu;
          currentMenu = currentMenu->items[selectedItem].menu;
          selectedItem = 0;
          break;
        }

        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();
      } else if (pressed & BUTTON_B) {
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();

        if (nbPreviousMenus > 0) {
          currentMenu = previousMenus[--nbPreviousMenus];
          selectedItem = previousSelectedItems[nbPreviousMenus];
        } else {
          break;
        }
      } else if (pressed & MENU_DOWN) {
        if (++selectedItem >= currentMenu->nbItems)
          selectedItem = 0;
      } else if (pressed & MENU_UP) {
        if (selectedItem-- <= 0)
          selectedItem = currentMenu->nbItems - 1;
      }

      Draw_Lock();
      menuDraw(currentMenu, selectedItem);
      Draw_Unlock();
    } while (true);
  }

  void ToggleMenuShow(ToggleMenu* menu)  // displays a toggle menu, analogous to rosalina cheats page
  {
    s32 selected = 0, page = 0, pagePrev = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      if (page != pagePrev) {
        Draw_ClearFramebuffer();
      }
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

      for (s32 i = 0; i < TOGGLE_MENU_MAX_SHOW && (u32)page * TOGGLE_MENU_MAX_SHOW + i < menu->nbItems; ++i) {
        s32 j = page * TOGGLE_MENU_MAX_SHOW + i;
        const char* checkbox = (menu->items[j].on ? "(x) " : "( ) ");
        Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "%s%s", checkbox, menu->items[j].title);
        Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_TITLE, j == selected ? '>' : ' ');
      }

      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B)
        break;
      if (pressed & BUTTON_A) {
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();

        if (menu->items[selected].method != NULL) {
          menu->items[selected].method(selected);  // the method will handle swapping on/off
        }

        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();
      } else if (pressed & MENU_DOWN) {
        selected++;
      } else if (pressed & MENU_UP) {
        selected--;
      } else if (pressed & MENU_LEFT) {
        selected -= TOGGLE_MENU_MAX_SHOW;
      } else if (pressed & MENU_RIGHT) {
        if ((u32)selected + TOGGLE_MENU_MAX_SHOW < menu->nbItems)
          selected += TOGGLE_MENU_MAX_SHOW;
        else if ((menu->nbItems - 1) / TOGGLE_MENU_MAX_SHOW == (u32)page)
          selected %= TOGGLE_MENU_MAX_SHOW;
        else
          selected = menu->nbItems - 1;
      }

      if (selected < 0)
        selected = menu->nbItems - 1;
      else if ((u32)selected >= menu->nbItems)
        selected = 0;

      pagePrev = page;
      page = selected / TOGGLE_MENU_MAX_SHOW;
    } while (true);
  }

  void AmountMenuShow(AmountMenu* menu) {  // displays an amount menu TODO: seems messed up
    s32 selected = 0, page = 0, pagePrev = 0;
    u32 curColor = COLOR_GREEN;
    u32 chosen = 0;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      if (page != pagePrev) {
        Draw_ClearFramebuffer();
      }
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, menu->title);

      for (s32 i = 0; i < AMOUNT_MENU_MAX_SHOW && (u32)page * AMOUNT_MENU_MAX_SHOW + i < menu->nbItems; ++i) {
        s32 j = page * AMOUNT_MENU_MAX_SHOW + i;
        Draw_DrawString(70, 30 + i * SPACING_Y, COLOR_WHITE, menu->items[j].title);
        Draw_DrawFormattedString(10, 30 + i * SPACING_Y, j == selected ? curColor : COLOR_TITLE,
                                 menu->items[j].hex ? "0x%04X" : "  %05d", menu->items[j].amount);
      }

      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B && !chosen)
        break;
      else if (pressed & BUTTON_A && !chosen) {
        curColor = COLOR_RED;
        chosen = 1;
      } else if (pressed & (BUTTON_A | BUTTON_B) & chosen) {
        if (menu->items[selected].method != NULL) {
          menu->items[selected].method(selected);  // the method will handle changing amount
        }
        curColor = COLOR_GREEN;
        chosen = 0;
      } else if (pressed & MENU_DOWN && !chosen) {
        selected++;
      } else if (pressed & MENU_DOWN && chosen) {
        menu->items[selected].amount--;
      } else if (pressed & MENU_UP && !chosen) {
        selected--;
      } else if (pressed & MENU_UP && chosen) {
        menu->items[selected].amount++;
      } else if (pressed & MENU_LEFT && !chosen) {
        selected -= AMOUNT_MENU_MAX_SHOW;
      } else if (pressed & MENU_LEFT && chosen) {
        menu->items[selected].amount += (menu->items[selected].hex ? 16 : 10);
      } else if (pressed & MENU_RIGHT && !chosen) {
        if ((u32)selected + AMOUNT_MENU_MAX_SHOW < menu->nbItems)
          selected += AMOUNT_MENU_MAX_SHOW;
        else if ((menu->nbItems - 1) / AMOUNT_MENU_MAX_SHOW == (u32)page)
          selected %= AMOUNT_MENU_MAX_SHOW;
        else
          selected = menu->nbItems - 1;
      } else if (pressed & MENU_RIGHT && chosen) {
        menu->items[selected].amount -= (menu->items[selected].hex ? 16 : 10);
      }
      if (selected < 0)
        selected = menu->nbItems - 1;
      else if ((u32)selected >= menu->nbItems)
        selected = 0;

      pagePrev = page;
      page = selected / AMOUNT_MENU_MAX_SHOW;
    } while (true);
  }

/*
 * Hex entry for an address.
 *
 * Not swkbd. That is a library applet, not a widget: swkbdInputText goes
 * through aptLaunchLibraryApplet, which suspends the running application and
 * hands the screens to a separate process, and the application's own APT loop
 * has to service the transition. This menu works by not returning from the
 * game's per-frame call, so the very thread that would have to cooperate is the
 * one being held. libctru's service layer is not initialised here either --
 * __service_ptr is null and nothing calls srvInit or aptInit; even SD access
 * borrows the game's own FS session rather than opening one.
 *
 * So it is a keypad, which is also what Rosalina does from the same kind of
 * injected context. Typing eight digits beats nudging four bytes by 0x10 and
 * 0x01, which is what this replaces.
 */
#define HEX_COLS 4
#define HEX_ROWS 5
#define HEX_DIGITS 8

  static const char* const HexKeys[HEX_ROWS][HEX_COLS] = {
      {"0", "1", "2", "3"}, {"4", "5", "6", "7"}, {"8", "9", "A", "B"}, {"C", "D", "E", "F"}, {"Del", "Clr", "OK", ""},
  };

  u32 HexEntry(const char* title, u32 initial) {
    char buf[HEX_DIGITS + 1];
    u32 len = 0;
    s32 row = 0, col = 0;

    // Start from the current value so a small correction does not mean retyping.
    for (u32 i = 0; i < HEX_DIGITS; ++i) {
      const u32 nibble = (initial >> ((HEX_DIGITS - 1 - i) * 4)) & 0xF;
      buf[i] = nibble < 10 ? (char)('0' + nibble) : (char)('A' + nibble - 10);
    }
    buf[HEX_DIGITS] = '\0';
    len = HEX_DIGITS;

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      Draw_DrawString(10, 10, COLOR_TITLE, title);
      Draw_DrawFormattedString(30, 30, COLOR_GREEN, "0x%-8s", buf);

      for (s32 r = 0; r < HEX_ROWS; ++r) {
        for (s32 c = 0; c < HEX_COLS; ++c) {
          if (!HexKeys[r][c][0])
            continue;
          const bool here = (r == row && c == col);
          Draw_DrawFormattedString(30 + c * 5 * SPACING_X, 50 + r * SPACING_Y, here ? COLOR_GREEN : COLOR_WHITE, "%-4s",
                                   HexKeys[r][c]);
        }
      }

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "A to pick. B to cancel.");
      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B)
        return initial;

      if (pressed & BUTTON_A) {
        const char* key = HexKeys[row][col];
        if (!strcmp(key, "OK"))
          break;
        if (!strcmp(key, "Clr")) {
          len = 0;
          buf[0] = '\0';
        } else if (!strcmp(key, "Del")) {
          if (len)
            buf[--len] = '\0';
        } else if (len < HEX_DIGITS) {
          buf[len++] = key[0];
          buf[len] = '\0';
        }
      } else if (pressed & MENU_UP) {
        row = (row + HEX_ROWS - 1) % HEX_ROWS;
      } else if (pressed & MENU_DOWN) {
        row = (row + 1) % HEX_ROWS;
      } else if (pressed & MENU_LEFT) {
        col = (col + HEX_COLS - 1) % HEX_COLS;
      } else if (pressed & MENU_RIGHT) {
        col = (col + 1) % HEX_COLS;
      }
      // The last row is three keys wide, not four.
      if (row == HEX_ROWS - 1 && col >= 3)
        col = 2;
    } while (true);

    u32 value = 0;
    for (u32 i = 0; i < len; ++i) {
      const char ch = buf[i];
      const u32 nibble = ch <= '9' ? (u32)(ch - '0') : (u32)(ch - 'A' + 10);
      value = (value << 4) | nibble;
    }
    return value;
  }

  u32 KeyboardFill(char* buf, u32 len) {
    const char* Upper = "1234567890QWERTYUIOPASDFGHJKL'ZXCVBNM,.+";
    const char* Lower = "1234567890qwertyuiopasdfghjkl'zxcvbnm,.+";

    const char* keys = Lower;
    s32 selected = 0;
    u32 idx = strlen(buf);

    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();

    do {
      Draw_Lock();
      Draw_DrawString(10, 10, COLOR_TITLE, "Edit Watch Name");

      for (u32 i = 0; i < 10; ++i) {
        Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30, (u32)selected == i ? COLOR_GREEN : COLOR_WHITE, "%c ",
                                 keys[i]);
      }
      for (u32 i = 0; i < 10; ++i) {
        u32 j = 10 + i;
        Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 2 * SPACING_Y,
                                 (u32)selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
      }
      for (u32 i = 0; i < 10; ++i) {
        u32 j = 20 + i;
        Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 4 * SPACING_Y,
                                 (u32)selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
      }
      for (u32 i = 0; i < 10; ++i) {
        u32 j = 30 + i;
        Draw_DrawFormattedString(30 + (i * 2 * SPACING_X), 30 + 6 * SPACING_Y,
                                 (u32)selected == j ? COLOR_GREEN : COLOR_WHITE, "%c ", keys[j]);
      }
      Draw_DrawString(30, 30 + 7 * SPACING_Y, COLOR_RED, buf);

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "L/R to switch case. Start to save and return.");

      Draw_FlushFramebuffer();
      Draw_Unlock();

      u32 pressed = waitInputWithTimeout(1000);
      if (pressed & BUTTON_B) {
        idx--;
        if ((s32)idx < 0)
          idx = 0;
        buf[idx] = '\0';
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_FlushFramebuffer();
        Draw_Unlock();
      } else if (pressed & BUTTON_A) {
        if (idx >= len)
          idx = len - 1;
        buf[idx] = keys[selected];
        idx++;
        buf[idx] = '\0';
      } else if (pressed & (BUTTON_R1 | BUTTON_L1)) {
        keys = (keys == Lower) ? Upper : Lower;
      } else if (pressed & MENU_DOWN) {
        selected += 10;
      } else if (pressed & MENU_UP) {
        selected -= 10;
      } else if (pressed & MENU_RIGHT) {
        selected++;
      } else if (pressed & MENU_LEFT) {
        selected--;
      } else if (pressed & BUTTON_START) {
        break;
      }

      if (selected >= 40)
        selected = 0;
      if (selected < 0)
        selected = 39;
    } while (true);

    return idx;
  }
}  // namespace msys
