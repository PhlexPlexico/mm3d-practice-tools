
//#include <fstream>
#include "include/file_functions.h"

namespace msys {
  
  bool check_or_create_profile_directory() {
    get_handle();
    FS_Archive sdmcArchive = 0;
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/mm3d/mm3d-practice-patch"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CloseArchive(sdmcArchive);
    close_handle();
    return true;
  }
  bool save_file(Command* commandList) {
    json jsonToSave = write_to_json(commandList);
    Handle fsHandle = get_handle();
    char path[] = "/3ds/mm3d/mm3d-practice-patch/test.json";
    FS_Archive sdmcArchive = 0;
    if(!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
    FSUSER_OpenFile(&fsHandle, sdmcArchive, fsMakePath(PATH_ASCII, path), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
    u32 bytesWritten = 0;
    FSFILE_Write(fsHandle, &bytesWritten, 0, &jsonToSave, sizeof(jsonToSave), FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
    FSFILE_Close(fsHandle);
    FSUSER_CloseArchive(sdmcArchive);
    close_handle();
    return true;
  }
  json write_to_json(Command* commandList) {
    json newJsonStruct;
    for (u32 i = 0; i < COMMAND_NUM_COMMANDS; ++i) {
      newJsonStruct[commandList[i].title]["comboLength"] = commandList[i].comboLen;
      newJsonStruct[commandList[i].title]["inputs"] = commandList[i].inputs;
      newJsonStruct[commandList[i].title]["strict"] = commandList[i].strict;
    }
    return newJsonStruct;
  }
  Handle get_handle() {
    Handle fsHandle = rst::util::GetPointer<Handle(void)>(0x012DA00)();
    fsUseSession(fsHandle);
    return fsHandle;
  }
  void close_handle() {
    fsEndUseSession();
    return;
  }
}  // namespace msys
