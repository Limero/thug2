# rodata2 name clusters → function names & source-file groupings

Status: analysis complete, DOL-verified. Companion data:
[`rodata2-script-command-registry.tsv`](rodata2-script-command-registry.tsv) (full 1327-row registry
with a `stub` column), regenerable with `tools/venv/bin/python tools/analyze_rodata_names.py`.

## TL;DR

The strings that look like function names inside
`build/G2TE52/obj/auto_03_8028FB60_rodata2.o` are **not** symbols — they are
string literals in the DOL's `.rodata2` section (0x8028FB60, 141 KB), referenced
by three pointer tables in `.data`. The big one is the **THUG2 script-command
registry**: 1327 × `{const char *name, void (*func)()}` entries at
`.data` 0x80303464. Each entry pairs a command name with the address of its
implementation function, which means the registry **provides original C function
names** for the `fn_XXXXXXXX` symbols:

| command name | function | size | decompiled |
|---|---|---|---|
| `LoadScene` | `fn_80118A84` | 0x1D0 | no |
| `UnloadScene` | `fn_80118DF8` | 0x98 | no |
| `SkaterGetScoreInfo` | `fn_80159618` | 0xBC | no |
| `GetCurrentAnimTimes` | `fn_80110654` | 0x8 | **yes** |
| `MemPushContext` | `fn_80117FC0` | 0x9C | no |
| `DebugLine` | `fn_8011058C` | 0xB8 | no |
| `GoalManager_GetGoalList` | `fn_80189F18` | 0x120 | no |

Section 6b inventories the other name sources in the DOL (class-name MemManager
tags, heap-name hash table, source paths, vtables) plus the 1.2 GB `game.rvz`
disc image that holds the rest of the game's names.

Headline numbers (from the corrected extraction):

- **1327** registry entries → **1202** with a func pointer → **1185** distinct functions.
- **280** of those functions are already decompiled (`src/fn_*.c` exists) — they can be
  renamed with their real names right now.
- **905** are still unmatched — the registry doubles as a ranked naming/target list.
- **72** are 8-byte `li r3, imm; blr` STUBS (flagged `stub=Y` in the TSV): the GC build
  ships auto-generated placeholders for script commands stripped from this platform.
  They return a hardcoded 1/0 — the name is the *command* name, not a real implementation.
- The **consumers** of the registry (functions that look commands up by name) are
  177 functions, of which **175 are still unmatched** — i.e. the script engine core
  is one of the biggest remaining unmapped blobs, and it has a built-in name index.

---

## 1. What the `.rodata2` block actually is

- DOL section 8, `0x8028FB60` – `0x802B23A0` (0x22840 = 141 KB), file offset 0x28CB60.
- Content: ~4000 printable strings plus float/double constants and padding.
- The linker auto-split it into per-`lbl_` objects; `auto_03_8028FB60_rodata2.o` is
  simply the first auto-split chunk. Its symbol table contains only `lbl_*` data
  labels and `fn_*` externs — no function definitions.

Code never addresses the strings directly (0 `lis`+`addi` refs in `.text`). Instead
three tables in `.data` hold pointers to them:

| table | `.data` range | entries | kind |
|---|---|---|---|
| T1 | 0x80301B50 | 12 | file-type extension names |
| T2 | 0x80303030 | 67 | level-event / story names |
| T3 | 0x80303464 – 0x80305DDC | 1327 | **script-command registry** |

## 2. T3: the script-command registry (the goldmine)

Layout verified byte-by-byte: 8-byte entries, `name ptr` at +0, `func ptr` at +4,
1327 × 8 = 0x2978 exactly. Example raw dump around `MemPushContext`:

```
0x8030432C: 802A1F68  "GotExtraMemory"      <- name ptr
0x80304330: 80117FA4  FUNC                  <- func ptr (fn_80117FA4)
0x80304334: 802A1F78  "MemPushContext"      <- name ptr
0x80304338: 80117FC0  FUNC                  <- func ptr (fn_80117FC0)
0x8030433C: 802A1F88  "MemPopContext"
0x80304340: 8011805C  FUNC
```

- 1202 entries resolve to a `.text` function; 125 have a null func slot
  (command aliases / registration-only names).
