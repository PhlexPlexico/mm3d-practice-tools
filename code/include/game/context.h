/**
 * @file context.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#pragma once

#include <cstddef>

#include "common/types.h"
#include "common/utils.h"
#include "game/actor.h"
#include "game/actorresource.h"
#include "game/camera.h"
#include "game/objectbankarchive.h"
#include "game/pad.h"
#include "game/resarchiveheader.h"
#include "game/scene.h"
#include "game/states/state.h"
#include "game/ui/screens/screen.h"
#include "z3d/z3DVec.h"

namespace game {

  namespace act {
    class BossTwinmold;
    class ObjElegyStatue;
    class Player;
  }  // namespace act

  namespace ui {
    class PlayHud;
  }

  enum class PauseFlag : u16 {
    PauseCalc = 1 << 0,
    PauseDraw = 1 << 1,
    PauseAll = PauseCalc | PauseDraw,
  };

  // Keeps track of spawned actors.
  struct ActorList {
    u32 num_actors;
    act::Actor* first;
    /// Set this after changing an actor's type to update the linked lists.
    bool need_to_update_lists;
  };
  static_assert(sizeof(ActorList) == 0xc);

  struct ActorContextSceneFlags {
    u32 switches[4];  // First 0x40 are permanent, second 0x40 are temporary
    u32 chest;
    u32 clearedRoom;
    u32 clearedRoomTemp;
    u32 collectible[4];  // bitfield of 128 bits
  };
  static_assert(sizeof(ActorContextSceneFlags) == 0x2C);

  struct PlayerImpact {
    u8 timer;
    u8 type;
    float dist;
    z3dVec3f pos;
  };
  static_assert(sizeof(PlayerImpact) == 0x14);

  struct TitleCardContext {
    void* texturePtr;
    s16 x;
    s16 y;
    u8 width;
    u8 height;
    u8 durationTimer;
    u8 delayTimer;
    u8 alpha;
    u8 intensity;
    u16 field_e;
    u16 field_10;
  };
  static_assert(sizeof(TitleCardContext) == 0x14);

  struct ActorLists {
    ActorList& GetList(act::Type type) { return lists[u8(type)]; }
    const ActorList& GetList(act::Type type) const { return lists[u8(type)]; }
    u8 freeze_flash_timer;
    u8 pad1;
    u8 field_2;
    u8 lens_active;
    u8 lens_mask_size;
    u8 flag;
    u8 gap_6[6];
    u8 num_actors;
    std::array<ActorList, 12> lists;
    u8 gap_2150[128];
    z3dVec3f field_21D0;
    u8 gap_21DC[280];
    ActorContextSceneFlags actor_ctx_scene_flags;
    TitleCardContext title_card_ctx;
    PlayerImpact player_impact;
    u8 gap_2348[72];
    void* absolute_space;
    std::array<act::ObjElegyStatue*, 5> elegy_statues;
    char field_23A8;
    u8 gap_23A9[3];
    pad::State pad_state_copy;
    u8 gap_2418[12];
  };
  static_assert(sizeof(ActorLists) == 0x374);
  static_assert(offsetof(ActorLists, gap_6) == 0x06);

  enum class OcarinaMode : u16 {
    OCARINA_MODE_NONE = 0,
    OCARINA_MODE_ACTIVE = 1,
    OCARINA_MODE_WARP = 2,
    OCARINA_MODE_EVENT = 3,
    OCARINA_MODE_END = 4,
    OCARINA_MODE_PLAYED_TIME = 5,
    OCARINA_MODE_PLAYED_HEALING = 6,
    OCARINA_MODE_PLAYED_EPONAS = 7,
    OCARINA_MODE_PLAYED_SOARING = 8,
    OCARINA_MODE_PLAYED_STORMS = 9,
    OCARINA_MODE_PLAYED_SUNS = 10,
    OCARINA_MODE_PLAYED_INVERTED_TIME = 11,
    OCARINA_MODE_PLAYED_DOUBLE_TIME = 12,
    OCARINA_MODE_PLAYED_SCARECROW_SPAWN = 13,
    OCARINA_MODE_E = 14,
    OCARINA_MODE_F = 15,
    OCARINA_MODE_10 = 16,
    OCARINA_MODE_11 = 17,
    OCARINA_MODE_PROCESS_SOT = 18,
    OCARINA_MODE_PROCESS_INVERTED_TIME = 19,
    OCARINA_MODE_14 = 20,
    OCARINA_MODE_PROCESS_DOUBLE_TIME = 21,
    OCARINA_MODE_APPLY_SOT = 22,
    OCARINA_MODE_17 = 23,
    OCARINA_MODE_APPLY_INV_SOT_FAST = 24,
    OCARINA_MODE_APPLY_INV_SOT_SLOW = 25,
    OCARINA_MODE_APPLY_DOUBLE_SOT = 26,
    OCARINA_MODE_1B = 27,
    OCARINA_MODE_WARP_TO_GREAT_BAY_COAST = 28,
    OCARINA_MODE_WARP_TO_ZORA_CAPE = 29,
    OCARINA_MODE_WARP_TO_SNOWHEAD = 30,
    OCARINA_MODE_WARP_TO_MOUNTAIN_VILLAGE = 31,
    OCARINA_MODE_WARP_TO_SOUTH_CLOCK_TOWN = 32,
    OCARINA_MODE_WARP_TO_MILK_ROAD = 33,
    OCARINA_MODE_WARP_TO_WOODFALL = 34,
    OCARINA_MODE_WARP_TO_SOUTHERN_SWAMP = 35,
    OCARINA_MODE_WARP_TO_IKANA_CANYON = 36,
    OCARINA_MODE_WARP_TO_STONE_TOWER = 37,
    OCARINA_MODE_WARP_TO_ENTRANCE = 38,
    OCARINA_MODE_PROCESS_RESTRICTED_SONG = 39,
    OCARINA_MODE_28 = 40,
    OCARINA_MODE_29 = 41,
    OCARINA_MODE_PLAYED_FULL_EVAN_SONG = 42
  };

  enum class OcarinaSongActionId : u16 {
    OCARINA_ACTION_0 = 0,
    OCARINA_ACTION_FREE_PLAY = 1,
    OCARINA_ACTION_DEMONSTRATE_SONATA = 2,
    OCARINA_ACTION_DEMONSTRATE_GORON_LULLABY = 3,
    OCARINA_ACTION_DEMONSTRATE_NEW_WAVE = 4,
    OCARINA_ACTION_DEMONSTRATE_ELEGY = 5,
    OCARINA_ACTION_DEMONSTRATE_OATH = 6,
    OCARINA_ACTION_DEMONSTRATE_SARIAS = 7,
    OCARINA_ACTION_DEMONSTRATE_TIME = 8,
    OCARINA_ACTION_DEMONSTRATE_HEALING = 9,
    OCARINA_ACTION_DEMONSTRATE_EPONAS = 10,
    OCARINA_ACTION_DEMONSTRATE_SOARING = 11,
    OCARINA_ACTION_DEMONSTRATE_STORMS = 12,
    OCARINA_ACTION_DEMONSTRATE_SUNS = 13,
    OCARINA_ACTION_DEMONSTRATE_INVERTED_TIME = 14,
    OCARINA_ACTION_DEMONSTRATE_DOUBLE_TIME = 15,
    OCARINA_ACTION_DEMONSTRATE_GORON_LULLABY_INTRO = 16,
    OCARINA_ACTION_11 = 17,
    OCARINA_ACTION_PROMPT_SONATA = 18,
    OCARINA_ACTION_PROMPT_GORON_LULLABY = 19,
    OCARINA_ACTION_PROMPT_NEW_WAVE = 20,
    OCARINA_ACTION_PROMPT_ELEGY = 21,
    OCARINA_ACTION_PROMPT_OATH = 22,
    OCARINA_ACTION_PROMPT_SARIAS = 23,
    OCARINA_ACTION_PROMPT_TIME = 24,
    OCARINA_ACTION_PROMPT_HEALING = 25,
    OCARINA_ACTION_PROMPT_EPONAS = 26,
    OCARINA_ACTION_PROMPT_SOARING = 27,
    OCARINA_ACTION_PROMPT_STORMS = 28,
    OCARINA_ACTION_PROMPT_SUNS = 29,
    OCARINA_ACTION_PROMPT_INVERTED_TIME = 30,
    OCARINA_ACTION_PROMPT_DOUBLE_TIME = 31,
    OCARINA_ACTION_PROMPT_GORON_LULLABY_INTRO = 32,
    OCARINA_ACTION_21 = 33,
    OCARINA_ACTION_CHECK_SONATA = 34,
    OCARINA_ACTION_CHECK_GORON_LULLABY = 35,
    OCARINA_ACTION_CHECK_NEW_WAVE = 36,
    OCARINA_ACTION_CHECK_ELEGY = 37,
    OCARINA_ACTION_CHECK_OATH = 38,
    OCARINA_ACTION_CHECK_SARIAS = 39,
    OCARINA_ACTION_CHECK_TIME = 40,
    OCARINA_ACTION_CHECK_HEALING = 41,
    OCARINA_ACTION_CHECK_EPONAS = 42,
    OCARINA_ACTION_CHECK_SOARING = 43,
    OCARINA_ACTION_CHECK_STORMS = 44,
    OCARINA_ACTION_CHECK_SUNS = 45,
    OCARINA_ACTION_CHECK_INVERTED_TIME = 46,
    OCARINA_ACTION_CHECK_DOUBLE_TIME = 47,
    OCARINA_ACTION_CHECK_GORON_LULLABY_INTRO = 48,
    OCARINA_ACTION_CHECK_SCARECROW_SPAWN = 49,
    OCARINA_ACTION_FREE_PLAY_DONE = 50,
    OCARINA_ACTION_SCARECROW_LONG_RECORDING = 51,
    OCARINA_ACTION_SCARECROW_LONG_DEMONSTRATION = 52,
    OCARINA_ACTION_SCARECROW_SPAWN_RECORDING = 53,
    OCARINA_ACTION_SCARECROW_SPAWN_DEMONSTRATION = 54,
    OCARINA_ACTION_37 = 55,
    OCARINA_ACTION_CHECK_NOTIME = 56,
    OCARINA_ACTION_CHECK_NOTIME_DONE = 57,
    OCARINA_ACTION_3A = 58,
    OCARINA_ACTION_3B = 59,
    OCARINA_ACTION_3C = 60,
    OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_FIRST_HALF = 61,
    OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_FIRST_HALF = 62,
    OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_SECOND_HALF = 63,
    OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_SECOND_HALF = 64,
    OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF = 65,
    OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF = 66,
    OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN = 67,
    OCARINA_ACTION_PROMPT_WIND_FISH_GORON = 68,
    OCARINA_ACTION_PROMPT_WIND_FISH_ZORA = 69,
    OCARINA_ACTION_PROMPT_WIND_FISH_DEKU = 70,
    OCARINA_ACTION_TIMED_PROMPT_SONATA = 71,
    OCARINA_ACTION_TIMED_PROMPT_GORON_LULLABY = 72,
    OCARINA_ACTION_TIMED_PROMPT_NEW_WAVE = 73,
    OCARINA_ACTION_TIMED_PROMPT_ELEGY = 74,
    OCARINA_ACTION_TIMED_PROMPT_OATH = 75,
    OCARINA_ACTION_TIMED_PROMPT_SARIAS = 76,
    OCARINA_ACTION_TIMED_PROMPT_TIME = 77,
    OCARINA_ACTION_TIMED_PROMPT_HEALING = 78,
    OCARINA_ACTION_TIMED_PROMPT_EPONAS = 79,
    OCARINA_ACTION_TIMED_PROMPT_SOARING = 80,
    OCARINA_ACTION_TIMED_PROMPT_STORMS = 81
  };

  enum class OcarinaSong : u16 {
    SonataOfAwakening = 0,
    GoronLullaby = 1,
    NewWaveBossaNova = 2,
    ElegyOfEmptiness = 3,
    OathToOrder = 4,
    SongOfTime = 6,
    SongOfHealing = 7,
    EponaSong = 8,
    SongOfSoaring = 9,
    SongOfStorms = 10,
    SunsSong = 11,
    InvertedSongOfTime = 12,
    SongOfDoubleTime = 13,
    GoronLullablyIntro = 14,
    WindFishHuman = 15,
    WindFishGoron = 16,
    WindFishZora = 17,
    WindFishDeku = 18,
    EvansSongPart1 = 19,
    EvansSongPart2 = 20,
    ZeldasLullaby = 21,
    ScarecrowSong = 22,
    TerminaWallSong = 23,
    SongMax = 24,

    InvalidDetecting = 0xfe,
    Invalid = 0xff,
  };

  struct OcarinaStaff {
    u8 buttonIndex;
    u8 song;
    u8 pos;
  };

  struct HudState {
    u32 field_0;
    u8 gap_4[86];
    u16 field_5A;
    u8 gap_5C[380];
    u32 field_1D8;
    u8 gap_1DC[36];
    u32 field_200;
    u8 gap_204[28];
    u16 field_220;
    s16 a_btn_num;
    s16 field_224;
    u8 gap_226[2];
    float field_228;
    u8 gap_22C[4];
    u16 field_230;
    u8 gap_232[10];
    s16 field_23C;
    u8 num_carrots;
    u8 gap_23F[5];
    u16 field_244;
    u16 field_246;
    u16 field_248;

    // From 0 (invisible) to 0xFF (fully visible).
    u16 a_btn_opacity;
    u16 b_btn_opacity;
    u16 item_btn_opacity[5];
    u16 camera_opacity;
    u16 field_25A;

    u8 gap_25C[6];
    u16 field_262;
    u16 field_264;
    char field_266;
    char field_267;
    u16 field_268;
    u8 gap_26A[2];
    char field_26C;
    char field_26D;
    u16 needLoadPerfectLayout;
    u8 field_270;
    u8 field_271;
    u8 field_272;
    bool prohibit_gear_or_bottles;
    int field_274;
    u8 field_278;
    bool prohibit_masks;
    bool prohibit_ocarina;
    bool prohibit_regular_items;
    u8 field_27C;
  };
  static_assert(sizeof(HudState) == 0x280);

  struct MessageContext {
    void* notebook_stuff;
    u8 gap_8024[536];
    OcarinaStaff* ocarinaStaff_maybe;
    u16 current_text_id;
    u8 gap_8222[10];
    int field_822C;
    u16 field_8230;
    u16 field_8232;
    u8 gap_8234[10];
    u8 msg_mode;
    u8 field_823F;
    u8 gap_8240[160];
    u32 field_82E0;
    u8 gap_82E4[28];
    int field_8300;
    u8 gap_8304[28];
    int field_8320;
    u8 gap_8324[27];
    u8 text_delay_timer;
    s16 state_timer;
    u8 gap_8343[4];
    OcarinaMode ocarinaMode;
    OcarinaSongActionId ocarinaSongActionId;
    OcarinaSong lastPlayedSong;
    u8 gap_834A[16];
    game::act::Actor* talk_actor;
    u16 field_8360;
    u16 field_8362;
    OcarinaSong ocarina_song2;
    OcarinaMode ocarina_state;
    OcarinaMode ocarina_state2;
    OcarinaSong ocarina_song;
    u16 field_836C;
    u8 field_836E;
    u8 field_836F;
    int field_8370;
    int field_8374;
    int field_8378;
    game::act::Actor* message_actor;
    u16 field_8380;
    u16 field_8382;
    u8 gap_8384[4]; /* ocaEff Spawned here? */
    int item_cost;
    int item_cost_two;
    u8 gap_8390[61];
    u8 bombers_notebook_event_queue_count;
    u8 gap_83CE[58];
  };
  static_assert(offsetof(MessageContext, field_8232) == 0x232);
  static_assert(offsetof(MessageContext, ocarinaStaff_maybe) == 0x21c);
  static_assert(offsetof(MessageContext, gap_8324) == 0x324);
  static_assert(sizeof(MessageContext) == 0x408);

  // Likely incomplete.
  struct GlobalContext : State {
    bool IsPaused() const { return pause_flags.IsOneSet(PauseFlag::PauseCalc, PauseFlag::PauseDraw); }

    act::Actor* FindActorWithId(act::Id id, act::Type type) const;
    template <typename T>
    T* FindActorWithId(act::Id id, act::Type type) const {
      return static_cast<T*>(FindActorWithId(id, type));
    }
    bool IsActorVisible(act::Id id, act::Type type) const {
      const auto* actor = FindActorWithId(id, type);
      return actor && actor->draw_fn;
    }

    act::Player* GetPlayerActor() const;

    act::Actor* SpawnActor(act::Actor* actor, act::Id id, u16 rx, u16 ry, u16 rz, u16 param, z3dVec3f pos);
    act::Actor* SpawnActor(act::Id id, u16 rx, u16 ry, u16 rz, u16 param, z3dVec3f pos);
    void ChangeActorType(act::Actor& actor, act::Type type);

    void ShowMessage(u16 msgid, act::Actor* = 0x0);
    void Talk(act::Actor* actor, int a = 0);

    void EmitLastDamageSound(const act::Actor& actor);

    void VoidPlayer();

    SceneId scene;
    u16 field_14A;
    // u8 gap_14C[200];
    u8 gap_14C[8];
    u32 zsi;
    ResArchiveHeader* scene_gar;
    game::ObjectBank::ObjectBankArchive scene_archive;
    u32 field_1F8;
    u8 gap_1FC[20];
    float field_210;
    float field_214;
    float field_218;
    float field_21C;
    u8 gap_220[132];
    float field_2A4;
    u8 gap_2A8[228];
    u8 field_38C;
    u8 gap_38D[71];
    z3d_nn_math_MTX34 some_global_mtx;
    u8 gap_404[4];
    Camera main_camera;
    Camera other_cameras[3];
    Camera* cameras[4];
    u16 new_camera_idx;
    u16 camera_idx;
    u8 gap_A7C[12];
    u32 field_A88;
    u8 gap_A8C[32];
    rnd::Flags<PauseFlag> pause_flags;
    u32 field_AB0;
    u8 gap_AB4[76];
    int field_B00;
    u8 gap_B04[5372];
    u32 field_2000;
    u8 gap_2004[172];
    ActorLists actors;
    /*u8 gap_2150[128];
    z3dVec3f field_21D0;
    u8 gap_21DC[280];
    ActorContextSceneFlags actor_ctx_scene_flags;
    TitleCardContext title_card_ctx;
    PlayerImpact player_impact;
    u8 gap_2348[72];
    void* absolute_space;
    std::array<act::ObjElegyStatue*, 5> elegy_statues;
    char field_23A8;
    u8 gap_23A9[3];
    pad::State pad_state_copy;
    u8 gap_2418[12];*/
    int field_2424;
    u32 field_2428;
    u8 gap_242C[604];
    u32 field_2688;
    u8 field_268C;
    // u8 gap_268D[5999];
    // u8 gap_268D[5490];
    u8 gap_268D[4169];
    u8 field_36D6;
    u8 gap_36D7[1321];
    game::SaveFile save_file;
    // u8 gap_3BFE[18];
    // int field_3C10;
    u8 gap_3C14[488];
    u16 field_3DFC;
    u8 gap_3DFE[16898];
    u32 field_8000;
    u8 gap_8004[28];
    MessageContext msg_context;
    HudState hud_state;
    u8 gap_86A8[4];
    u16 field_86AC;
    u8 gap_86B0[272];
    u32 field_87C0;
    u8 gap_87C4[59];
    u8 field_87FF;
    u8 gap_8800[58];
    u8 field_883A;
    __attribute__((aligned(2))) u8 gap_883C[2];
    u8 field_883E;
    __attribute__((aligned(2))) u8 gap_8840[3060];
    game::ActorResource::ActorResources* actors_spawn_stuff;
    game::ActorResource::ObjectContext object_context;
    u8 gap_AC6C[5012];
    u32 field_C000;
    u8 gap_C004[604];
    u8 room_number;
    char field_C261;
    char field_C262;
    char field_C263;
    u8 gap_C264[88];
    u16 field_C2BC;
    u8 gap_C2BE[355];
    __attribute__((packed)) __attribute__((aligned(1))) u32 field_C421;
    u8 gap_C425[7];
    void (*player_init)(act::Player*, GlobalContext*, int);
    void (*player_update)(act::Player*, GlobalContext*, pad::State*, pad::TouchscreenState*);
    void (*player_switch_to_held_state_0)(GlobalContext*, act::Player*);
    void (*player_use_fishing_rod)(GlobalContext*);
    bool (*player_switch_to_held_state)(GlobalContext*, act::Player*, bool is_gyorg);
    void* player_fn_x4;
    void* player_switch_to_still;
    void* player_fn_x5;
    void* player_talk;
    void* player_fn_x6;
    void* player_fn_x7;
    void* player_fn_x8;
    void* player_fn_x9;
    // u8 gap_C460[0x68];
    u32 field_C460;
    s8 field_c462;
    u8 gap_C464[0x63];
    char field_C4C8[4];
    u16 field_C4CC;
    u8 gap_C4CE[46];
    u32 field_C4FC;
    u8 gap_C500[40];
    u8 field_C528;
    // Void flag.
    u8 field_C529_one_to_clear_input;
    u8 gap_C52A[4];
    u16 next_entrance;
    u8 field_C530;
    u8 field_C531;
    u8 field_C532;
    // u8 gap_C533[5];
    u8 gap_C533;
    u8 transitionType;
    u8 field_C535;
    u16 field_C536;
    int field_C538;
    u8 gap_C53C[798];
    u8 field_C85A;
    u8 gap_C85B[5];
    void* some_ptr;
    u8 gap_C864[572];
    void (*some_fn1)(void*, u32);
    u32 field_CAA4;
    bool (*some_fn2)(void*);
    u8 gap_CAAC;
    u8 field_CAAD;
    u8 gap_CAAE[2];
    u32 field_CAB0;
    u32 field_CAB4;
    u8 gap_CAB8[4];
    u32 field_CABC;
    SceneInfo* scene_info;
    u32 field_CAC4;
    u8 gap_CAC8[480];
    char setup2;
    char field_CCA9;
    char field_CCAA;
    char field_CCAB;

    /// If true, causes black borders (if configured) to be drawn on the top screen.
    /// This is used to implement the letterbox effect when targeting and during some cutscenes.
    bool enable_letterbox;

    /// Opacity of the dimming overlay for the bottom screen.
    /// This is automatically updated every frame depending on flags (see below).
    ///
    /// If this value is > 0.001 and dim_overlay_alpha == dim_heart_overlay_alpha, a
    /// semi-transparent rectangle is drawn over the entire bottom screen. Otherwise, if this value
    /// is only > 0.001, several rectangles are drawn over the screen to dim everything except the
    /// heart status widget.
    float dim_overlay_alpha;

    /// Opacity of the dimming overlay for the heart status widget on the bottom screen.
    /// This is automatically updated every frame depending on flags (see below).
    float dim_heart_overlay_alpha;

    /// Non-zero if the heart status widget should be undimmed. Typically set to 211 when non-zero.
    u8 undim_heart_status;
    /// Whether the bottom screen should be undimmed.
    u8 undim_bottom_screen;

    u8 gap_CCBC[4];
    u32 field_CCC0;
    ui::PlayHud* play_hud;
    u8 gap_CCC8[134];
    u8 has_kafei;
    u8 gap_CD4F[9];
    u16 field_CD58;
    u8 gap_CD5A[46];
    u32 transition_plane;
    u8 gap_CD8C[52];
    u32 field_CDC0;
    u8 gap_CDC4[60];
    u32 field_CE00;
    u8 gap_CE04[180];
    u32 field_CEB8;
    u8 gap_CEBC[8260];
    u16 field_EF00;
    u8 gap_EF02[251];
    u8 field_EFFD;
    u16 field_EFFE;
    u32 odolwa;
    u32 moths;
    z3dVec3f odolwa_position;
    u8 gap_14[64];
    u32 field_54;
    u8 gap_58[8];
    u32 field_60;
    u8 gap_64[114];
    u8 field_F0D6;
    u8 gap_F0D7;
    float field_F0D8;
    act::BossTwinmold* twinmold_actor;
    act::BossTwinmold* twinmold_2_actor;
    act::Actor* boss_actor_maybe;
    u8 gap_F0E8[4];
    act::Actor* blue_warp_actor;
    act::Player* self;
    u8 gap_F0F4[3852];
    u32 field_10000;
    u8 gap_10004[4075];
    u8 field_10FEF;
    u8 field_10FF0;
    u8 field_10FF1;
    u8 field_10FF2;
    u8 field_10FF3;
    u8 gap_10FF4[20];
    u32 field_11008;
    u8 gap_1100C[4];
    game::ui::ScreenCaptureContext screen_capture;
  };
  static_assert(offsetof(GlobalContext, main_camera) == 0x408);
  static_assert(offsetof(GlobalContext, pause_flags) == 0xAAC);
  static_assert(offsetof(GlobalContext, actors.elegy_statues) == 0x2394);
  static_assert(offsetof(GlobalContext, actors.gap_2348) == 0x2348);
  static_assert(offsetof(GlobalContext, field_C000) == 0xc000);
  static_assert(offsetof(GlobalContext, field_C4C8) == 0xC4C8);
  static_assert(offsetof(GlobalContext, gap_AC6C) == 0xAC6C);
  static_assert(offsetof(GlobalContext, msg_context) == 0x8020);
  static_assert(offsetof(GlobalContext, msg_context.ocarinaMode) == 0x8366);
  static_assert(offsetof(GlobalContext, gap_404) == 0x0404);
  static_assert(offsetof(GlobalContext, object_context) == 0x9438);
  static_assert(offsetof(GlobalContext, transitionType) == 0xC534);
  static_assert(offsetof(GlobalContext, field_C538) == 0xC538);
  static_assert(sizeof(GlobalContext) == 0x11030);

  struct PersistentSceneCycleFlags {
    union switches0 {
      u32 raw;

      BitField<0, 1, u32> unk0;
      BitField<1, 1, u32> unk1;
      BitField<2, 1, u32> unk2;
      BitField<3, 1, u32> unk3;
      BitField<4, 1, u32> unk4;
      BitField<5, 1, u32> unk5;
      BitField<6, 1, u32> unk6;
      BitField<7, 1, u32> unk7;
      BitField<8, 1, u32> unk8;
      BitField<9, 1, u32> unk9;
      BitField<10, 1, u32> unk10;
      BitField<11, 1, u32> unk11;
      BitField<12, 1, u32> unk12;
      BitField<13, 1, u32> unk13;
      BitField<14, 1, u32> unk14;
      BitField<15, 1, u32> unk15;
      BitField<16, 1, u32> unk16;
      BitField<17, 1, u32> unk17;
      BitField<18, 1, u32> unk18;
      BitField<19, 1, u32> unk19;
      BitField<20, 1, u32> unk20;
      BitField<21, 1, u32> unk21;
      BitField<22, 1, u32> unk22;
      BitField<23, 1, u32> unk23;
      BitField<24, 1, u32> unk24;
      BitField<25, 1, u32> unk25;
      BitField<26, 1, u32> unk26;
      BitField<27, 1, u32> unk27;
      BitField<28, 1, u32> unk28;
      BitField<29, 1, u32> unk29;
      BitField<30, 1, u32> unk30;
      BitField<31, 1, u32> unk31;
    };
    switches0 switch0;
    union switches1 {
      u32 raw;

      BitField<0, 1, u32> unk0;
      BitField<1, 1, u32> unk1;
      BitField<2, 1, u32> unk2;
      BitField<3, 1, u32> unk3;
      BitField<4, 1, u32> unk4;
      BitField<5, 1, u32> unk5;
      BitField<6, 1, u32> unk6;
      BitField<7, 1, u32> unk7;
      BitField<8, 1, u32> unk8;
      BitField<9, 1, u32> unk9;
      BitField<10, 1, u32> unk10;
      BitField<11, 1, u32> unk11;
      BitField<12, 1, u32> unk12;
      BitField<13, 1, u32> unk13;
      BitField<14, 1, u32> unk14;
      BitField<15, 1, u32> unk15;
      BitField<16, 1, u32> unk16;
      BitField<17, 1, u32> unk17;
      BitField<18, 1, u32> unk18;
      BitField<19, 1, u32> unk19;
      BitField<20, 1, u32> unk20;
      BitField<21, 1, u32> unk21;
      BitField<22, 1, u32> unk22;
      BitField<23, 1, u32> unk23;
      BitField<24, 1, u32> unk24;
      BitField<25, 1, u32> unk25;
      BitField<26, 1, u32> unk26;
      BitField<27, 1, u32> unk27;
      BitField<28, 1, u32> unk28;
      BitField<29, 1, u32> unk29;
      BitField<30, 1, u32> unk30;
      BitField<31, 1, u32> unk31;
    };
    switches1 switch1;
    u32 chest;
    u32 collectible;
  };
  static_assert(sizeof(PersistentSceneCycleFlags) == 0x10);

  PersistentSceneCycleFlags* GetPersistentCycleStruct();
  void KillAllActorsWithMissingObjects(game::GlobalContext*);
}  // namespace game
