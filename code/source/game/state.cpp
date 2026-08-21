#include "game/states/state.h"

namespace game {

  /*
   * Ask the main loop to switch game state on the next tick.
   *
   * The practice tool's copy of this lived in a state.cpp that also carried the
   * custom-game-state machinery -- an extended StateInfo table and the
   * rst_GameStateGetNextStateInfo trampoline behind the 0x1053EC hook. None of
   * that is needed to change to a state the game already knows about, so only
   * this is here; the extension comes in with the feature that needs it.
   */
  void State::ChangeState(StateType new_type) {
    status = State::Status::Changing;
    next_state_init_fn = nullptr;
    type = new_type;
  }

}  // namespace game
