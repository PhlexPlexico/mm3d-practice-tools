
//#include <fstream>
#include "include/file_functions.h"
#include "game/addresses.h"

namespace msys {

  bool File_CheckOrCreateProfileDirectory() {
    File_GetHandle();
    FS_Archive sdmcArchive = 0;
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""))))
      return false;
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d/mm3d-practice-patch"),
                           FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return true;
  }

  Result File_SaveProfile(Command* commandList) {
    ProfileEntry entries[COMMAND_NUM_COMMANDS];
    BlobHeader header = {PZ3D_PROFILE_MAGIC, PZ3D_BLOB_VERSION, 0};

    for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
      // "Reset Input" is hard-coded and deliberately not rebindable.
      if (!strcmp(commandList[i].title, "Reset Input"))
        continue;
      ProfileEntry& e = entries[header.count++];
      memset(&e, 0, sizeof(e));
      strncpy(e.title, commandList[i].title, PZ3D_TITLE_MAX - 1);
      e.comboLen = commandList[i].comboLen;
      e.strict = commandList[i].strict;
      for (u32 j = 0; j < COMMAND_COMBO_MAX; ++j)
        e.inputs[j] = commandList[i].inputs[j];
    }

    u8 buffer[sizeof(BlobHeader) + sizeof(entries)];
    memcpy(buffer, &header, sizeof(header));
    memcpy(buffer + sizeof(header), entries, header.count * sizeof(ProfileEntry));

    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.bin";
    return File_WriteBlobToSd(buffer, sizeof(header) + header.count * sizeof(ProfileEntry), path);
  }

  Result File_LoadProfile(Command* commandList) {
    u8 buffer[sizeof(BlobHeader) + COMMAND_NUM_COMMANDS * sizeof(ProfileEntry)];
    u32 read = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.bin";
    if (!R_SUCCEEDED(File_ReadBlobFromSd(buffer, sizeof(buffer), &read, path)))
      return -1;

    BlobHeader header;
    if (read < sizeof(header))
      return -2;
    memcpy(&header, buffer, sizeof(header));
    if (header.magic != PZ3D_PROFILE_MAGIC || header.version != PZ3D_BLOB_VERSION)
      return -3;
    if (read < sizeof(header) + header.count * sizeof(ProfileEntry))
      return -4;

    for (u32 n = 0; n < header.count; ++n) {
      ProfileEntry e;
      memcpy(&e, buffer + sizeof(header) + n * sizeof(ProfileEntry), sizeof(e));
      e.title[PZ3D_TITLE_MAX - 1] = 0;
      // Matched by name: reordering the command list must not rebind controls.
      for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
        if (strcmp(commandList[i].title, e.title))
          continue;
        if (e.comboLen > COMMAND_COMBO_MAX)
          break;  // corrupt entry; keep the default binding
        commandList[i].comboLen = e.comboLen;
        commandList[i].strict = e.strict;
        for (u32 j = 0; j < COMMAND_COMBO_MAX; ++j)
          commandList[i].inputs[j] = e.inputs[j];
        break;
      }
    }
    return 1;
  }

  Result File_SaveWatches(Watch* watches) {
    WatchEntry entries[WATCHES_MAX];
    BlobHeader header = {PZ3D_WATCHES_MAGIC, PZ3D_BLOB_VERSION, 0};

    for (u32 i = 0; i < WATCHES_MAX; ++i) {
      if (watches[i].addr == NULL)
        continue;
      WatchEntry& e = entries[header.count++];
      memset(&e, 0, sizeof(e));
      strncpy(e.name, watches[i].name, WATCHES_MAXNAME);
      e.display = watches[i].display;
      e.type = (u32)watches[i].type;
      e.posX = watches[i].posX;
      e.posY = watches[i].posY;
      static_assert(sizeof(void*) == sizeof(u32));
      e.addr = (u32)(uintptr_t)watches[i].addr;
    }

    u8 buffer[sizeof(BlobHeader) + sizeof(entries)];
    memcpy(buffer, &header, sizeof(header));
    memcpy(buffer + sizeof(header), entries, header.count * sizeof(WatchEntry));

    char path[] = "/3ds/mm3d/mm3d-practice-patch/watches.bin";
    return File_WriteBlobToSd(buffer, sizeof(header) + header.count * sizeof(WatchEntry), path);
  }

  Result File_LoadWatches(Watch* watches) {
    u8 buffer[sizeof(BlobHeader) + WATCHES_MAX * sizeof(WatchEntry)];
    u32 read = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/watches.bin";
    if (!R_SUCCEEDED(File_ReadBlobFromSd(buffer, sizeof(buffer), &read, path)))
      return -1;

    BlobHeader header;
    if (read < sizeof(header))
      return -2;
    memcpy(&header, buffer, sizeof(header));
    if (header.magic != PZ3D_WATCHES_MAGIC || header.version != PZ3D_BLOB_VERSION)
      return -3;
    if (header.count > WATCHES_MAX || read < sizeof(header) + header.count * sizeof(WatchEntry))
      return -4;

    for (u32 i = 0; i < header.count; ++i) {
      WatchEntry e;
      memcpy(&e, buffer + sizeof(header) + i * sizeof(WatchEntry), sizeof(e));
      e.name[WATCHES_MAXNAME] = 0;
      strncpy(watches[i].name, e.name, WATCHES_MAXNAME + 1);
      watches[i].display = e.display;
      watches[i].type = (WatchType)e.type;
      watches[i].posX = e.posX;
      watches[i].posY = e.posY;
      watches[i].addr = (void*)(uintptr_t)e.addr;
    }
    return 1;
  }

  Result File_SavePositions(StoredPosition* positions) {
    PositionEntry entries[POSITION_SLOTS];
    BlobHeader header = {PZ3D_POSITIONS_MAGIC, PZ3D_BLOB_VERSION, POSITION_SLOTS};

    for (u32 i = 0; i < POSITION_SLOTS; ++i) {
      memset(static_cast<void*>(&entries[i]), 0, sizeof(entries[i]));
      entries[i].used = positions[i].used;
      entries[i].angle = positions[i].angle;
      entries[i].pos = positions[i].pos;
    }

    u8 buffer[sizeof(BlobHeader) + sizeof(entries)];
    memcpy(buffer, &header, sizeof(header));
    memcpy(buffer + sizeof(header), entries, sizeof(entries));

    char path[] = "/3ds/mm3d/mm3d-practice-patch/positions.bin";
    return File_WriteBlobToSd(buffer, sizeof(buffer), path);
  }

  Result File_LoadPositions(StoredPosition* positions) {
    u8 buffer[sizeof(BlobHeader) + POSITION_SLOTS * sizeof(PositionEntry)];
    u32 read = 0;
    char path[] = "/3ds/mm3d/mm3d-practice-patch/positions.bin";
    if (!R_SUCCEEDED(File_ReadBlobFromSd(buffer, sizeof(buffer), &read, path)))
      return -1;

    BlobHeader header;
    if (read < sizeof(header))
      return -2;
    memcpy(&header, buffer, sizeof(header));
    if (header.magic != PZ3D_POSITIONS_MAGIC || header.version != PZ3D_BLOB_VERSION)
      return -3;
    // Fewer slots than we have is fine -- an older file just leaves the rest
    // empty. More than we have is not, so it is clamped rather than trusted.
    u32 count = header.count < POSITION_SLOTS ? header.count : POSITION_SLOTS;
    if (read < sizeof(header) + count * sizeof(PositionEntry))
      return -4;

    for (u32 i = 0; i < count; ++i) {
      PositionEntry e;
      memcpy(&e, buffer + sizeof(header) + i * sizeof(PositionEntry), sizeof(e));
      positions[i].used = e.used ? 1 : 0;
      positions[i].angle = e.angle;
      positions[i].pos = e.pos;
    }
    return 1;
  }

  Result File_SaveContextToSD(game::CommonData* cdata, game::act::Player* player, const char* path) {
    // Static: MemFileT is ~6.9KB, too big for the menu thread's 12KB stack, and
    // operator new would drag in std::bad_alloc's unwinder for a single user.
    static MemFileT memfileBuf;
    MemFileT* newmemfile = &memfileBuf;
    /*
     * Through a void*, not the struct directly. MemFileT holds game structs
     * that are not trivially copyable, so memset/memcpy on them warns -- but
     * this is a blob written to disk verbatim, so a byte-wise clear is exactly
     * what is wanted. The cast is the documented way to say so.
     *
     * Not `newmemfile = {}`: that assigns nullptr to the pointer, and every
     * field write below then goes through it.
     */
    memset(static_cast<void*>(newmemfile), 0, sizeof(MemFileT));

    newmemfile->pzversion = PZ3D_VERSION;

    memcpy(static_cast<void*>(&newmemfile->save), &cdata->save, sizeof(game::SaveData));
    memcpy(static_cast<void*>(&newmemfile->csub1), &cdata->sub1, sizeof(game::CommonDataSub1));
    // Every respawn slot, not just the first.
    memcpy(static_cast<void*>(newmemfile->respawn), cdata->sub13s, sizeof(newmemfile->respawn));

    PlayerState& st = newmemfile->player;
    st.pos = player->pos;
    st.initial_pos = player->initial_pos;
    st.ztarget_pos = player->ztarget_pos;
    st.shape_rot = player->actor_shape.rot;
    st.player_angle = player->player_angle;
    st.vel = player->vel;
    st.vel_xz = player->vel_xz;
    st.vel_y = player->vel_y;
    st.lin_vel = player->lin_vel;
    st.flags1 = player->flags1;
    st.flags2 = player->flags2;
    st.flags3 = player->flags3;

    File_WriteMemFileToSd(newmemfile, path);
    return 1;
  }

  Handle File_GetHandle() {
    Handle fsHandle = rnd::util::GetPointer<Handle(void)>(ADDR_File_GetHandle_12DA00)();
    fsUseSession(fsHandle);
    return fsHandle;
  }

  void File_CloseHandle() {
    fsEndUseSession();
    return;
  }

  Result File_WriteBlobToSd(const void* data, u32 length, const char* path) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rnd::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    }
    FSUSER_OpenFile(&fsHandle, sdmcArchive, fsMakePath(PATH_ASCII, path), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    // Truncate first, or a shorter blob leaves a tail of the previous one.
    FSFILE_SetSize(fsHandle, length);
    FSFILE_Write(fsHandle, NULL, 0, data, length, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return 1;
  }

  Result File_ReadBlobFromSd(void* out, u32 maxLength, u32* outLength, const char* path) {
    Handle fsHandle = File_GetHandle();
    u64 fileSize = 0;

    if (!R_SUCCEEDED(FSUSER_OpenFileDirectly(&fsHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""),
                                             fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    }
    FSFILE_GetSize(fsHandle, &fileSize);
    if (fileSize > maxLength)
      fileSize = maxLength;
    // No allocation: nothing to leak on the error paths.
    u32 bytesRead = 0;
    if (!R_SUCCEEDED(FSFILE_Read(fsHandle, &bytesRead, 0, out, (u32)fileSize))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -2;
    }
    FSFILE_Close(fsHandle);
    File_CloseHandle();
    if (outLength)
      *outLength = bytesRead;
    return 1;
  }

  Result File_WriteMemFileToSd(MemFileT* data, const char* path) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rnd::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    }
    FSUSER_OpenFile(&fsHandle, sdmcArchive, fsMakePath(PATH_ASCII, path), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    FSFILE_Write(fsHandle, NULL, 0, data, sizeof(MemFileT), FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return 1;
  }

  Result File_ReadMemFileFromSd(MemFileT* data, const char* path) {
    // Straight into the caller's struct: the previous version leaked a ~6.9KB
    // scratch buffer on every call, against a 64KB heap.
    u32 read = 0;
    if (!R_SUCCEEDED(File_ReadBlobFromSd(data, sizeof(MemFileT), &read, path)))
      return -1;
    if (read < sizeof(MemFileT))
      return -2;
    if (data->pzversion != PZ3D_VERSION)
      return -1;
    return 1;
  }

  Result File_DeleteFileFromSd(char path[]) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rnd::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    }
    if (!R_SUCCEEDED(FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, path)))) {
      FSFILE_Close(fsHandle);
      FSUSER_CloseArchive(sdmcArchive);
      File_CloseHandle();
      return -1;
    } else {
      FSFILE_Close(fsHandle);
      FSUSER_CloseArchive(sdmcArchive);
      File_CloseHandle();
      return 1;
    }
  }
}  // namespace msys
