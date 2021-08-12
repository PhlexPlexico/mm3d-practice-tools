#include "msys/include/menus/save.h"
#include "msys/include/file_functions.h"
#include "msys/include/menus/commands.h"

// XXX: Move Drawing to individual function instead of copy/paste.
namespace msys {
static void Save_ProfileToJson(void) {
  bool saved = false;
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    if (!saved) {
      Draw_Lock();
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Save Current Shortcut Keys? ");

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      "Press A to save, B to go back, and Y to delete your watches.");

      Draw_FlushFramebuffer();
      Draw_Unlock();
    }

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B) {
      saved = false;
      break;
    }

    if (pressed & BUTTON_A) {
      saved = (bool)File_SaveProfile(commandList);
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      "Save Complete! Press B to go back.");
      Draw_FlushFramebuffer();
      Draw_Unlock();
    } else if (pressed & BUTTON_Y) {
      saved =
          (bool)File_DeleteFileFromSd("/3ds/mm3d/mm3d-practice-patch/profile.json");
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      "Delete Complete! Press B to go back.");
      Draw_FlushFramebuffer();
      Draw_Unlock();
    }

  } while (true);
}

static void Save_WatchesToJson(void) {
  bool saved = false;
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    if (!saved) {
      Draw_Lock();
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Save Current Watches?");

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      "Press A to save, B to go back, and Y to delete your profile.");

      Draw_FlushFramebuffer();
      Draw_Unlock();
    }

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B) {
      saved = false;
      break;
    }

    if (pressed & BUTTON_A) {
      saved = (bool)File_SaveWatches(watches);
      Draw_Lock();
      Draw_ClearFramebuffer();
      if (!saved) {
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_RED,
                        "Save not completed. Please ensure you have watches TO save!");
      } else {
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                        "Save Complete! Press B to go back.");
      }
      Draw_FlushFramebuffer();
      Draw_Unlock();
    } else if (pressed & BUTTON_Y) {
      saved =
          (bool)File_DeleteFileFromSd("/3ds/mm3d/mm3d-practice-patch/watches.json");
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      "Delete Complete! Press B to go back.");
      Draw_FlushFramebuffer();
      Draw_Unlock();
    }

  } while (true);
}

Menu SaveMenu = {.title = "Save",
                 .nbItems = 2,
                 .items = {
                     {.title = "Save Profile", .action_type = METHOD, .method = Save_ProfileToJson},
                     {.title = "Save Watches", .action_type = METHOD, .method = Save_WatchesToJson},
                 }};

}  // namespace msys
