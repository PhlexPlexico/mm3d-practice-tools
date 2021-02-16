#include "common/hidstate.h"

namespace rst {
AdvanceState& GetAdvState() {
    static AdvanceState s_advstate{};
    return s_advstate;
}
}  // namespace rst
