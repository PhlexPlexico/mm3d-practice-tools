#include "game/objectbankarchive.h"
#include "game/addresses.h"

namespace game::ObjectBank {
  // set_field_5c always = 0 in code calls.
  void init(ObjectBankArchive* obj_bank_archive, u32 actor_id, ResArchiveHeader* data, int size, char set_field_5c) {
    return rnd::util::GetPointer<void(ObjectBankArchive*, u32, ResArchiveHeader*, int, char)>(ADDR_find_1F57DC)(
        obj_bank_archive, actor_id, data, size, set_field_5c);
  }
  void* getCMBManByIndex(ObjectBankArchive* obj_bank_archive, u32 cmb_file_index, u32 archive_type) {
    return rnd::util::GetPointer<void*(ObjectBankArchive*, u32, u32)>(ADDR_getCMBManByIndex_1F5C00)(
        obj_bank_archive, cmb_file_index, archive_type);
  }
  void free(ObjectBankArchive* obj_bank_archive) {
    return rnd::util::GetPointer<void(ObjectBankArchive*)>(ADDR_free_1E477C)(obj_bank_archive);
  }

  ObjectBankArchive* freeAndCleanup(ObjectBankArchive* obj_bank_archive) {
    return rnd::util::GetPointer<ObjectBankArchive*(ObjectBankArchive*)>(ADDR_freeAndCleanup_1616B8)(obj_bank_archive);
  }
}  // namespace game::ObjectBank