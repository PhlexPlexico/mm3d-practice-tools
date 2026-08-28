/**
 * @file context.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/context.h"
#include "game/addresses.h"

#include "common/advanced_context.h"
#include "game/player.h"
#include "game/static_context.h"
#include "z3d/z3DVec.h"

namespace game {

  act::Actor* GlobalContext::FindActorWithId(act::Id id, act::Type type) const {
    if (u8(type) >= actors.lists.size())
      return nullptr;

    act::Actor* actor = this->actors.lists[u8(type)].first;
    while (actor && actor->id != id)
      actor = actor->next;
    return actor;
  }

  act::Player* GlobalContext::GetPlayerActor() const {
    return static_cast<act::Player*>(this->actors.lists[u8(act::Type::Player)].first);
  }

  act::Actor* GlobalContext::SpawnActor(act::Actor* actor, act::Id id, u16 rx, u16 ry, u16 rz, u16 param,
                                        z3dVec3f pos) {
    auto spawn_actor_wrapper = rnd::util::GetPointer<act::Actor*(
        ActorLists*, act::Actor*, GlobalContext*, act::Id, u16, u16, u16, u16 param, z3dVec3f)>(ADDR_SpawnActor_22CAAC);
    return spawn_actor_wrapper(&actors, actor, this, id, rx, ry, rz, param, pos);
  }

  act::Actor* GlobalContext::SpawnActor(act::Id id, u16 rx, u16 ry, u16 rz, u16 param, z3dVec3f pos) {
    auto spawn_actor_wrapper =
        rnd::util::GetPointer<act::Actor*(ActorLists*, GlobalContext*, act::Id, u16, u16, u16, u16 param, z3dVec3f)>(
            ADDR_SpawnActor_22074C);
    return spawn_actor_wrapper(&actors, this, id, rx, ry, rz, param, pos);
  }

  void GlobalContext::ChangeActorType(act::Actor& actor, act::Type type) {
    actors.GetList(actor.actor_type).need_to_update_lists = true;
    actor.actor_type = type;
  }

  void GlobalContext::ShowMessage(u16 msgid, act::Actor* actor) {
    rnd::util::GetPointer<void(GlobalContext*, int msgid, act::Actor*)>(ADDR_ShowMessage_21BAFC)(this, msgid, actor);
  }

  void GlobalContext::Talk(act::Actor* actor, int a) {
    GetPlayerActor()->talk_actor = actor;
    rnd::util::GetPointer<void(GlobalContext*, act::Actor*, int)>(ADDR_Talk_2209A8)(this, actor, a);
  }

  void GlobalContext::EmitLastDamageSound(const act::Actor& actor) {
    rnd::util::GetPointer<void(GlobalContext*, const act::Actor&)>(ADDR_EmitLastDamageSound_389AC0)(this, actor);
  }

  void GlobalContext::VoidPlayer() {
    rnd::util::GetPointer<void(GlobalContext*)>(ADDR_VoidPlayer_230EC8)(this);
  }

  // Grabs the persistent cycle flags for cycle reset.
  PersistentSceneCycleFlags* GetPersistentCycleStruct() {
    return rnd::util::GetPointer<PersistentSceneCycleFlags>(ADDR_GetPersistentCycleStruct_6A017C);
  }

  void KillAllActorsWithMissingObjects(game::GlobalContext* gctx) {
    rnd::util::GetPointer<void(game::GlobalContext*, game::ActorLists*)>(ADDR_KillAllActorsWithMissingObjects_4E0974)(
        gctx, &gctx->actors);
  }

}  // namespace game
