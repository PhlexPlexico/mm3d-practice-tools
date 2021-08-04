
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
  bool File_SaveProfile(Command* commandList) {
    json jsonToSave = File_WriteCommandListToJson(commandList);
    const char* jsonInChar = jsonToSave.dump(2).c_str();
    char path[] = "/3ds/mm3d/mm3d-practice-patch/profile.json";
    File_WriteStringFileToSd(jsonInChar, path);
    return true;
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
    readJson = (char*)malloc(fileSize+1024);
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
    // XXX: Maybe check the parse before setting?
    *jsonFromFile = json::parse(readJson);
    return 0;
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
  bool File_WriteStringFileToSd(const char* data, char path[]) {
    FS_Archive sdmcArchive = 0;
    u32 bytesWritten = 0;
    Handle fsHandle = File_GetHandle();
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
    FSUSER_OpenFile(&fsHandle, sdmcArchive, fsMakePath(PATH_ASCII, path), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    FSFILE_Write(fsHandle, &bytesWritten, 0, data, strlen(data), FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    File_CloseHandle();
    return true;
  }
}  // namespace msys
