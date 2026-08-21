#pragma once

#include "common/types.h"

namespace game {

  struct ResArchiveHeader {
    u32 magic;
    u32 size;
    u16 num_types;
    u16 num_files;
    u32 types_offest;
    u32 info_offset;
    u32 data_offsets_offset;
    char creator[8];
  };
  static_assert(sizeof(ResArchiveHeader) == 0x20);

  struct ResArchiveFileType {
    u32 numFiles;
    u32 file_indices_offset;
    u32 name_offset;
    u32 field_C;
  };
  static_assert(sizeof(ResArchiveFileType) == 0x10);

  struct ResArchiveFileInfo {
    u32 size;
    u32 file_name_offset;
    u32 path_offset;
  };
  static_assert(sizeof(ResArchiveFileInfo) == 0x0C);

  enum class ResFileType {
    CMB,    // CtrModelBinary
    CSAB,   // CtrSkeletalAnimationBinary
    CTXB,   // CtrTextureBinary
    PTXB,   // ProceduralTextureBinary
    CMAB,   // CtrMaterialAnimationBinary
    ZSI,    // ZeldaSceneInformation: Scene data
    QDB,    // QueenDatabase(?): Cutscene/script commands?
    FACEB,  // FaceBinary(?): Is this different/unused in MM3D?
    TBD,    // TempBinaryData(?): Used for storm/lens flare params
    CCB,    // CtrCameraBinary: Camera animations
    LINKB,  // LinkBinary(?): Facial animation data
    COLB,   // ColorBinary: Vertex colors the sky lerps between
    GFB,    // GraphicsBinary: Particle container? Contains .ctxb texture(s) too
    VWX,    // Vertex(?): Vertex deform data for water?
    OTHER,  // Unknown file types go here
    Count,
  };

  inline const char* ResFileType_GetExtension(ResFileType type) {
    switch (type) {
    case ResFileType::CMB:
      return "cmb";
    case ResFileType::CSAB:
      return "csab";
    case ResFileType::CTXB:
      return "ctxb";
    case ResFileType::PTXB:
      return "ptxb";
    case ResFileType::CMAB:
      return "cmab";
    case ResFileType::ZSI:
      return "zsi";
    case ResFileType::QDB:
      return "qdb";
    case ResFileType::FACEB:
      return "faceb";
    case ResFileType::TBD:
      return "tbd";
    case ResFileType::CCB:
      return "ccb";
    case ResFileType::LINKB:
      return "linkb";
    case ResFileType::COLB:
      return "colb";
    case ResFileType::GFB:
      return "gfb";
    case ResFileType::VWX:
      return "vwx";
    case ResFileType::OTHER:
      return "unknown";
    default:
      return "";
    }
  }

  inline bool ResArchive_StrEq(const char* a, const char* b) {
    while (*a && *a == *b) {
      ++a;
      ++b;
    }
    return *a == *b;
  }

  inline ResArchiveFileType* ResArchive_GetTypes(void* raw) {
    auto* header = static_cast<ResArchiveHeader*>(raw);
    return reinterpret_cast<ResArchiveFileType*>(static_cast<u8*>(raw) + header->types_offest);
  }

  inline u32* ResArchive_GetDataOffsets(void* raw) {
    auto* header = static_cast<ResArchiveHeader*>(raw);
    return reinterpret_cast<u32*>(static_cast<u8*>(raw) + header->data_offsets_offset);
  }

  inline ResArchiveFileType* ResArchive_FindType(void* raw, ResFileType type) {
    auto* header = static_cast<ResArchiveHeader*>(raw);
    ResArchiveFileType* types = ResArchive_GetTypes(raw);
    const char* ext = ResFileType_GetExtension(type);
    for (u16 i = 0; i < header->num_types; ++i) {
      const char* name = reinterpret_cast<const char*>(static_cast<u8*>(raw) + types[i].name_offset);
      if (ResArchive_StrEq(name, ext))
        return &types[i];
    }
    return nullptr;
  }

  inline s32 ResArchive_GetFileIndex(void* gar, ResFileType type, u32 indexInType) {
    ResArchiveFileType* group = ResArchive_FindType(gar, type);
    if (group == nullptr || indexInType >= group->numFiles)
      return -1;
    auto* indices = reinterpret_cast<s32*>(static_cast<u8*>(gar) + group->file_indices_offset);
    return indices[indexInType];
  }

  inline void* ResArchive_GetFileByType(void* gar, ResFileType type, u32 indexInType = 0) {
    s32 fileIndex = ResArchive_GetFileIndex(gar, type, indexInType);
    if (fileIndex < 0)
      return nullptr;
    return static_cast<u8*>(gar) + ResArchive_GetDataOffsets(gar)[fileIndex];
  }

}  // namespace game
