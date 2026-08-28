/**
 * @file actor.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */

#include "game/as.h"
#include "game/addresses.h"

#include "common/utils.h"

namespace game::as {

  void ActorUtil::PlayAnim(u32 id, float x) {
    rnd::util::GetPointer<void(ActorUtil*, u32, float)>(ADDR_PlayAnim_51689C)(this, id, x);
  }

  void ActorUtil::PlayAnimFull(u32 id, float x) {
    rnd::util::GetPointer<void(ActorUtil*, u32, float)>(ADDR_PlayAnimFull_5153C8)(this, id, x);
  }

  int ActorUtil::GetAnimDuration(u32 id) {
    return rnd::util::GetPointer<int(ActorUtil*, u32)>(ADDR_GetAnimDuration_240DD8)(this, id);
  }

  void ActorUtil_Construct(game::ObjectBank::ObjectBankArchive* archive, game::GlobalContext* gctx,
                           game::as::ActorUtil* actorUtil, void* cmbMan, s32 animId, void* boneMtxBuf) {
    rnd::util::GetPointer<int(game::ObjectBank::ObjectBankArchive*, game::GlobalContext*, game::as::ActorUtil*, void*,
                              void*, s32, void*, void*, int)>(ADDR_int_4C3A40)(archive, gctx, actorUtil, cmbMan,
                                                                               /*actorResource*/ NULL, animId,
                                                                               boneMtxBuf, boneMtxBuf, 8);
  }

  void ActorUtil_Destroy(game::as::ActorUtil* actorUtil) {
    rnd::util::GetPointer<void(game::as::ActorUtil*)>(ADDR_ActorUtil_Destroy_1FD358)(actorUtil);
  }

}  // namespace game::as