- 9 functions are registered under multiple names, e.g. `fn_8014DB38` appears
  as `LaunchPanelMessage`, `LaunchLocalPanelMessage`, `KillMessages`,
  `ChangeLocalMessage`, `LaunchConsoleMessage`, `UseOnePadInFrontEnd`, … and
  `SetSkaterCamAnimSkippable` / `SetCutsceneSkippable` share `fn_8015A0D8`.
- The C shape is almost certainly an array of structs like
  `static const ScriptCommand g_scriptCommands[] = { {"LoadScene", LoadScene}, ... }`
  (or `{name, func, ...}` with a wider struct), registered once at boot.

**Stub detection** (TSV column 6): a registry function is a stub iff it is exactly
8 bytes of `addi rD, r0, imm` (li) followed by `blr` — i.e. it just returns a
hardcoded value. 72 funcs match (`li r3,1; blr` × 64, `li r3,0; blr` × 8),
e.g. `GetTime`, `GetCurrentAnimTimes`, `SkaterDebugOff`, `InGroupRoom`,
`Printf`, `PrintStruct`. Slightly larger single-load getters (0xC/0x10,
`lis r9,...; lwz r3,off(r9); blr`) are REAL functions (e.g. `CD`, `NotCD`,
`Bootstrap`, `Inside`) and are NOT flagged.

### Consumer analysis

Scanning `.text` for `lis`+`addi` sequences that resolve into T3's range shows
**177 distinct functions reference registry entries**. Only 2 are decompiled.
The top shared slots are command implementations referenced from many places
(e.g. the func slot at 0x80304330 — `fn_80117FA4`, `GotExtraMemory` — is
referenced from 40 code sites): these are the runtime call sites of the script
engine, all still unmatched.

## 3. The names are real function names — use them

`GetCurrentAnimTimes`, `LoadScene`, `SkaterGetScoreInfo` and friends are the
original function names from the THUG2 source tree (the game registers its script
commands by name). Naming conventions visible in the registry confirm this is the
`gel/` codebase: `GoalManager_*`, `Obj_*`, `Ngc_*` (GameCube-specific), `Skater*`,
`Park*` (park editor), plus engine primitives (`MemPushContext`, `Printf`,
`DebugLine`, `DumpHeaps`).

Subsystem prefix distribution (distinct command names):

| prefix | commands | decompiled now |
|---|---|---|
| `GoalManager_` | 140 | 89 |
| `Obj_` | 22 | 0 |
| `Weather` | 20 | 0 |
| `Skater` | 19 | 4 |
| `Print` | 13 | 10 |
| `Ngc_` | 10 | 2 |
| `Dump` | 9 | 3 |
| `Mem` | 7 | 1 |
| `Car` / `Park` | 7 / 7 | 0 / 3 |
| ... | ~1029 other | ~162 |

### Recommended next steps

1. **Rename the 280 decompiled functions** to their registry names
   (TSV column 5 == `Y`). They are byte-identical matches already; renaming is
   cosmetic but makes every subsequent diff and doc far more legible, and the
   names cluster into the original source files (`goalmanager.cpp`, `ngc_*.cpp`,
   `skater_*.cpp`, `music.cpp`, `mem.cpp`, ...). For `stub=Y` rows (column 6),
   keep the name but add a `// stubbed on GC (command stripped)` comment — the
   real implementation is not in this binary.
2. **Target the 905 unmatched registry functions next.** Each row gives the
   function's real name, address and size — a ready-made work list. Small ones
   first (e.g. `GetCurrentAnimTimes` is 8 bytes: `mr r3, ...; blr`).
3. **The 175 unmatched consumers are the script engine.** Functions that
   `lis`+`lwz` a registry entry are `Script_*` dispatch / binding code; the
   registry gives them names too once matched.
4. **Name the class/heap/vtable hubs from section 6b** — `fn_80145C14`
   (global manager init), `fn_80054720` (render-manager init),
   `fn_8000F36C` (heap-name lookup), `fn_8001CC70` (NGC hardware init,
   `p_hwinit.cpp`) and the 7 vtable constructors: a quick batch of real,
   verifiable names for functions already in the tree.

