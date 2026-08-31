#include "common/advanced_context.h"
#include "common/hidstate.h"
#include "common/input.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/pad.h"
#include "game/player.h"
#include "game/states/state.h"
#include "game/ui.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"
#include "msys/include/menus/cheats.h"
#include "msys/include/menus/commands.h"
#include "msys/include/menus/save.h"
#include "msys/include/menus/watches.h"

extern "C" {
#include <3ds/svc.h>
}

namespace rnd {

  namespace {
    bool s_show_title = false;

    void Init(Context& context) {
      msys::Watches_Init();
      msys::Positions_Init();
      context.has_initialised = true;
    }
  }  // namespace

  extern "C" {

  void* __service_ptr = nullptr;

  char* fake_heap_start;
  char* fake_heap_end;
  extern void (*__init_array_start[])(void) __attribute__((weak));
  extern void (*__init_array_end[])(void) __attribute__((weak));

  void _start(void) {
    static char s_fake_heap[0x10000];

    fake_heap_start = &s_fake_heap[0];
    fake_heap_end = &s_fake_heap[sizeof(s_fake_heap)];
    for (size_t i = 0; i < size_t(__init_array_end - __init_array_start); i++) {
      __init_array_start[i]();
    }
  }
  }

  namespace {

    void toggle_advance() {
      AdvanceState& advState = GetAdvState();
      Input_Update();

      if (advState.pauseUnpause && advState.advance_ctx_t.advance_state == advState.NORMAL &&
          !advState.advance_ctx_t.d_down_latched) {
        advState.advance_ctx_t.advance_state = advState.PAUSED;
        advState.advance_ctx_t.d_down_latched = 1;
      } else if (advState.pauseUnpause && advState.advance_ctx_t.advance_state != advState.NORMAL &&
                 !advState.advance_ctx_t.d_down_latched) {
        advState.advance_ctx_t.advance_state = advState.NORMAL;
        advState.advance_ctx_t.d_down_latched = 1;
      } else if (advState.frameAdvance && advState.advance_ctx_t.advance_state == advState.NORMAL) {
        advState.advance_ctx_t.advance_state = advState.LATCHED;
      } else if (!advState.pauseUnpause) {
        advState.advance_ctx_t.d_down_latched = 0;
      }
    }

    /// Spinning here is what stops the game: calc() is its per-frame call, so
    /// not returning freezes everything. Commands stay polled so we can resume.
    void frame_advance() {
      AdvanceState& advState = GetAdvState();

      toggle_advance();
      if (advState.advance_ctx_t.advance_state == advState.STEP) {
        advState.advance_ctx_t.advance_state = advState.frameAdvance ? advState.LATCHED : advState.PAUSED;
      }

      advState.pauseUnpause = false;
      advState.frameAdvance = false;

      while (advState.advance_ctx_t.advance_state == advState.PAUSED ||
             advState.advance_ctx_t.advance_state == advState.LATCHED) {
        Input_Update();
        msys::Command_UpdateCommands(rInputCtx.cur.val);
        toggle_advance();
        if (advState.advance_ctx_t.advance_state == advState.LATCHED && !advState.frameAdvance)
          advState.advance_ctx_t.advance_state = advState.PAUSED;
        if (advState.advance_ctx_t.advance_state == advState.PAUSED && advState.frameAdvance)
          advState.advance_ctx_t.advance_state = advState.STEP;
        advState.pauseUnpause = false;
        advState.frameAdvance = false;
        // The render hook is frozen in here, so anything on the top screen has
        // to be drawn by this loop.
        Draw_DrawFormattedStringTop(20, 20, COLOR_WHITE, "PAUSED");
        Draw_FlushFramebufferTop();
        svcSleepThread(16e6);
      }
    }

  }  // namespace

  extern "C" {

  void DrawMenu() {
    Draw_SetupFramebuffer();
    if (s_show_title) {
      Draw_DrawFormattedStringTop(130, 20, COLOR_WHITE, "MM3D Practice Patch");
      Draw_FlushFramebufferTop();
    } else {
      msys::drawWatches();
      msys::Commands_DrawToast();
    }
  }

  void calc(game::State* state) {
    Context& context = GetContext();
    context.gctx = nullptr;

    if (!context.has_initialised && state->type == game::StateType::FirstGame)
      Init(context);

    s_show_title = state->type == game::StateType::FileSelect;

    if (state->type != game::StateType::Play)
      return;

    context.gctx = static_cast<game::GlobalContext*>(state);

    Input_Update();
    msys::Commands_ApplyBreakFree();
    msys::Command_UpdateCommands(rInputCtx.cur.val);
    frame_advance();

    msys::Save_ApplyPendingMomentum();
    msys::Cheats_ApplyInfiniteItems();

    if (GetAdvState().useISG) {
      if (game::act::Player* player = context.gctx->GetPlayerActor()) {
        player->sword_active_timer = 1;
        player->sword_active = 1;
      }
    }
  }

  /* Bracket the actor update, from 0x174A6C and 0x174E08. */
  void PreActorCalc() {}
  void PostActorCalc() {}

  void readPadInput() {
    auto* gctx = GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return;

    const bool zr = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZR);
    const bool start = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Start);
    const bool select = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Select);

    if (!zr && select)
      game::ui::OpenScreen(game::ui::ScreenType::Items);
    if (!zr && start && game::GetCommonData().save.inventory.collect_register.bombers_notebook)
      game::ui::OpenScreen(game::ui::ScreenType::Schedule);
    if (zr && start)
      game::ui::OpenScreen(game::ui::ScreenType::Quest);
    if (zr && select) {
      // Clear "soaring" mode or the map reopens as the owl warp selector.
      util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
      game::ui::OpenScreen(game::ui::ScreenType::Map);
      gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
      gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
    }
  }
  }

}  // namespace rnd
