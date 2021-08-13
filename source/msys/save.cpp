extern "C" {
  #include <3ds/types.h>
}
#include "msys/include/menus/save.h"
#include "msys/include/file_functions.h"
#include "msys/include/menus/commands.h"

// XXX: Move Drawing to individual function instead of copy/paste.
namespace msys {

static void Save_DrawInformation(char* topMsg, char* btmMsg, char* successMsg, char* delMsg, char* failMsg, Result* saved, char filePath[]) {
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();
  do {
    if (*saved <= 0) {
      Draw_Lock();
      Draw_DrawFormattedString(10, 10, COLOR_TITLE, topMsg);

      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE,
                      btmMsg);

      Draw_FlushFramebuffer();
      Draw_Unlock();
    }

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B) {
      *saved = -1;
      break;
    }

    if (pressed & BUTTON_A) {
      *saved = File_SaveProfile(commandList);
      Draw_Lock();
      Draw_ClearFramebuffer();
      if (R_FAILED(*saved)) {
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_RED,
                        failMsg);
      } else {
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE,
                        successMsg);
      }
      Draw_FlushFramebuffer();
      Draw_Unlock();
    } else if (pressed & BUTTON_Y) {
      *saved =
          File_DeleteFileFromSd(filePath);
      Draw_Lock();
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE,
                      delMsg);
      Draw_FlushFramebuffer();
      Draw_Unlock();
    } 
  } while (true);
}

static void Save_ProfileToJson(void) {
  Result saved = 0;
  char path[43] = "/3ds/mm3d/mm3d-practice-patch/profile.json";
  char saveMsg[] = "Save Current Shortcut Keys?";
  char confirmMsg[] = "Press A to save, B to go back, and Y to delete yourprofile.";
  char successMsg[] = "Save Complete! Press B to go back.";
  char delMsg[] = "Delete Complete! Press B to go back.";
  char failMsg[] = "Save not completed. Error writing to SD.\nPlease restart your game and try again.";

  Save_DrawInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path);
}

static void Save_WatchesToJson(void) {
  Result saved = 0;
  char path[43] = "/3ds/mm3d/mm3d-practice-patch/watches.json";
  char saveMsg[] = "Save Current Watches?";
  char confirmMsg[] = "Press A to save, B to go back, and Y to delete your watches.";
  char successMsg[] = "Save Complete! Press B to go back.";
  char delMsg[] = "Delete Complete! Press B to go back.";
  char failMsg[] = "Save not completed. Please ensure you have watches\nTO save!\nPlease restart your game and try again.";

  Save_DrawInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path);

}

Menu SaveMenu = {.title = "Save",
                 .nbItems = 2,
                 .items = {
                     {.title = "Save Profile", .action_type = METHOD, .method = Save_ProfileToJson},
                     {.title = "Save Watches", .action_type = METHOD, .method = Save_WatchesToJson},
                 }};

}  // namespace msys
