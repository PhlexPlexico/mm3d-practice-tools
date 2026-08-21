# MM3D Practice Tools — @VERSION@ (@PACKAGE@)

This package is for **one specific game version and target**. The exheader
differs between them, so do not mix files between packages.

## Console (Luma3DS)

Copy both files to:

    sd:/luma/titles/@TITLE_ID@/

Then enable **Game Patching** in the Luma configuration menu (hold Select at
boot).

## Citra / Azahar / Emulator

Copy both files to:

    <emulator data dir>/load/mods/@TITLE_ID@/

If a `code.bps` from an older release is already there, remove it first — both
would be applied and they will conflict.

## Contents

| file | |
|---|---|
| `code.ips` | the patch, applied to the game's `code.bin` |
| `exheader.bin` | grows the mapped data region and grants the loader's SVC and SD access |