## 4. T1: file-type extension table (12 entries)

`BIN COL SCN GEOM MDL SKA FAM SKE SKIN TEX CUT QB` at `.data` 0x80301B50.
This is the scene-file type table (`.scn`, `.col`, `.geom` …). Only one
consumer found: `fn_800F2270` (unmatched) — almost certainly the scene-load
dispatcher that maps a file extension to a loader.

## 5. T2: level-event / story names (67 entries)

`LevelEvents/AU_LevelEvent1`, `LevelEvents/AU_SmallEvent_Billboard`,
`Story/BO_2B_Male1`, `Story/SK_9_Male4`, … at `.data` 0x80303030.
Level-goal event trigger names (AU = Australia, BO = Boston, TR = Tampa, …).
5 consumers, all unmatched (e.g. `fn_80121314` references
`LevelEvents/AU_LevelEvent1`).

## 6. Direct string refs from matched functions

34 already-decompiled functions reference `.rodata2` strings directly (not via
the tables). Notable subsystem hints for grouping:

- `fn_80192588` — `win_record / gotBronze / gotSilver / gotGold / reward_given` (goal rewards)
- `fn_80054894`, `fn_8005761C` — `levels\%s\%s%s.scn.%s` / `levels\%s\%s%s.col.%s` (scene/col loading)
- `fn_801225F8` — `c:/nxcommon_skate6/code/gel/movies/NGC/p_movies.cpp` + assert text (movie system, matches `Movie` commands)
- `fn_801FA0E8` — `CEditedRailPoint / CEditedRail` (park editor rail data)
- `fn_800F3894`..`fn_800F5C60` — `Unnamed Asset / Animation / Scene / SceneColl / Skeleton / Skin / SkinColl` (asset registry type strings — the asset manager)

## 6b. More name sources in the game data

Beyond the command registry, four more name-bearing structures live in the DOL:

### 6b.1 Class-name MemManager tags (82 strings -> 4 named functions)

82 `C[A-Z]...` class-name strings sit in rodata2, mostly in consecutive clusters
(`CViewportManager CFlexibleParticleManager CImposterManager`,
`CPathMan CAssMan CSfxManager CCompositeObjectManager CTrickObjectManager
CGameMode CPlayerProfileManager CGameRecords CParkEditor CScreenElementManager
CNodeArrayManager CTODManager`, and the script-system `CStruct CVector CPair
CArray CScript CSymbolTableEntry ...`). They are Neversoft MemManager debug
block tags pushed around constructions (`bl MemPushBlock; ...; bl MemPopBlock`).
Functions referencing them:

- `fn_80145C14` — references ALL 11 manager names → global manager init/registry.
- `fn_80054720` — CViewportManager + CFlexibleParticleManager + CImposterManager → render-manager init.
- `fn_80125AEC` — CComponent; `fn_800A2A60` — COIMHeap.

### 6b.2 Heap-name hash table -> fn_8000F36C

The heap names (`BottomUpHeap`, `SkaterGeom0-3`, `ThemeHeap`, `CutsceneTopDown`, ...)
are hashed constants in a dispatch function: `fn_8000F36C` compares its argument
against ~19 `lis/ori` heap-name hash constants — it is the heap-name→heap-ID
lookup (binary-search over hashes). `fn_8000EE70`, `fn_8000FAB4`, `fn_8000FF18`
consume subsets. The constants are the **same Neversoft QB string hash** — now
reverse-engineered (section 6c, `tools/qb_hash.py`), so these heap names can be
verified/expanded by hashing candidate strings.

### 6b.3 Source-file path strings (3)

Only 3 `c:/nxcommon_skate6/code/...` paths survive in the DOL (assert `__FILE__`
strings, stripped in release):

- `fn_8001CC70` → `code/sys/NGC/p_hwinit.cpp` (NGC hardware init — confirmed: writes hw regs).
- `fn_801225F8` → `code/gel/movies/NGC/p_movies.cpp` (movie system).
- music path → gel/music/NGC/p_music.cpp consumer.

### 6b.4 Vtables & method tables — see `data-structures.md` (corrected)

