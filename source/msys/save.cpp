
#include "msys/include/menus/save.h"

namespace msys {

static void Save_DrawJsonInformation(char* topMsg, char* btmMsg, char* successMsg, char* delMsg, char* failMsg, Result* saved, char filePath[]) {
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
      Draw_Lock();
      Draw_ClearFramebuffer();
      *saved = File_SaveProfile(commandList);
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE,
                        "Saving...");
      if (R_FAILED(*saved)) {
        Draw_ClearFramebuffer();
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_RED,
                        failMsg);
      } else {
        Draw_ClearFramebuffer();
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_GREEN,
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

  Save_DrawJsonInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path);
}

static void Save_WatchesToJson(void) {
  Result saved = 0;
  char path[43] = "/3ds/mm3d/mm3d-practice-patch/watches.json";
  char saveMsg[] = "Save Current Watches?";
  char confirmMsg[] = "Press A to save, B to go back, and Y to delete your watches.";
  char successMsg[] = "Save Complete! Press B to go back.";
  char delMsg[] = "Delete Complete! Press B to go back.";
  char failMsg[] = "Save not completed. Please ensure you have watches\nTO save!\nPlease restart your game and try again.";

  Save_DrawJsonInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path);
}

static void Save_WriteToBin(s32 selected) {
  game::CommonData& cdata = game::GetCommonData();
  game::act::Player* link = rst::GetContext().gctx->GetPlayerActor();
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_TITLE,
                      "Saving...");
  if(R_SUCCEEDED(File_SaveContextToSD(&cdata, link, selected))) {
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_GREEN,
                      "Saved!");
  }
  Draw_FlushFramebuffer();
  Draw_Unlock();
}

static void Save_ReadFromBin(s32 selected) {
  game::CommonData& cdata = game::GetCommonData();
  MemFileT* newmemfile = new MemFileT();
  std::string savePath = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
  savePath.replace(38,1,std::to_string(selected));
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_TITLE,
                      "Loading...");

  if(R_SUCCEEDED(File_ReadMemFileFromSd(newmemfile, savePath.c_str()))) {
    memcpy(&cdata.save, &newmemfile->save, sizeof(game::SaveData));
    memcpy(&cdata.save_backup, &newmemfile->save, sizeof(game::SaveData));
    memcpy(&cdata.sub1, &newmemfile->csub1, sizeof(game::CommonDataSub1));
    memcpy(&cdata.sub13s, &newmemfile->respawn, sizeof(game::RespawnData));

    cdata.time_copy = newmemfile->save.time;
    game::GlobalContext* gctx = rst::GetContext().gctx;
    gctx->next_entrance = cdata.sub1.entrance;
    gctx->gap_C533[1] = 0;
    cdata.field_13624 = 0xFFFFFFFB;
    //EntranceWarp(cdata.sub1.entrance);
    
    //EntranceWarp(newmemfile->linkcoords.rot.z);
    cdata.sub13s[0].pos = newmemfile->linkcoords.pos;
    
    game::act::Player* link = gctx->GetPlayerActor();
    
    link->pos = newmemfile->linkcoords;
    link->initial_pos = newmemfile->linkcoords;
    link->ztarget_pos = newmemfile->linkcoords;
    link->angle = newmemfile->angle;
    gctx->field_C529_one_to_clear_input = 0x14;
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_GREEN,
                      "Loaded!");
  } else {
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_RED,
                      "Version not supported!");
  }
  delete newmemfile;
  Draw_FlushFramebuffer();
  Draw_Unlock();
}

static void Save_MemfileToBin(void) {
  s32 selected = 0;

  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_FlushFramebuffer();
  Draw_Unlock();

  do {
    Draw_Lock();
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Memfiles");
    for (s32 i = 0; i < MAX_SAVED_PROFILES; ++i) {
      Draw_DrawFormattedString(30, 30 + i * SPACING_Y, COLOR_WHITE, "Memfile #%i", i);
      Draw_DrawCharacter(10, 30 + i * SPACING_Y, COLOR_GREEN, i == selected ? '>' : ' ');
    }
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_WHITE, "A to save, Y to load, X to delete");
    Draw_FlushFramebuffer();
    Draw_Unlock();

    u32 pressed = waitInputWithTimeout(1000);
    if (pressed & BUTTON_B)
      break;
    if (pressed & BUTTON_A) {
      Save_WriteToBin(selected);
    } else if (pressed & BUTTON_Y) {
      Save_ReadFromBin(selected);
    } else if (pressed & BUTTON_X) {
      rst::util::Print("%s: Not yet implemented...", __func__);
    }else if (pressed & BUTTON_DOWN) {
      selected++;
    } else if (pressed & BUTTON_UP) {
      selected--;
    }

    if (selected < 0)
      selected = MAX_SAVED_PROFILES - 1;
    else if (selected >= MAX_SAVED_PROFILES)
      selected = 0;
  } while (true);
}

Menu SaveMenu = {.title = "SD Card",
                 .nbItems = 3,
                 .items = {
                     {.title = "Profile", .action_type = METHOD, .method = Save_ProfileToJson},
                     {.title = "Watches", .action_type = METHOD, .method = Save_WatchesToJson},
                     {.title = "Memfiles", .action_type = METHOD, .method = Save_MemfileToBin}
                 }};

}  // namespace msys
