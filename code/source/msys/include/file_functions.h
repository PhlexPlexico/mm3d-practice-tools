extern "C" {
#include <3ds/result.h>
#include <3ds/services/fs.h>
}
#include <stdio.h>
#include "common/debug.h"
#include "common/flags.h"
#include "common/utils.h"
#include "game/actor.h"
#include "game/common_data.h"
#include "game/player.h"
#include "menus/commands.h"
#include "menus/watches.h"
#include "z3d/z3DVec.h"

namespace msys {
#define MAX_SAVED_PROFILES 3
#define PZ3D_MEMFILE_MAX 3
#define PZ3D_VERSION 2
#define PZ3D_RESPAWN_SLOTS 8
  /*
   * Link's kinematic state at the moment the memfile was written.
   *
   * The save file covers what he has; this covers where he was and how he was
   * moving. Kept as its own struct so the save and load paths cannot disagree
   * about which fields are part of it.
   */
  typedef struct {
    game::act::PosRot pos;
    game::act::PosRot initial_pos;
    game::act::PosRot ztarget_pos;
    z3dVec3s shape_rot;  // full rotation; only .y used to be kept
    u16 player_angle;    // the angle movement uses, distinct from the visual one
    z3dVec3f vel;
    float vel_xz;
    float vel_y;
    float lin_vel;
    rnd::Flags<game::act::Player::Flag1> flags1;
    rnd::Flags<game::act::Player::Flag2> flags2;
    rnd::Flags<game::act::Player::Flag3> flags3;
  } PlayerState;

  typedef struct {
    u8 pzversion;
    game::SaveData save;
    game::CommonDataSub1 csub1;
    /*
     * All of them. CommonData::sub13s is an array of eight -- one per respawn
     * mode -- and only the first used to be written, while the load path went
     * on to modify the third. Saving one and restoring into several left the
     * rest holding whatever the previous scene had put there.
     */
    game::RespawnData respawn[PZ3D_RESPAWN_SLOTS];
    PlayerState player;
  } MemFileT;

  // The whole array, or restoring one slot leaves the others stale.
  static_assert(PZ3D_RESPAWN_SLOTS == sizeof(game::CommonData::sub13s) / sizeof(game::RespawnData));

  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
/*
 * On-disk format for the two config files. Entries are keyed by name, not
 * index, so reordering commands cannot silently rebind anyone's controls;
 * unknown names are skipped and missing ones keep their defaults.
 */
#define PZ3D_PROFILE_MAGIC 0x50335A50u   /* 'PZ3P' */
#define PZ3D_WATCHES_MAGIC 0x57335A50u   /* 'PZ3W' */
#define PZ3D_POSITIONS_MAGIC 0x4F335A50u /* 'PZ3O' */
#define PZ3D_BLOB_VERSION 1
#define PZ3D_TITLE_MAX 32

  typedef struct {
    u32 magic;
    u16 version;
    u16 count;
  } BlobHeader;

  typedef struct {
    char title[PZ3D_TITLE_MAX];
    u32 comboLen;
    u32 inputs[COMMAND_COMBO_MAX];
    u32 strict;
  } ProfileEntry;

  /*
   * Positions are the one thing keyed by slot rather than by name -- the slot
   * number is the identity, so the file is a straight array and an unused slot
   * is written out too, keeping index and position in step.
   */
  typedef struct {
    u8 used;
    u16 angle;
    game::act::PosRot pos;
  } PositionEntry;

  typedef struct {
    char name[WATCHES_MAXNAME + 1];
    u8 display;
    u32 type;
    u32 posX;
    u32 posY;
    u32 addr;
  } WatchEntry;

  bool File_CheckOrCreateProfileDirectory();
  Handle File_GetHandle();
  void File_CloseHandle();
  Result File_SaveProfile(Command*);
  Result File_LoadProfile(Command*);
  Result File_SaveWatches(Watch*);
  Result File_LoadWatches(Watch*);
  Result File_SavePositions(StoredPosition*);
  Result File_LoadPositions(StoredPosition*);
  Result File_SaveContextToSD(game::CommonData*, game::act::Player*, const char*);
  Result File_WriteBlobToSd(const void*, u32, const char*);
  Result File_ReadBlobFromSd(void*, u32, u32*, const char*);
  Result File_WriteMemFileToSd(MemFileT*, const char*);
  Result File_ReadMemFileFromSd(MemFileT*, const char*);
  Result File_DeleteFileFromSd(char[]);
}  // namespace msys
