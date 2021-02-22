#include "msys/include/draw.h"
#include "msys/include/menu.h"
#include "../game/scene.h"
#include "../game/common_data.h"
#include "../common/context.h"

#define ENTRANCE_MENU_MAX_SHOW 15
#define SCENE_MENU_MAX_SHOW 18

rst::Context warpCtx;

static void GetContext() {
  warpCtx = rst::GetContext();
}

void EntranceWarp(u16 EntranceIndex){
    GetContext();
    game::CommonData& cdata = game::GetCommonData();
    warpCtx.gctx->next_entrance = EntranceIndex;
    cdata.sub13s[8].entrance_index = EntranceIndex;
    warpCtx.gctx->field_C529_one_to_clear_input = 0x14;
}