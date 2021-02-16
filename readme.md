# MM3D Practice Patch

**MM3D Practice Patch** is a *Majora's Mask 3D* patch that includes game patches from [Project Restoration](https://github.com/leoetlino/project-restoration) and some other custom patches that makes the game a bit easier to glitch hunt and practice speedrun strategies.

Please refer to the [official website at restoration.zora.re](https://restoration.zora.re) for setup instructions.

## Rationale
Right now there is a project for the OoT3D community that has a practice patch that includes things such as warp codes, items, actor watches, to name a few of the features.

This patch is going to aim to implement these things as well, and throw in some more custom code, such as time freezing/moving, and a few of the cheats that Luma has.


## About the project

After viewing the source code of [Project Restoration](https://github.com/leoetlino/project-restoration), and ~~annoying~~ asking @leoetlino for help with this, I was able to strip out a majority of Restoration's code, and start including my own. However, there are a few things I've kept in as quality of life (QOL) improvements.

As of right now the following features exist:
- Frame advance (Done by pressing R+d-pad down, then d-pad right to advance frames).
- Pressing select/start in the ocarina menu opens up the songs instead of touch screen.
- Bomber's notebook can be interacted with buttons.
- Faster blocks in Stone Tower
- ZR + Start/Select Open Different menus.
- ZR + Dpad left stops time. 
- ZR + Dpad Right resumes time. Press it again to speed up time.


The aim of this project right now is to provide some hot-keys for useful commands (time control, frame advance...) and will later be expanded to include other things such as giving items to the player.

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

* Put the original code.bin and exheader.bin files in the v100, v101 and v110 folders respectively. You must dump those binaries from the ExeFS yourself; those are **not** provided in this repository for copyright reasons.
* Run make_release.sh. You need git and Magikoopa and Flips in your PATH. **Currently, a [fork](https://github.com/leoetlino/Magikoopa) is required**.
* Generated code patches (code.bps) and patched exheaders can be found in `release/`.
* If you're using Luma on 3DS, copy over exheader_legacy.bin as exheader.bin, and code.bps to /luma/titles/0004000000125500/ where 0004000000125500 is the TitleID of Majora's Mask 3D US.

# Thanks To
 - [Leo](https://github.com/leoetlino) for the source of Project Restoration, plus all the pestering he's had to put up with me and my questions!
 - N3rdsWithGame for the initial idea of Frame Advance and his repos for basic implementation.
 - Megahirtz for testing

PRs and help are welcome!
