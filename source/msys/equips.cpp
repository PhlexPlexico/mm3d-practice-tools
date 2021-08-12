#include "msys/include/menus/equips.h"
#include "game/common_data.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"

namespace msys {
static const char* const EquipButtonNames[] = {
    "B Button", "Y Button", "X Button", "I Button", "II Button",
};

static void Equips_ModifyButton(u32 button) {
  game::EquipmentData& equips = game::GetCommonData().save.equipment;
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();

    Draw_DrawFormattedString(10, 10, COLOR_TITLE,
                             "Select item for the %s:", EquipButtonNames[button]);
    Draw_DrawFormattedString(30, 30, COLOR_WHITE, "%03u", equips.data[0].item_btns[button]);

    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & (BUTTON_B | BUTTON_A)) {
      break;
    } else if (pressed & BUTTON_UP) {
      equips.data[0].item_btns[button] =
          (game::ItemId)((u64)equips.data[0].item_btns[button] + (u64)1);
    } else if (pressed & BUTTON_DOWN) {
      equips.data[0].item_btns[button] =
          (game::ItemId)((u64)equips.data[0].item_btns[button] - (u64)1);
    } else if (pressed & BUTTON_LEFT) {
      equips.data[0].item_btns[button] =
          (game::ItemId)((u64)equips.data[0].item_btns[button] + (u64)10);
    } else if (pressed & BUTTON_RIGHT) {
      equips.data[0].item_btns[button] =
          (game::ItemId)((u64)equips.data[0].item_btns[button] - (u64)10);
    }

  } while (true);
}

static void Equips_ModifyBButton(void) {
  Equips_ModifyButton(EQUIP_BUTTON_B);
}

static void Equips_ModifyYButton(void) {
  Equips_ModifyButton(EQUIP_BUTTON_Y);
}

static void Equips_ModifyXButton(void) {
  Equips_ModifyButton(EQUIP_BUTTON_X);
}

static void Equips_ModifyIButton(void) {
  Equips_ModifyButton(EQUIP_BUTTON_I);
}

static void Equips_ModifyIIButton(void) {
  Equips_ModifyButton(EQUIP_BUTTON_II);
}

Menu EquipsMenu = {
    .title = "Equips",
    .nbItems = 5,
    .items{
        {.title = "B button", .action_type = METHOD, .method = Equips_ModifyBButton},
        {.title = "Y button", .action_type = METHOD, .method = Equips_ModifyYButton},
        {.title = "X button", .action_type = METHOD, .method = Equips_ModifyXButton},
        {.title = "I button", .action_type = METHOD, .method = Equips_ModifyIButton},
        {.title = "II button", .action_type = METHOD, .method = Equips_ModifyIIButton},
    }};
}  // namespace msys
