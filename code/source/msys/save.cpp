
#include "msys/include/menus/save.h"

namespace msys {

  /// Which of the three config blobs the dialog is acting on.
  enum SaveTarget { SAVE_PROFILE, SAVE_WATCHES, SAVE_POSITIONS };

  static void Save_DrawJsonInformation(char* topMsg, char* btmMsg, char* successMsg, char* delMsg, char* failMsg,
                                       Result* saved, char filePath[], SaveTarget target) {
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Draw_Unlock();
    do {
      if (*saved <= 0) {
        Draw_Lock();
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, topMsg);

        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE, btmMsg);

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
        switch (target) {
        case SAVE_PROFILE:
          *saved = File_SaveProfile(commandList);
          break;
        case SAVE_WATCHES:
          *saved = File_SaveWatches(watches);
          break;
        case SAVE_POSITIONS:
          *saved = File_SavePositions(storedPositions);
          break;
        }
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE, "Saving...");
        if (R_FAILED(*saved)) {
          Draw_ClearFramebuffer();
          Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_RED, failMsg);
        } else {
          Draw_ClearFramebuffer();
          Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_GREEN, successMsg);
        }
        Draw_FlushFramebuffer();
        Draw_Unlock();
      } else if (pressed & BUTTON_Y) {
        *saved = File_DeleteFileFromSd(filePath);
        Draw_Lock();
        Draw_ClearFramebuffer();
        Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, delMsg);
        Draw_FlushFramebuffer();
        Draw_Unlock();
      }
    } while (true);
  }

  static void Save_ProfileToJson(void) {
    Result saved = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.bin";
    char saveMsg[] = "Save Current Shortcut Keys?";
    char confirmMsg[] = "Press A to save, B to go back, and Y to delete yourprofile.";
    char successMsg[] = "Save Complete! Press B to go back.";
    char delMsg[] = "Delete Complete! Press B to go back.";
    char failMsg[] = "Save not completed. Error writing to SD.\nPlease restart your game and try again.";

    Save_DrawJsonInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path, SAVE_PROFILE);
  }

  static void Save_WatchesToJson(void) {
    Result saved = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/watches.bin";
    char saveMsg[] = "Save Current Watches?";
    char confirmMsg[] = "Press A to save, B to go back, and Y to delete your watches.";
    char successMsg[] = "Save Complete! Press B to go back.";
    char delMsg[] = "Delete Complete! Press B to go back.";
    char failMsg[] =
        "Save not completed. Please ensure you have watches\nTO save!\nPlease restart your game and try again.";

    Save_DrawJsonInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path, SAVE_WATCHES);
  }

  static void Save_WriteToBin(s32 selected) {
    game::CommonData& cdata = game::GetCommonData();
    game::act::Player* link = rnd::GetContext().gctx->GetPlayerActor();
    // Plain buffer: std::to_string pulls in newlib's float printf. The '#'
    // placeholder is at index 38 and the slot is a single digit.
    char savePath[] = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
    savePath[38] = (char)('0' + (selected % 10));
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, "Saving...");
    if (R_SUCCEEDED(File_SaveContextToSD(&cdata, link, savePath))) {
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_GREEN, "Saved!");
    } else {
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_RED, "Error saving! Please check SD card access/space.");
    }
    Draw_FlushFramebuffer();
    Draw_Unlock();
  }

  static void Save_DeleteMemFile(s32 selected) {
    char savePath[] = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
    savePath[38] = (char)('0' + (selected % 10));
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, "Deleting File...");
    if (R_SUCCEEDED(File_DeleteFileFromSd(savePath))) {
      Draw_ClearFramebuffer();
      Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 40, COLOR_GREEN, "Memfile %i successfully deleted!", selected);
    } else {
      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_RED, "Error deleting! Please ensure this file exists.");
    }
    Draw_FlushFramebuffer();
    Draw_Unlock();
  }

/*
 * Momentum has to be restored after the scene reloads, not before.
 *
 * Loading voids the player: the game rebuilds the scene and respawns Link from
 * the respawn data. Anything written to the player actor at load time is on an
 * actor that is about to be destroyed, so position and facing survive only
 * because they go through the respawn entries -- velocity has nowhere to ride
 * along. It has to be applied to the new actor once it exists.
 *
 * The signal is CommonData::field_13624, the respawn flag, which sits directly
 * before sub13s and behaves like MM's respawnFlag: we set it to request the
 * void, the game clears it when the scene comes back up. Waiting for it to
 * return to zero and for a player actor to exist puts us on the first frame
 * where writing velocity means anything.
 *
 * Guarded two ways in case that assumption does not hold on some path: the
 * actor pointer must also have changed since the load, and the whole thing
 * gives up after a few seconds rather than firing into an unrelated scene.
 */
