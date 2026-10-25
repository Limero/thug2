THUG2
============================

A work-in-progress matching decompilation of Tony Hawk's Underground 2 (GameCube, USA).

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Clean-room policy: leaked source code for Tony Hawk's Underground 1 is publicly
circulating, but **nothing from it is used in this project**. All code here is
written from the compiled game binary only. Real function names come from script data extracted from the game or
symbol data for Tony Hawk's Proving Ground (Wii), not from the leak.

Supported versions:

- `G2TE52`: Rev 0 (USA)

Unsupported versions:

- `G2TP52`: Rev 0 (EU)

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/Limero/thug2.git
  ```

- Copy your game's disc image to `orig/G2TE52` (e.g. as `game.rvz`).
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python3 configure.py --dtk tools/dtk --ninja tools/ninja
  ```

  To use a version other than `G2TE52` (USA), specify it with `--version`.

- Build:

  ```sh
  tools/ninja build/G2TE52/main.dol
  ```

  The first build downloads the toolchains automatically (SN Systems ProDG for
  game code, Metrowerks mwcc via wibo for runtime objects). This takes a while;
  subsequent builds are fast.

- Verify the build matches the original (`build/G2TE52/main.dol: OK` means matching):

  ```sh
  tools/ninja build/G2TE52/ok
  ```

Note: the default ninja target is `progress` (full objdiff report, slow).
Always build the specific targets above for a quick matching check.

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.
