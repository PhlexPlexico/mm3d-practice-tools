# The two `game/` trees

`code/include/game` (from mm3dr) and `mm3d-practice-tools/source/game` both
descend from leoetlino's Project Restoration and have drifted apart since.
**mm3dr's copy is authoritative here.** The skeleton already compiles against it,
it is the more developed of the two (19 shared headers, mm3dr a superset in
almost all), and it carries ~164 `static_assert(offsetof(...))` layout
assertions that the practice tool's copy mostly lacks.

Practice-tool headers are imported **one feature at a time**, in the same commit
as the code that needs them — never in bulk. A struct-layout mismatch does not
fail to compile, it silently reads the wrong memory.

## Differences that are not real

These show up in a naive diff but do not change layout. Rewrite on import:

| practice tool | mm3dr | note |
|---|---|---|
| `rst::Flags<T>` | `rnd::Flags<T>` | namespace only |
| `rst::BitSet<...>` | `rnd::BitSet<...>` | namespace only |
| `Vec3` / `Vec4` (Eigen) | `z3dVec3f` / `z3dVec4f` | same storage; this is the Eigen removal |
| `u32 offset` | `const char* offset` | both 4 bytes (`MessageResText`) |
| `field_368C` | `magic_max_2` | mm3dr named the field |
| `gap_14C[200]`, `gap_20F[293]` | shorter gaps + named fields | mm3dr filled the gap in |

## Differences that are real

Resolve against **Ghidra (USA 1.0, port 8081)** before importing the feature that
touches them; the struct offsets in the binary are ground truth. Add a
`static_assert(offsetof(...))` for whatever is settled.

| struct | practice tool | mm3dr | why it matters |
|---|---|---|---|
| `CommonDataSub1` member 9 | `int field_14` | `u8 option_3` | size differs — shifts every later field. **Save states read this.** |
| `CommonDataSub3` member 0 | `u32 field_0` | `u8 field_0` | size differs |
| `PlayerData` member 1 | `gap_120[2]` | `gap_124[2]` | gap named for a different offset — something before it differs by 4 |
| `ActorUtil` member 0 | `void* vtable` | `u16 field_0` | 4 bytes vs 2 |
| `DynaPolyActor` size | `0x20C` | `0x210` | **resolved below — mm3dr was wrong** |
| `ActorLists` member 0 | `gap_0[4]` | `u8 freeze_flash_timer` | check mm3dr accounts for all 4 bytes |

## Resolved

| what | outcome |
|---|---|
| `MaskId` first enumerator | **Not a conflict.** Every enumerator is explicitly valued in both and the shared ones match; mm3dr simply adds `None`, `MaskOfTruth` and `BunnyHood`. A superset, not a renumbering. |
| `InventoryData` bit 17 | **Layout identical**, both `BitField<17, 1, u32>`; only the name is disputed (`suns_song` vs `scarecrows_song_icon`). Using mm3dr's. The practice tool's own menu labels it "does nothing", so nothing depends on which is right — but nobody has confirmed it against the game, so the label keeps the caveat. |

### `DynaPolyActor` — mm3dr was wrong

The one case so far where the authoritative tree lost. mm3dr had a trailing
`u8 interact_flags` that rounded the struct to `0x210`, shifting every subclass
field by four.

Checked against the game with Ghidra (USA 1.0, port 8081) and the disassembly:
`calc_move` at `0x2AC52C` reads its `ObjStoneTowerBlock` at `[r4,#0x20C]`,
`#0x210`, `#0x214`, `#0x218` and stores the action function at `[r4,#0x220]`.
Those are the subclass's own fields, so the base must end at `0x20C`.

Corrected in `include/game/actor.h`, keeping mm3dr's better field names and
dropping only the trailing member. Caught by `ObjStoneTowerBlock`'s
`static_assert(sizeof(...) == 0x228)` failing at compile time — which is the
whole reason those assertions are worth carrying.

**Being authoritative means being the default, not being right.** The binary is
the tiebreaker.

## Layout-clean

Identical member order in both, safe to use as-is: `scene.h`, `sound.h`,
`static_context.h`, `states/state.h`, `ui/screens/screen.h`,
`ui/layouts/message_window.h`, `ui/layouts/play_hud.h`,
`actors/obj_elegy_statue.h`.

Also verified identical where it matters so far: `FormEquipmentData`,
`EquipmentData`, `ItemId` (all enumerators explicitly valued, so safe regardless).

## Only in the practice tool

Import on demand, alongside the feature that needs them:

`actors/boss_{goht,gyorg,odolwa,twinmold}.h`, `actors/npc_bombers.h`,
`actors/obj_owl_statue.h`, `actors/obj_stone_tower_block.h`, `memory.h`,
`random.h`, `states/state_ending.h`, `states/state_sot_save.h`,
`ui/layouts/{item_icon,num_all,play_action_icon}.h`, `ui/message_text.h`,
`ui/res.h`, `ui/screens/{gear_screen,main_screen,schedule_screen}.h`
