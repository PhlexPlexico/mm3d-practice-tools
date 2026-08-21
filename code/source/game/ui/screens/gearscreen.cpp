#include "game/ui/screens/gearscreen.h"
#include "game/addresses.h"

namespace game::ui::screens {
  GearScreen* GetGearScreen() {
    return rnd::util::GetPointer<GearScreen>(ADDR_GetGearScreen_6F4130);
  }

}  // namespace game::ui::screens