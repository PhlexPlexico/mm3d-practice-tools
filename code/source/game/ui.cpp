/**
 * @file ui.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/ui.h"
#include "game/addresses.h"

#include <string_view>

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/context.h"
#include "game/static_context.h"
#include "game/ui/screens/screen.h"

namespace game::ui {

  ScreenContext& GetScreenContext() {
    return *rnd::util::GetPointer<ScreenContext>(ADDR_GetScreenContext_72F5BC);
  }

  Screen* GetScreen(ScreenType screen) {
    /*
     * The game keeps one Screen* per ScreenType in a contiguous table, so this
     * is an index rather than the eight-case switch it used to be. That also
     * means only the table's base address needs tracking across game versions
     * instead of all eight slots -- and the individual slots could not be
     * resolved anyway, since nothing references them directly.
     */
    static_assert(u32(ScreenType::Ocarina) == 7);
    const auto idx = u32(screen);
    if (idx > u32(ScreenType::Ocarina))
      return nullptr;
    return rnd::util::GetPointer<Screen*>(ADDR_if_656B00)[idx];
  }

  bool OpenScreen(ScreenType screen) {
    GlobalContext* gctx = rnd::GetContext().gctx;
    ScreenContext& ui_ctx = GetScreenContext();

    if (!gctx || gctx->type != StateType::Play)
      return false;

    ui_ctx.new_screen = GetScreen(screen);
    gctx->pause_flags = PauseFlag::PauseCalc;
    gctx->enable_letterbox = false;

    if (GetStaticContext().field_D38) {
      GetStaticContext().field_D38 = 0;
      gctx->field_CAB0 = 0xA0A0A000;
    }
    if (!gctx->field_CAAD)
      gctx->field_CAB0 = 0;

    if (gctx->some_fn2 && !gctx->some_fn2(&gctx->some_ptr) && gctx->some_fn1)
      gctx->some_fn1(&gctx->some_ptr, 0);

    return true;
  }

  bool CheckCurrentScreen(ScreenType screen) {
    auto& ctx = GetScreenContext();
    return ctx.active_screen == GetScreen(screen) && !ctx.new_screen;
  }

  CommonLayouts& GetCommonLayouts() {
    return *rnd::util::GetPointer<CommonLayouts>(ADDR_GetCommonLayouts_6B7B8C);
  }

}  // namespace game::ui
