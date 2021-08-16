
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
  game::GlobalContext* gctx = rst::GetContext().gctx;
  game::act::DayTimerActor* boundaryWrites;
  for (size_t actSize = 0; actSize < gctx->actors.lists.size(); ++actSize) {
    game::ActorList& actorList = gctx->actors.lists[actSize];
    for (game::act::Actor* actor = actorList.first; actor; actor = actor->next) {
      if (actor->id == game::act::Id::DayTimer) {
        boundaryWrites = (game::act::DayTimerActor*)actor;
        break;
      }
    }
  }
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_TITLE,
                      "Saving...");
  if(R_SUCCEEDED(File_SaveContextToSD(&cdata, boundaryWrites, selected))) {
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_GREEN,
                      "Saved!");
  }
  Draw_FlushFramebuffer();
  Draw_Unlock();
}

static void Save_ReadFromBin(s32 selected) {
  game::CommonData& cdata = game::GetCommonData();
  game::GlobalContext* gctx = rst::GetContext().gctx;
  game::act::DayTimerActor* boundaryWrites = NULL;
  for (size_t actSize = 0; actSize < gctx->actors.lists.size(); ++actSize) {
    game::ActorList& actorList = gctx->actors.lists[actSize];
    for (game::act::Actor* actor = actorList.first; actor; actor = actor->next) {
      if (actor->id == game::act::Id::DayTimer) {
        boundaryWrites = (game::act::DayTimerActor*)actor;
        break;
      }
    }
  }
  MemFileT* newmemfile = new MemFileT();
  std::string savePath = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
  savePath.replace(38,1,std::to_string(selected));
  Draw_Lock();
  Draw_ClearFramebuffer();
  Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_TITLE,
                      "Loading...");
  rst::util::Print("%s:PRELOAD\nEvening stored? %u\nTime? %i\nDaytimer calc? %lu", 
                     __func__, newmemfile->evening, newmemfile->time, newmemfile->daytimer_calc);
  if(R_SUCCEEDED(File_ReadMemFileFromSd(newmemfile, savePath.c_str()))) {
    rst::util::Print("%s: \nEvening stored? %u\nTime? %i\nDaytimer calc? %lu\n\n\nSave data time: %lu", 
                     __func__, newmemfile->evening, newmemfile->time, newmemfile->daytimer_calc, cdata.save.time);
    // memcpy(&cdata, &newmemfile->file, sizeof(game::CommonData));
    
    // memcpy(&cdata.sub1, &newmemfile->sub1, sizeof(game::CommonDataSub1));
    memcpy(&cdata, &newmemfile->file, sizeof(game::CommonData));
    memcpy(&cdata.save, &newmemfile->save, sizeof(game::SaveData));
    memcpy(&cdata.save_backup, &newmemfile->save, sizeof(game::SaveData));
    memcpy(&cdata.sub1, &newmemfile->csub1, sizeof(game::CommonDataSub1));
    memcpy(&cdata.sub3, &newmemfile->csub3, sizeof(game::CommonDataSub3));
    memcpy(&cdata.sub4, &newmemfile->csub4, sizeof(game::CommonDataSub4));
    memcpy(&cdata.sub5, &newmemfile->csub5, sizeof(game::CommonDataSub5));
    memcpy(&cdata.sub6, &newmemfile->csub6, sizeof(game::CommonDataSub6));
    memcpy(&cdata.sub7, &newmemfile->csub7, sizeof(game::CommonDataSub7));
    memcpy(&cdata.sub8, &newmemfile->csub8, sizeof(game::CommonDataSub8));
    memcpy(&cdata.sub9, &newmemfile->csub9, sizeof(game::CommonDataSub9));
    memcpy(&cdata.sub10, &newmemfile->csub10, sizeof(game::CommonDataSub10));
    memcpy(&cdata.sub11, &newmemfile->csub11, sizeof(game::CommonDataSub11));
    memcpy(&cdata.sub12, &newmemfile->csub12, sizeof(game::CommonDataSub12));
    memcpy(&cdata.sub13s, &newmemfile->respawn, sizeof(game::RespawnData));
    boundaryWrites->evening = newmemfile->evening;
    boundaryWrites->field_1F9 = newmemfile->unk_1F9;
    boundaryWrites->time = newmemfile->save.time;
    boundaryWrites->field_1FE = newmemfile->unk_1FE;
    boundaryWrites->daytimer_calc = newmemfile->daytimer_calc;
    boundaryWrites->field_208 = newmemfile->unk_208;
    cdata.save.time = newmemfile->save.time;
    rst::util::Print("%s: Time is now %lu", cdata.save.time);
    EntranceWarp(cdata.sub1.entrance);
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 60, COLOR_GREEN,
                      "Loaded!");
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
