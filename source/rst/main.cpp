#include "common/context.h"
#include "common/debug.h"
#include "common/hidstate.h"
#include "common/types.h"
#include "common/utils.h"
#include "game/camera.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/pad.h"
#include "game/player.h"
#include "game/sound.h"
#include "game/states/state.h"
#include "game/ui.h"
#include "game/ui/screens/gear_screen.h"
#include "game/ui/screens/schedule_screen.h"
#include "msys/include/MyThread.h"
#include "msys/include/draw.h"
#include "msys/include/menu.h"
#include "msys/include/menus/commands.h"

namespace rst {

advance_input_t inputs = {};
bool frameBufferInit = true;
bool showTitle = true;
AdvanceState& advState = GetAdvState();

namespace {

void Init(Context& context) {
  // link::Init();

  util::Print("Project Restoration initialised (" __DATE__ " " __TIME__ ")");
  game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_QUEST_CLEAR);
  context.has_initialised = true;
}

}  // anonymous namespace

[[maybe_unused]] static void PrintDebug(game::GlobalContext* gctx) {
  std::string actors_str = "actors:";
  for (size_t i = 0; i < gctx->actors.lists.size(); ++i) {
    game::ActorList& list = gctx->actors.lists[i];
    actors_str += util::StringFromFormat("\ntype %02zu: ", i);
    for (auto* actor = list.first; actor; actor = actor->next) {
      actors_str += util::StringFromFormat("%04x[%04x] ", u16(actor->id), actor->params);
    }
  }
  util::Print(actors_str);

  const auto* player = gctx->GetPlayerActor();
  if (player) {
    util::Print("%08lx %08lx %08lx %08lx %08x", player->flags1.flags, player->flags2.flags,
                player->flags3.flags, player->flags4, player->flags_94.flags);

    util::Print("state handler: %p - 92C: %u - 92D: %u", player->state_handler_fn, player->fn1_idx,
                player->fn2_idx);

    auto* camera = &gctx->main_camera + gctx->camera_idx;
    util::Print("camera_idx=%u target=%p%s state=%04x mode=%04x", gctx->camera_idx,
                camera->target_actor,
                (camera->target_actor && camera->target_actor == player) ? "(player)" : "",
                u16(camera->state), u16(camera->mode));
  }
}

static bool IsStartOrSelectPressed() {
  return GetContext().gctx && GetContext().gctx->pad_state.input.new_buttons.IsOneSet(
                                  game::pad::Button::Start, game::pad::Button::Select);
}

static void UiOcarinaScreenUpdate() {
  if (!game::ui::CheckCurrentScreen(game::ui::ScreenType::Ocarina))
    return;
  auto* screen = game::ui::GetScreen(game::ui::ScreenType::Ocarina);

  if (IsStartOrSelectPressed()) {
    util::Write<bool>(screen, 0x41, true);  // is transitioning
    auto* layout_ocarina = util::BitCastPtr<game::ui::Layout*>(screen, 0x10);
    auto* layout_music_list = util::BitCastPtr<game::ui::Layout*>(screen, 0x14);
    const bool is_menu_ocarina = util::BitCastPtr<bool>(screen, 0x40);
    if (is_menu_ocarina)
      util::GetPointer<void(void*)>(0x5F54DC)(layout_ocarina);
    else
      util::GetPointer<void(void*)>(0x5F7DC8)(layout_music_list);
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_DECIDE);
  }
}

void scan_shared_hid_inputs() {
  inputs.cur.val = shared_hid->pad.pads[shared_hid->pad.index].curr.val;
  inputs.pressed.val = (inputs.cur.val) & (~inputs.old.val);
  inputs.up.val = (~inputs.cur.val) & (inputs.old.val);
  inputs.old.val = inputs.cur.val;
}

static void toggle_advance() {
  scan_shared_hid_inputs();

  // util::Print("%s: %d pressed is pressed and we are NOT normal. UNPAUSING", __func__,
  // inputs.cur.val);
  if (advState.pauseUnpause && advState.advance_ctx_t.advance_state == advState.NORMAL &&
      !advState.advance_ctx_t.d_down_latched) {
    // util::Print("%s: Down is pressed and we are normal. Pausing", __func__);
    advState.advance_ctx_t.advance_state = advState.PAUSED;
    advState.advance_ctx_t.d_down_latched = 1;
  } else if (advState.pauseUnpause && advState.advance_ctx_t.advance_state != advState.NORMAL &&
             !advState.advance_ctx_t.d_down_latched) {
    // util::Print("%s: Down is pressed and we are NOT normal. UNPAUSING", __func__);
    advState.advance_ctx_t.advance_state = advState.NORMAL;
    advState.advance_ctx_t.d_down_latched = 1;
  } else if (advState.frameAdvance && advState.advance_ctx_t.advance_state == advState.NORMAL) {
    // util::Print("%s: RIGHT is pressed and we are normal. LATCHING?", __func__);
    advState.advance_ctx_t.advance_state = advState.LATCHED;
  } else if (!advState.pauseUnpause) {
    advState.advance_ctx_t.d_down_latched = 0;
  }
}

