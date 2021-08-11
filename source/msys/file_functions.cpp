
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
    File_WriteStringFileToSd(jsonInChar, path);
    return 1;
  }

  Result File_SaveWatches(Watch* watches) {
    json jsonToSave = File_WriteWatchesToJson(watches);
    if (!jsonToSave.empty()) {
      const char* jsonInChar = jsonToSave.dump(2).c_str();
      rst::util::Print("%s", jsonInChar);
      char path[] = "/3ds/mm3d/mm3d-practice-patch/watches.json";
      File_WriteStringFileToSd(jsonInChar, path);
      return 1;
    } else {
      return -1;
    }
    
    
  }

  json File_WriteCommandListToJson(Command* commandList) {
    json newJsonStruct;
    for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
      newJsonStruct[commandList[i].title]["comboLength"] = commandList[i].comboLen;
      newJsonStruct[commandList[i].title]["inputs"] = commandList[i].inputs;
      newJsonStruct[commandList[i].title]["strict"] = commandList[i].strict;
    }
    return newJsonStruct;
  }

  json File_WriteWatchesToJson(Watch* watches) {
    json newJsonStruct;
    for (u32 i = 0; i < WATCHES_MAX; i++) {
      if(watches[i].addr != NULL) {
        rst::util::Print("Writing watches");
        char addr[13];
        sprintf(addr, "%p", watches[i].addr);
        newJsonStruct[watches[i].name]["watchType"] = watches[i].type;
        newJsonStruct[watches[i].name]["posX"] = watches[i].posX;
        newJsonStruct[watches[i].name]["posY"] = watches[i].posY;
        newJsonStruct[watches[i].name]["address"] = addr;
        newJsonStruct[watches[i].name]["showOnScreen"] = watches[i].display;
      }
    }
    return newJsonStruct;
  }

  Result File_ReadCommandListFromJson(json* jsonFromFile, char path[]) {
    Handle fsHandle = File_GetHandle();
    u64 fileSize = 0;
    char* readJson;

    if(!R_SUCCEEDED(FSUSER_OpenFileDirectly(&fsHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -1;
    } 
    // Get the proper size and alloc as necessary.
    FSFILE_GetSize(fsHandle, &fileSize);
    readJson = (char*)malloc(fileSize+1);
    memset(readJson, 0, fileSize);

    // Read the file into the buffer.
    if(!R_SUCCEEDED(FSFILE_Read(fsHandle, NULL, 0, readJson, fileSize))) {
      FSFILE_Close(fsHandle);
      File_CloseHandle();
      return -2;
    } 
    FSFILE_Close(fsHandle);
    File_CloseHandle();
    // Parse the JSON.
    *jsonFromFile = json::parse(readJson, NULL, false);
    if (*jsonFromFile == json::value_t::discarded) {
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
}  // namespace msys
