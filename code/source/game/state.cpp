#include "game/states/state.h"
#include "common/utils.h"
#include "game/addresses.h"

namespace game {

  const StateInfo* FindStateInfoByType(StateType type) {
    const StateInfo* table = rnd::util::GetPointer<const StateInfo>(ADDR_sStateInfoTable_6883FC);
    for (u32 i = 0; i < 16; ++i) {
      if (table[i].init_fn == nullptr)
        break;
      if (table[i].type == type)
        return &table[i];
    }
    return nullptr;
  }

  void State::ChangeState(StateType new_type) {
    const StateInfo* info = FindStateInfoByType(new_type);
    if (!info)
      return;
    next_state_init_fn = info->init_fn;
    next_state_instance_size = info->instance_size;
    type = new_type;
    status = State::Status::Changing;
  }

}  // namespace game