static void frame_advance() {
  // Check to advance
  toggle_advance();
  if (advState.advance_ctx_t.advance_state == advState.STEP) {
    if (advState.frameAdvance) {
      advState.advance_ctx_t.advance_state = advState.LATCHED;
      util::Print("%s: We are now latched!", __func__);
    } else {
      advState.advance_ctx_t.advance_state = advState.PAUSED;
    }
  }

  advState.pauseUnpause = false;
  advState.frameAdvance = false;

  while (advState.advance_ctx_t.advance_state == advState.PAUSED ||
         advState.advance_ctx_t.advance_state == advState.LATCHED) {
    scan_shared_hid_inputs();
    Command_UpdateCommands(inputs.cur.val);
    toggle_advance();
    if (advState.advance_ctx_t.advance_state == advState.LATCHED && !advState.frameAdvance) {
      util::Print("%s: We are now paused! Our state? %d", __func__,
                  advState.advance_ctx_t.advance_state);
      advState.advance_ctx_t.advance_state = advState.PAUSED;
    }
    if (advState.advance_ctx_t.advance_state == advState.PAUSED && advState.frameAdvance) {
      advState.advance_ctx_t.advance_state = advState.STEP;
    }
    advState.pauseUnpause = false;
    advState.frameAdvance = false;
    svcSleepThread(16e6);
  }
}

static void freeze_unfreeze_time() {
  auto* gctx = GetContext().gctx;
  if (!gctx || gctx->type != game::StateType::Play)
    return;
  game::CommonData& cdata = game::GetCommonData();
  if (advState.timeFreeze && cdata.save.extra_time_speed != -2) {
    cdata.save.extra_time_speed = -2;
  } else if (!advState.timeFreeze && cdata.save.extra_time_speed == -2) {
    cdata.save.extra_time_speed = 0;
  }
}

static void daychanger() {
  auto* gctx = GetContext().gctx;
  if (!gctx || gctx->type != game::StateType::Play)
    return;

  const bool zl = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZL);
  const bool dpleft = gctx->pad_state.input.buttons.IsSet(game::pad::Button::Left);
  const bool dpright = gctx->pad_state.input.buttons.IsSet(game::pad::Button::Right);
  game::CommonData& cdata = game::GetCommonData();

  // Advance day, if max days, loop back to 1.
  if (zl && dpright) {
    if (cdata.save.day <= cdata.save.total_day + 1) {
      cdata.save.day++;
      return;
    } else {
      cdata.save.day = 0;
    }
  }
  // Advance day, if max days, loop back to 1.
  if (zl && dpleft) {
    if (cdata.save.day >= -1) {
      util::Print("%s: Total days are %d, current day is %d", __func__, cdata.save.total_day,
                  cdata.save.day);
      cdata.save.day--;
      return;
    } else {
      cdata.save.day = 0;
    }
  }
}

// Main entry hook in game loop.
RST_HOOK void Calc(game::State* state) {
  Context& context = GetContext();
  context.gctx = nullptr;

  if (!context.has_initialised && state->type == game::StateType::FirstGame)
    Init(context);
  if (state->type == game::StateType::FileSelect)
    showTitle = true;
  else
    showTitle = false;
  if (state->type != game::StateType::Play)
    return;
  //
  context.gctx = static_cast<game::GlobalContext*>(state);
  game::CommonData& cdata = game::GetCommonData();

  // Move in improvements from Project Restoration
  UiOcarinaScreenUpdate();
  // End improvments.
  scan_shared_hid_inputs();
  Command_UpdateCommands(inputs.cur.val);
  // Begin routines for MM3D Practice Patches.
  frame_advance();
  freeze_unfreeze_time();
  // daychanger();
  // store_pos();
  // End routines.
}

RST_HOOK void DrawMenu() {
  if (frameBufferInit) {
    Draw_SetupFramebuffer();
    frameBufferInit = false;
  }
  if (showTitle) {
    Draw_DrawFormattedStringTop(150, 20, COLOR_WHITE, "MM3D Practice Patch");
    Draw_FlushFramebufferTop();
  }
}

RST_HOOK void PreActorCalcHook() {
  // FixOwlStatueActivationTrigger();
}

// RST_HOOK void PostActorCalcHook() {
//   //FixBosses();
// }

// This opens menu based on what buttons are pressed.
RST_HOOK void UiScheduleTriggerHook() {
  auto* gctx = GetContext().gctx;
  if (!gctx || gctx->type != game::StateType::Play)
    return;

  const bool zr = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZR);
  const bool start = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Start);
  const bool select = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Select);
  if (!zr && select)
    game::ui::OpenScreen(game::ui::ScreenType::Items);
  if (!zr && start && game::GetCommonData().save.inventory.collect_register & 0x40000)
    game::ui::OpenScreen(game::ui::ScreenType::Schedule);
  if (zr && start)
    game::ui::OpenScreen(game::ui::ScreenType::Quest);
  if (zr && select) {
    // Clear map screen type. (Needed because the screen could be in "soaring" mode.)
    util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
    game::ui::OpenScreen(game::ui::ScreenType::Map);
    gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
    gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
  }
}

}  // namespace rst

extern "C" {
extern char* fake_heap_start;
extern char* fake_heap_end;
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));

RST_HOOK void _start(void) {
  // Just in case something needs to be dynamically allocated...
  static char s_fake_heap[0x80000];
  fake_heap_start = &s_fake_heap[0];
  fake_heap_end = &s_fake_heap[sizeof(s_fake_heap)];

  for (size_t i = 0; i < size_t(__init_array_end - __init_array_start); i++)
    __init_array_start[i]();
}
}
