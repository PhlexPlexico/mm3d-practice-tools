# MM3D Practice Patch

This is a project that gives a [Rosalina](https://github.com/LumaTeam/Luma3DS)-like menu, which is packed with features that are kindly imported from the likes of [kz](https://github.com/krimtonz/kz) and [OoT3D Practice Patch](https://github.com/gamestabled/oot3d_practice_menu) in hopes of streamlining practice, and make the discovery of bugs easier to accomplish. There are also a few improvements that have been borrowed from [Project Restoration](https://github.com/leoetlino/project-restoration) (plus a bunch of its source for methods and in game functions!).

## Shoutouts
 - Gamestabled for the initial [OoT3D Practice Patch (gz3d)](https://github.com/gamestabled/oot3d_practice)
 - [Leo](https://github.com/leoetlino) for the source of Project Restoration, plus all the pestering he's had to put up with me and my questions! Without Restoration, this would have been a hell of a lot harder to implement.
 - N3rdsWithGame for the initial idea of Frame Advance and his repos for basic implementation/notes from years before about making game patches for MM3D and OoT3D.
 - Megahirtz for testing, and implementing all of warp locations!
 - MrCheeze for helping me figure out some warp rooms and inputs.
 - Rylie for helping me with entrances/warps as well.
 - The entire MM3D community, for giving me the motivation and helping all features that are currently included!
 - [kz](https://github.com/krimtonz/kz) for reference for some features.


## Notes About the Project

After viewing the source code of [Project Restoration](https://github.com/leoetlino/project-restoration), and ~~annoying~~ asking [leoetlino](https://github.com/leoetlino) for help with this, I was able to strip out a majority of Restoration's code, and start including my own. However, there are a few things I've kept in as quality of life (QOL) improvements, such as decoupling the ZL/ZR buttons, some minor start menu changes, and quick song of soaring.

The aim of this project is to create an environment for a player so that they can practice tricks, glitch hunt, and reset at ease without having the hassle of turning off or resetting the game.

### Project structure

* `source/` *Project Restoration*'s source code.
  * `build/`: build outputs.
  * `common/`: small utilities.
  * `game/`: implementation for the known parts of *Majora's Mask 3D*. Contains headers and some reimplementation of game functions.
  * `rst/`: *Project Restoration*/*MM3D Practice Patch* code.
  * `msys/`: The rest of the practice patch code.
* `hooks/`: configuration for patches and hooks (for Magikoopa).
* `loader/`: Code loader (from [Magikoopa](https://github.com/RicBent/Magikoopa)).

Sometimes you will find *Project Restoration* extensions and new code under `source/game`. Those extensions will always be clearly labelled as such.

## How to Use
- Ensure you have the latest version of Luma3DS installed.
- Grab the latest [release](https://github.com/PhlexPlexico/mm3d-practice-tools/releases) from the releases page.
- For 3DS Users:
  - USA: Place `code.ips` and `exheader.bin` in `/luma/titles/0004000000125500/`
  - JPN: Place `code.ips` and `exheader.bin` in `/luma/titles/00040000000D6E00/`
  - EU: Place `code.ips` and `exheader.bin` in `/luma/titles/0004000000125600/`
- For Citra Users:
  - Right click Majora's Mask 3D and Open Mods Location. 
  - Place `code.bps` and `exheader_citra.bin` in the folder that was opened.
  - Rename `exheader_citra.bin` to `exheader.bin`

## [Usage](./USAGE.md)

### Build instructions
#### Preparing your environment
- Put the original code.bin and exheader.bin files in the v100, v101 and v110 folders respectively. You must dump those binaries from the ExeFS yourself; those are **not** provided in this repository for copyright reasons.
- You will need the following build tools available on your PATH:
  - This [fork](https://github.com/leoetlino/Magikoopa) of Magikoopa for command line patching.
  - Ninja (ninja - small build system closest in spirit to Make).
  - [Flips](https://github.com/Alcaro/Flips)
  - [devkitPro](https://devkitpro.org/wiki/Getting_Started)
  - git
* Run make_release.sh.
* Generated code patches (code.bps) and patched exheaders can be found in `release/`.

PRs and help are welcome!
