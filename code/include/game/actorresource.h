/**
 * @file actorresources.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#pragma once
#define OBJECT_EXCHANGE_BANK_MAX 36

#include "common/types.h"
#include "common/utils.h"
#include "game/objectbankarchive.h"

namespace game::ActorResource {
  // Same as ObjectStatus in OoT3DR
  struct ActorResource {
    u16 object_id;
    u16 field_2;
    ResArchiveHeader* file_data;
    u32 file_size;
    u32 file;
    game::ObjectBank::ObjectBankArchive archive;
  };
  static_assert(sizeof(ActorResource) == 0xAC);

  struct ActorResources {
    u8 flags;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    ActorResource resources[387];
  };
  static_assert(sizeof(ActorResources) == 0x10408);

  struct ActorResourcePath {
    char path[52];
  };
  static_assert(sizeof(ActorResourcePath) == 0x34);

  struct ObjectContext {
    u8 num;
    u8 numPersistent;
    char gap_02[2];
    ActorResource status[OBJECT_EXCHANGE_BANK_MAX];
  };
  static_assert(sizeof(ObjectContext) == 0x1834);

  u32 find(ActorResources*, int);
  u32 loadActorResource(ActorResources*, u32);
  void freeActorResource(ActorResource*);
  ActorResourcePath* GetActorResourcePathTable();

}  // namespace game::ActorResource