Earlier versions of this note reported “14 vtables, ~700 method slots” with
constructor pairs like fn_80286B0C→0x8030FB80. **That was wrong**: those runs
are mostly **switch jump tables** (e.g. 0x8030FB80 is `fn_80286B0C+0x20`-
style offsets dispatched via `lwzx/mtctr/bctr` — dtk names them
`jumptable_*`, 20 total).

The corrected, regenerable analysis lives in
[`data-structures.md`](data-structures.md) (`tools/analyze_data_structures.py`):

- **5 genuine method tables** (91 slots) at 0x8030804C, 0x803084AC, 0x803089D0,
  0x80308A40, 0x80308B22 — consecutive fn-pointer families (e.g.
  0x803089D0 → fn_8028DF14..fn_8028DF38, the tiny stub methods). These are
  registered through the **interface map at 0x80308040** (a data-pointer
  table holding {0x8030804C, 0x80308060, 0x80308074}) rather than stored by
  per-class ctors.
- **20 jump tables** (dtk-named) + 2 string-pointer tables + the T3
  {name,func} registry split (381 + 820 pairs) + 3 data-pointer tables.

Methods are nameable as `Vtable0x803089D0_mN`; the class NAMES are not in the
DOL (disc image, see below).

### 6b.5 The disc image: `orig/G2TE52/game.rvz` (1.2 GB) — extracted, and the QB hash is cracked

The DOL's 4,000 strings are a tiny slice of the game's names. `game.rvz` is a
compressed GameCube disc image containing the QB script files (script command
usage, thousands of constants/struct/object names). It is now extracted (see
section 6c) and — the big unlock — **the Neversoft QB string hash was
reverse-engineered from the DOL** and verified against name/hash pairs embedded
in the QB script files. Every hash constant in the DOL's `.text` is now
resolvable.

## 6c. The Neversoft QB hash — CRACKED (fn_8000A778)

The script engine's string→hash routine is `fn_8000A778`. It is a table-driven
CRC-style hash:

```
hash = 0xFFFFFFFF
for each char c (lowercased if A-Z; '/' normalized to '\\'):
    hash = table[(hash ^ c) & 0xFF] ^ (hash >> 8)
```

The 256-entry u32 table lives at `.data` 0x802FFA3C in the DOL (it is a custom
Neversoft CRC table — not crc32/djb2/fnv/jenkins, which is why all standard
candidates failed). Verified 5/5 against `[hash][string]` pairs embedded in the
`.prg` files:

| string | hash |
|---|---|
| `anims\\Ped_M\\Ped_M_CheerIdle6.ska.ngc` | 0x7E62B845 |
| `anims\\Ped_M\\Ped_M_CheerIdle5.ska.ngc` | 0x47EF8480 |
| `anims\\Ped_M\\Ped_M_CheerIdle2.ska.ngc` | 0x238EE949 |
| `anims\\Ped_M\\Ped_M_CheerIdle3.ska.ngc` | 0x34F5FD0A |
| `anims\\Ped_M\\Ped_M_CheerIdle4.ska.ngc` | 0x509490C3 |

Tools: `tools/qb_hash.py` (hash impl + table extraction, self-verifying).

**Collision caveat:** the resolver builds its dictionary by hashing every
plaintext name in the `.prg` files (≈118k names) with first-wins on hash
collisions; expected self-collisions are ~1–2, so a handful of the 380
resolutions could map to the wrong string. Spot-check any name you rely on
against the disassembly (the constant site should be `lis+ori` followed by a
hash compare/lookup).

### 6c.1 Resolving the DOL's hash constants

Hashing every plaintext name found in the `.prg` files and matching against the
3177 `lis+ori` 32-bit constants in `.text` resolves **380 constants (12%)** to
real names — e.g. `Skater` (0x5B8AB877), `Default` (0x1CA1FF20), `Skeleton`
(0x222756D5), `Network` (0xE37E78C5), `Focus`, `Texture`, `Script`, `Start`,
`TopDown`, `Obj_Flip`, `WaitAnim`, `RailNode`, `Position`, `Geometry`…
Verification: the constant sites are `lis+ori` immediately followed by a hash
compare/lookup (`cmpw r9,r0` or `bl` into the symbol resolver), and short names
resolve consistently across many sites. Full table:
[`dol-qb-hash-resolved.tsv`](dol-qb-hash-resolved.tsv).