#define MOMENTUM_TIMEOUT_FRAMES 600

  static PlayerState s_pendingState;
  static const void* s_actorAtLoad = nullptr;
  static u32 s_pendingFrames = 0;

  static void Save_QueueMomentum(const PlayerState& st, const void* actorNow) {
    s_pendingState = st;
    s_actorAtLoad = actorNow;
    s_pendingFrames = MOMENTUM_TIMEOUT_FRAMES;
  }

  void Save_ApplyPendingMomentum(void) {
    if (s_pendingFrames == 0)
      return;
    if (--s_pendingFrames == 0)
      return;  // gave up

    game::CommonData& cdata = game::GetCommonData();
    if (cdata.field_13624 != 0)
      return;  // the void has not been consumed yet

    game::GlobalContext* gctx = rnd::GetContext().gctx;
    if (!gctx)
      return;
    game::act::Player* link = gctx->GetPlayerActor();
    if (!link || link == s_actorAtLoad)
      return;  // same actor: the reload has not happened

    const PlayerState& st = s_pendingState;
    link->vel = st.vel;
    link->vel_xz = st.vel_xz;
    link->vel_y = st.vel_y;
    link->lin_vel = st.lin_vel;
    // The respawn only carries a single yaw, so the rest of the rotation is
    // restored here alongside the momentum it belongs with.
    link->actor_shape.rot = st.shape_rot;
    link->player_angle = st.player_angle;

    s_pendingFrames = 0;
  }

  static void Save_ReadFromBin(s32 selected) {
    game::CommonData& cdata = game::GetCommonData();
    // Static: see File_SaveContextToSD.
    static MemFileT loadBuf;
    MemFileT* newmemfile = &loadBuf;
    // Plain buffer: std::to_string pulls in newlib's float printf. The '#'
    // placeholder is at index 38 and the slot is a single digit.
    char savePath[] = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
    savePath[38] = (char)('0' + (selected % 10));
    Draw_Lock();
    Draw_ClearFramebuffer();
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, "Loading...");

    if (R_SUCCEEDED(File_ReadMemFileFromSd(newmemfile, savePath))) {
      memcpy(static_cast<void*>(&cdata.save), &newmemfile->save, sizeof(game::SaveData));
      memcpy(static_cast<void*>(&cdata.save_backup), &newmemfile->save, sizeof(game::SaveData));
      memcpy(static_cast<void*>(&cdata.sub1), &newmemfile->csub1, sizeof(game::CommonDataSub1));
      memcpy(static_cast<void*>(cdata.sub13s), newmemfile->respawn, sizeof(newmemfile->respawn));

      cdata.time_copy = newmemfile->save.time;
      game::GlobalContext* gctx = rnd::GetContext().gctx;
      const PlayerState& st = newmemfile->player;

      /*
       * Loading works by voiding: the scene reloads and the game places Link from
       * the respawn data, so that is what has to be right. The writes to the
       * player actor below only cover the frames before the reload takes hold.
       *
       * Position and facing both go in. yaw was never set before, so Link came
       * back pointing whichever way the respawn entry already happened to say.
       */
      for (u32 i = 0; i < PZ3D_RESPAWN_SLOTS; ++i) {
        cdata.sub13s[i].pos = st.pos.pos;
        cdata.sub13s[i].yaw = (s16)st.shape_rot.y;
      }
      gctx->next_entrance = cdata.sub13s[0].entrance_index;

      // 0xFFFFFFFB is a void that does no damage. 1 is the usual water void, and
      // 2 zooms the camera and can soft-lock.
      cdata.field_13624 = 0xFFFFFFFB;
      gctx->field_C529_one_to_clear_input = 0x14;

      game::act::Player* link = gctx->GetPlayerActor();
      if (link) {
        link->pos = st.pos;
        link->initial_pos = st.initial_pos;
        link->ztarget_pos = st.ztarget_pos;
        link->actor_shape.rot = st.shape_rot;
        link->player_angle = st.player_angle;
        link->vel = st.vel;
        link->vel_xz = st.vel_xz;
        link->vel_y = st.vel_y;
        link->lin_vel = st.lin_vel;
        link->flags1 = st.flags1;
        link->flags2 = st.flags2;
        link->flags3 = st.flags3;
      }

      // Velocity cannot ride through the void with the respawn data, so it is
      // applied to the new actor once the scene is back.
      Save_QueueMomentum(st, link);

      Draw_ClearFramebuffer();
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_GREEN, "Loaded!");
    } else {
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_RED, "Version not supported!");
    }
    Draw_FlushFramebuffer();
    Draw_Unlock();
  }

  static void Save_PositionsToBin(void) {
    Result saved = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/positions.bin";
    char saveMsg[] = "Save Stored Positions?";
    char confirmMsg[] = "Press A to save, B to go back, and Y to delete them.";
    char successMsg[] = "Save Complete! Press B to go back.";
    char delMsg[] = "Delete Complete! Press B to go back.";
    char failMsg[] = "Save not completed. Error writing to SD.\nPlease restart your game and try again.";

    Save_DrawJsonInformation(saveMsg, confirmMsg, successMsg, delMsg, failMsg, &saved, path, SAVE_POSITIONS);
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
      Draw_DrawString(10, SCREEN_BOT_HEIGHT - 10, COLOR_WHITE, "A to save, Y to load, X to delete");
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
        Save_DeleteMemFile(selected);
      } else if (pressed & MENU_DOWN) {
        selected++;
      } else if (pressed & MENU_UP) {
        selected--;
      }

      if (selected < 0)
        selected = MAX_SAVED_PROFILES - 1;
      else if (selected >= MAX_SAVED_PROFILES)
        selected = 0;
    } while (true);
  }

  Menu SaveMenu = {.title = "SD Card",
                   .nbItems = 4,
                   .items = {{.title = "Profile", .action_type = METHOD, .method = Save_ProfileToJson},
                             {.title = "Watches", .action_type = METHOD, .method = Save_WatchesToJson},
                             {.title = "Positions", .action_type = METHOD, .method = Save_PositionsToBin},
                             {.title = "Memfiles", .action_type = METHOD, .method = Save_MemfileToBin}}};

}  // namespace msys
