# MM3D Practice Patch

**MM3D Practice Patch** is a *Majora's Mask 3D* patch that includes game patches from [Project Restoration](https://github.com/leoetlino/project-restoration) and some other custom patches that makes the game a bit easier to glitch hunt and practice speedrun strategies.

Please refer to the [official website at restoration.zora.re](https://restoration.zora.re) for setup instructions.

## Rationale
Right now there is a project for the OoT3D community that has a practice patch that includes things such as warp codes, items, actor watches, to name a few of the features.

This patch is going to aim to implement these things as well, and throw in some more custom code that is aimed more towards Majora's Mask 3D.


## About the project

After viewing the source code of [Project Restoration](https://github.com/leoetlino/project-restoration), and ~~annoying~~ asking @leoetlino for help with this, I was able to strip out a majority of Restoration's code, and start including my own. However, there are a few things I've kept in as quality of life (QOL) improvements, such as decoupling the ZL/ZR buttons, and some minor start menu changes.

The following features exist in this patch:
- In game menu support (thanks Gamestabled)(L+R+Start)
- Re-assign hotkeys for commands
- Run fast (default Y)
- Moon Jump (default X+A)
- Reload the current scene
- Restore Healt/Magic
- Return to file select
- Restore Item Counts
- ~~Void from current scene~~
- ~~Actor Watches~~
- ~~Change Time~~
- ~~Freeze/Slowdown/Speed up Time~~
- ~~Give equipment~~
- ~~Give Masks~~

The aim of this project is to create an environment for a player so that they can practice tricks, glitch hunt, and reset at ease without having the hassle of turning off or resetting the game.

## Thanks To
 - Gamestabled for the initial [OoT3D Practice Patch](https://github.com/gamestabled/oot3d_practice)
 - [Leo](https://github.com/leoetlino) for the source of Project Restoration, plus all the pestering he's had to put up with me and my questions!
 - N3rdsWithGame for the initial idea of Frame Advance and his repos for basic implementation.
 - Megahirtz for testing

### Project structure

* `source/` *Project Restoration*'s source code.
  * `build/`: build outputs.
  * `common/`: small utilities.
  * `game/`: implementation for the known parts of *Majora's Mask 3D*. Contains headers and some reimplementation of game functions.
  * `rst/`: *Project Restoration*/*MM3D Practice Patch* code.
* `hooks/`: configuration for patches and hooks (for Magikoopa).
* `loader/`: Code loader (from [Magikoopa](https://github.com/RicBent/Magikoopa)).

Sometimes you will find *Project Restoration* extensions and new code under `source/game`. Those extensions will always be clearly labelled as such.

### Build instructions

* Put the original code.bin and exheader.bin files in the v100, v101 and v110 folders respectively. You must dump those binaries from the ExeFS yourself; those are **not** provided in this repository for copyright reasons. (TODO: Make better explanation)
* Run make_release.sh. You need git and Magikoopa and Flips in your PATH. **Currently, a [fork](https://github.com/leoetlino/Magikoopa) is required**.
* Generated code patches (code.bps) and patched exheaders can be found in `release/`.
* If you're using Luma on 3DS, copy over exheader_legacy.bin as exheader.bin, and code.bps to /luma/titles/0004000000125500/ where 0004000000125500 is the TitleID of Majora's Mask 3D US. (TODO: Update make_release to change exheader names)

PRs and help are welcome!
