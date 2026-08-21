/**
 * @file actorresource.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */

#include "game/actorresource.h"
#include "game/addresses.h"

namespace game::ActorResource {

  u32 find(ActorResources* resources, int object_id) {
    return rnd::util::GetPointer<u32(ActorResources*, int)>(ADDR_find_1F57DC)(resources, object_id);
  }

  // Returns a value of (ObjectBankArchive->field_0 + 1 & 0xff) - 1 - It's the Actors Object ID!
  u32 loadActorResource(ActorResources* archive, u32 actor_id) {
    return rnd::util::GetPointer<u32(ActorResources*, u32)>(ADDR_loadActorResource_4C01CC)(archive, actor_id);
  }

  void freeActorResource(ActorResource* resource) {
    return rnd::util::GetPointer<void(ActorResource*)>(ADDR_freeActorResource_14E8F4)(resource);
  }

  // Returns a pointer to the array of the Overlay Table.
  // This is known as gActorOverlay in OoT3DR.
  ActorResourcePath* GetActorResourcePathTable() {
    return rnd::util::GetPointer<ActorResourcePath>(ADDR_GetActorResourcePathTable_6927E4);
  }

}  // namespace game::ActorResource

// 0x804af5c
// 0x804af5c Object Context - Watch point this
//  804af58
//  8041b20 Fairly static global context.