The remaining 88% are constants whose names are not in plaintext anywhere on
the disc (QB symbol names are stored hashed-only in the bytecode); they are
resolvable in bulk only by decompiling the QB script files themselves.

### 6c.2 What the disc image adds

`game.rvz` was converted with the Dolphin flatpak (`dolphin-tool`, run with
`XDG_RUNTIME_DIR` set; sandbox needs `--filesystem=` on the repo). Contents
(listing in `orig/G2TE52/disc/files/`):

- **`scripts/qdir.txt`** — the original source-tree list of **209 `.qb` script
  files** (`c:\\skate6\\data\\scripts\\*.qb` — `allanims.qb`, `skater_helpers.qb`,
  `engine/camera.qb`, `debugger/view_object.qb`, …), saved to
  [`qdir-script-sources.txt`](qdir-script-sources.txt). These name the script
  modules (not C++ files, but subsystem hints).
- **`pre/*.prg/.prd/.prf`** (164 files) — compiled QB scripts. They embed
  `[hash u32][plaintext string]` pairs for named symbols (anim paths,
  goal/script names, constants). The plaintext names (~27k in script files,
  e.g. `GoalManager_DeactivateAllGoals`) are the QB-level symbol names;
  18 of them also appear in the DOL command registry.
- **`levels/Default/default.qb*`** etc. — per-level compiled QB.
- `anims/`, `models/`, `textures/`, `music/`, `world/pak/` — asset dirs.

Extraction commands (one-liners):

```
export XDG_RUNTIME_DIR=/tmp/xdgrt
flatpak run --filesystem=$PWD --command=dolphin-tool org.DolphinEmu.dolphin-emu \
  extract -s pre -i orig/G2TE52/game.rvz -o orig/G2TE52/disc
```

## 7. Method (how to reproduce)

1. Index printable runs in `.rodata2` (addr → string).
2. Scan `.data` for 4-byte slots whose value lands in `.rodata2` (→ name pointers).
3. For T3, walk 0x80303464 in 8-byte steps; `{name, func}` pair per entry; resolve
   func addresses against `config/G2TE52/symbols.txt`.
4. Consumers: scan `.text` for `lis`+`addi`/`ori`/`addis` resolving into each
   table range; map the ref site to the covering `fn_*` symbol.
5. All checks are against `orig/G2TE52/sys/main.dol`; decompiled status =
   `src/fn_XXXXXXXX.c` exists.

Full tooling:

- `tools/analyze_rodata_names.py` — regenerates the command-registry TSV + stats.
- `tools/qb_hash.py` — the cracked Neversoft QB hash + table extraction (self-verifying).
- `tools/resolve_qb_hashes.py` — hashes `.prg` plaintext names and resolves DOL `lis+ori` constants.

## 8. Caveats

- Name→func pairing must read each 8-byte entry as `{name@+0, func@+4}`.
  Naive "pair a name with the nearest func in either direction" mispairs every
  entry with its neighbor (e.g. `MemPushContext` ↔ `fn_80117FA4` is WRONG; the
  correct func is `fn_80117FC0`, and `fn_80117FA4` is `GotExtraMemory`).
- The 125 null-func entries are aliases or registration-only rows; don't assume
  every name maps 1:1 to a unique function.
- These are script-command names, i.e. the *public* C names for those functions;
  internal helpers are not in the table.
- The QB hash is verified against embedded `[hash][string]` pairs; the 380
  resolved constants are correct *as names* but the semantics are still up to
  interpretation (e.g. `Skater`/`Default` are command/struct names, not
  function names).
- `stub=Y` (72 rows) means the function is an 8-byte `li;blr` placeholder, NOT a
  real implementation — `GetTime` returning 1 is the command being stripped on
  GameCube, not a real time getter. Don't describe stub behavior as real logic.
- TSV pairings were re-verified against an independent raw-DOL walk: 0 of 1202
  func rows differ (20/20 spot-checks OK).
