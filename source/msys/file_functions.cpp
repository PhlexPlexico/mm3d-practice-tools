
//#include <fstream>
#include "include/file_functions.h"

namespace msys {
  
  bool File_CheckOrCreateProfileDirectory() {
    File_GetHandle();
    FS_Archive sdmcArchive = 0;
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d/mm3d-practice-patch"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return true;
  }

  Result File_SaveProfile(Command* commandList) {
    json jsonToSave = File_WriteCommandListToJson(commandList);
    const char* jsonInChar = jsonToSave.dump(2).c_str();
    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.json";
    if(!R_SUCCEEDED(File_WriteStringFileToSd(jsonInChar, path))) return -1;
    return 1;
  }

  Result File_SaveWatches(Watch* watches) {
    json jsonToSave = File_WriteWatchesToJson(watches);
    if (!jsonToSave.empty()) {
      const char* jsonInChar = jsonToSave.dump(2).c_str();
      char path[] = "/3ds/mm3d/mm3d-practice-patch/watches.json";
      if(!R_SUCCEEDED(File_WriteStringFileToSd(jsonInChar, path))) return -1;
      return 1;
    } else {
      return -1;
    }
  }

  Result File_SaveContextToSD(game::CommonData* cdata, game::act::DayTimerActor* dtBoundaries, s32 idx) {
    MemFileT *newmemfile;
    std::string savePath = "/3ds/mm3d/mm3d-practice-patch/memfile-#.bin";
    savePath.replace(38,1,std::to_string(idx));
    newmemfile = (MemFileT*)malloc(sizeof(*newmemfile));
    // Copy the common data struct.
    memcpy(&newmemfile->file, &cdata, sizeof(newmemfile->file));
    // We don't need the actual actor, just some of the flags stored.
    newmemfile->evening = dtBoundaries->evening;
    newmemfile->unk_1F9 = dtBoundaries->field_1F9;
    newmemfile->time = dtBoundaries->time;
    newmemfile->unk_1FE = dtBoundaries->field_1FE;
    newmemfile->daytimer_calc = dtBoundaries->daytimer_calc;
    newmemfile->unk_208 = dtBoundaries->field_208;

    File_WriteMemFileToSd(newmemfile, savePath.c_str());
    return 1;
  }

  json File_WriteCommandListToJson(Command* commandList) {
    json newJsonStruct;
    for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
      if(strcmp(commandList[i].title, "Reset Input")) {
        newJsonStruct[commandList[i].title]["comboLength"] = commandList[i].comboLen;
        newJsonStruct[commandList[i].title]["inputs"] = commandList[i].inputs;
        newJsonStruct[commandList[i].title]["strict"] = commandList[i].strict;
      }
    }
    return newJsonStruct;
  }

  json File_WriteWatchesToJson(Watch* watches) {
    json newJsonStruct;
    for (u32 i = 0; i < WATCHES_MAX; i++) {
      if(watches[i].addr != NULL) {
        rst::util::Print("Writing watches");
        newJsonStruct[watches[i].name]["watchType"] = watches[i].type;
        newJsonStruct[watches[i].name]["posX"] = watches[i].posX;
        newJsonStruct[watches[i].name]["posY"] = watches[i].posY;
        newJsonStruct[watches[i].name]["address"] = (uintptr_t)watches[i].addr;
        newJsonStruct[watches[i].name]["showOnScreen"] = watches[i].display;
      }
    }
    return newJsonStruct;
  }

  Result File_ReadFromJsonFile(json* jsonFromFile, char path[]) {
    Handle fsHandle = File_GetHandle();
    u64 fileSize = 0;
    char* readJson;

    if(!R_SUCCEEDED(FSUSER_OpenFileDirectly(&fsHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    } 
    rst::util::Print("%s: Made it past open file directly.", __func__);
    // Get the proper size and alloc as necessary.
    FSFILE_GetSize(fsHandle, &fileSize);
    readJson = (char*)malloc(fileSize+1);
    memset(readJson, 0, fileSize);
    rst::util::Print("%s: Malloc'd.", __func__);
    // Read the file into the buffer.
    if(!R_SUCCEEDED(FSFILE_Read(fsHandle, NULL, 0, readJson, fileSize))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -2;
    } 
    rst::util::Print("%s: Made it past read file.", __func__);
    FSFILE_Close(fsHandle);
    File_CloseHandle();
    // Parse the JSON.
    *jsonFromFile = json::parse(readJson, NULL, false);
    if (jsonFromFile->is_discarded()) {
      rst::util::Print("%s: Could not parse JSON. Please check file or create a new one.", __func__);
      return -3;
    }
    return 1;
  }

  Handle File_GetHandle() {
    Handle fsHandle = rst::util::GetPointer<Handle(void)>(0x012DA00)();
    fsUseSession(fsHandle);
    return fsHandle;
  }

  void File_CloseHandle() {
    fsEndUseSession();
    return;
  }

  Result File_WriteStringFileToSd(const char* data, char path[]) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rst::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    } 
    FSUSER_OpenFile(&fsHandle, sdmcArchive, fsMakePath(PATH_ASCII, path), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    FSFILE_Write(fsHandle, NULL, 0, data, strlen(data), FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return 1;
  }

  Result File_WriteMemFileToSd(MemFileT* data, const char* path) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rst::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
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
    Handle fsHandle = File_GetHandle();
    u64 fileSize = 0;

    if(!R_SUCCEEDED(FSUSER_OpenFileDirectly(&fsHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    } 
    rst::util::Print("%s: Made it past open file directly.", __func__);
    // Get the proper size and alloc as necessary.
    FSFILE_GetSize(fsHandle, &fileSize);
    char* buffer = (char*)malloc(fileSize+1);
    memset(buffer, 0, fileSize);
    rst::util::Print("%s: Malloc'd.", __func__);
    // Read the file into the buffer.
    if(!R_SUCCEEDED(FSFILE_Read(fsHandle, NULL, 0, buffer, fileSize))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -2;
    } 
    rst::util::Print("%s: Made it past read file.", __func__);
    FSFILE_Close(fsHandle);
    File_CloseHandle();
    memcpy(data, &buffer, sizeof(buffer));
    rst::util::Print("%s:\nEvening stored? %u\nTime? %i\nDaytimer calc? %lu",
                     __func__, data->time, data->evening, data->daytimer_calc);
    return 1;
  }

  Result File_DeleteFileFromSd(char path[]) {
    FS_Archive sdmcArchive = 0;
    Handle fsHandle = File_GetHandle();
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
      rst::util::Print("%s: Could not open archive. Perhaps it was not closed prior to?", __func__);
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    } 
    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, path));
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return 1;
  }
}  // namespace msys
