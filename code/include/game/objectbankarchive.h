#pragma once

#include "common/types.h"
#include "common/utils.h"
#include "game/cmb.h"
#include "game/resarchiveheader.h"

namespace game::ObjectBank {
  struct Archive {
    u8* raw;
    ResArchiveHeader* header;
    ResArchiveFileType* types;
    ResArchiveFileInfo* info;
    u32* data_offsets;
  };
  static_assert(sizeof(Archive) == 0x14);

  struct CsabMan {
    u32 field_0;
    u32 field_4;
    u8 field_8;
  };  // size == 0x09?
  static_assert(sizeof(CsabMan) == 0x0C);

  struct CmabMan {
    void* vtable;
    int field_4;
    u8 field_8;
    u8 gap_9[3];
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
  };  // size == 0x09?
  static_assert(sizeof(CmabMan) == 0x1C);

  struct CmbSkeleton {
    cmb::Skeleton* skl;
    // Likely incomplete.
  };

  struct CmbMan {
    void** vtable;       // 0 = init(CmbMan*, void* rawCmbData)
    cmb::CMB_HEAD* cmb;  // the raw CMB
    u8 gap_08[0x1C];
    CmbSkeleton* skeleton;
    u8 gap_28[0x24];
  };
  static_assert(offsetof(CmbMan, cmb) == 0x4);
  static_assert(offsetof(CmbMan, skeleton) == 0x24);
  static_assert(sizeof(CmbMan) == 0x4C);

  struct ObjectBankArchive {
    u32 field_0;
    Archive archive;
    u32 archive_data;
    u32 file_type_indices[16];
    u8 field_5C;
    u8 gap_5D;
    u16 actor_id;
    CmbMan** cmb_files;
    CsabMan** csab_files;
    void** ctxb_files;
    void** ptxb_files;
    CmabMan** cmab_files;
    void** zsi_files;
    void** qdb_files;
    void** faceb_files;
    void** tbd_files;
    void** ccb_files;
    void** linkb_files;
    void** colb_files;
    void** gfb_files;
    void** vwx_files;
    void** other_files;
  };
  static_assert(sizeof(ObjectBankArchive) == 0x9C);

  void init(ObjectBankArchive*, u32, ResArchiveHeader*, int, char);
  void* getCMBManByIndex(ObjectBankArchive*, u32, u32);
  void free(ObjectBankArchive*);
  ObjectBankArchive* freeAndCleanup(ObjectBankArchive*);
}  // namespace game::ObjectBank
