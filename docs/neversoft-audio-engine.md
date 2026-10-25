# THUG2 audio stack map (identification)

Companion to `docs/neversoft-math-lib.md`. This doc records the **identification**
of every game-side function that touches the Dolphin SDK audio layer (AR / ARQ /
AI / AX / DSP) in the retail `main.dol` (`orig/G2TE52/sys/main.dol`,
case `G2TE52`). All addresses are virtual. No decomp work has been done on
this stack yet - the goal here is a reliable address-level map and the
game/SDK separation line.

## 1. The SDK audio layer (present in the DOL, unwired in the build)

The audio SDK code that the game links against:

| Region | Extent | Notes |
|---|---|---|
| AR / ARQ / AI | 0x80274BEC - 0x80277030 | `ARQPostRequest` at 0x8027691C (5 game callers) |
| AX | 0x802773A0 - 0x8027A3BC | Mar-11-2003 build = the **bfbb-era** SDK copy (tww-line tooling has it too); `AXInit`, `AXQuit`, `AXSetMode`, `AXSetCompressor`, `AXAcquireVoice`, `AXFreeVoice`, `AXRegisterCallback` all named in `symbols.txt` |
| DSP | 0x80280B14 - 0x80280CDC | DSP microcode loader |
| 64-bit shift helpers | fn_80273480 (`slw`-pair, shift-left), fn_80273B68 (`srw`-pair, shift-right) | live MSL-zone runtime helpers; **not** named; called only by the soundtrack cluster (see §5) and `ScriptTrackEnabled` |

The AX module is unwired in the build (tww/bfbb `libs/dolphin/ax*` when the
time comes - see `docs/dolphin-sdk.md` for the wiring audit).

## 2. Game-side audio code: five clusters, not one region

The game's audio engine is **not contiguous**. It sits in four address bands:

| Cluster | Addrs | Role |
|---|---|---|
| A | 0x8001BA14 / 0x800181A4 / 0x8001D4FC-0x8001D768 | audio bootstrap, teardown/reset, ARAM DMA helpers |
| B | 0x80119510 - 0x80123BE0 (interleaved) | core sound engine: play/stop, voice pool, stream loaders, 3D panning |
| C | 0x8011D588 - 0x8011E0E4 | soundtrack / track engine (64-bit shift users) |
| D | 0x801354B4 - 0x80135E4C | second voice pair (trick sounds / frontend sfx) |
| E | 0x80124C00 - 0x80124478 | FMV movie player (VI + GX + AX audio callback) |

## 3. Cluster A - bootstrap / teardown / ARAM DMA (0x8001xxxx)

Master init path: `fn_8001BA14` (OSInit, DVDInit, VIInit, VIConfigure, thread
create, OSSetResetCallback) calls the audio bootstrap:

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_8001BCA8 | - | `ARInit`, `ARQInit`, `AIInit`, `AXInit`, `AXSetMode`, `AXSetCompressor`, `OSGetArenaLo`/`OSGetArenaHi`, `OSSetArenaLo`, `OSVReport` | **audio bootstrap**: initializes the whole AR/ARQ/AI/AX stack and carves the arena for it (reads the game settings globals `lbl_8025E9AC`/`lbl_8025EDA0`/`lbl_8025F0D4`/`lbl_8025EA48`) |
| fn_800181A4 | - | `ARQFlushQueue`, `AXQuit`, `AIReset`, `ARQReset`, `ARReset`, `ARGetDMAStatus`, `PADRecalibrate`, `VIFlush`, `VIWaitForRetrace`, `OSResetSystem` | **teardown / reset handler**: quits AX, resets all audio hardware, then soft-resets the console (also calls fn_80120924) |
| fn_8001D4FC | - | `DCFlushRange`, `ARQPostRequest`, `memcpy` | ARAM DMA copy helper |
| fn_8001D668 | - | `DCFlushRange`, `ARQPostRequest`, `memcpy` | twin of fn_8001D4FC (different buffer/queue params) |
| fn_8001D768 | - | `ARGetBaseAddress` | returns the ARAM base for stream buffers |

Neighbor (not audio): fn_8001D040 - fn_8001D4C8 are tiny getter/setter pairs
over the setting globals `lbl_8025DFD4`/`lbl_8025E260`/... - the console
settings object, not audio.

## 4. Cluster B - the core sound engine (0x8011xxxx)

The bulk of the game's sound code. It reuses a handful of AX-internal
helpers (named `fn_80279*` here; all inside the AX module 0x802773A0-0x8027A3BC):
fn_80279CD0 (used 6x: voice-state helper), fn_80279C0C, fn_80279D2C,
fn_80279D78, fn_80279FCC, fn_8027A024, fn_8027A134, fn_8027A1D8, fn_8027A270,
fn_8027A308.

### 4.1 Init chain

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_80119510 | 104 | (calls fn_80119794) | sound-system init outer |
| fn_80119794 | 104 | (calls fn_8011ECA0) | mid init |
| fn_8011ECA0 | 160 | `OSGetSoundMode`, `AXRegisterCallback`, `memset`, `DCFlushRange` | **AX callback registration** (gated on OS sound mode = mono/stereo) |

### 4.2 Play / stop

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_8011A56C | 316 | - | **play-sound core**. Callers: `ScriptPlaySound`, fn_8011B9F4, fn_80196ACC, fn_801C1364, fn_80204928, fn_800EE0B8, fn_800EE55C, fn_8010CC40 |
| fn_8011B9F4 | 548 | (calls fn_8011A56C) | higher-level play path (volume/param setup) |
| fn_8011BEAC | 80 | - | stop-stream entry (callers: `ScriptStopStream`, fn_8011D0AC, fn_8011DED0; calls fn_80121178) |
| fn_8011BEFC | 216 | - | stop stream / free voice (callers: `ScriptStopStream`, fn_800CD534, fn_800CD6C8, fn_800EFB60, fn_801917FC, fn_80191C50) |
| fn_8011DED0 | 380 | - | stream-state manager (callers: fn_800AD890, fn_8016899C, fn_8019DB68; calls fn_8011BEAC, fn_80120B44) |
| fn_80120924 | 168 | `OSGetTick` | shutdown helper (callers: fn_800181A4, fn_8011BE68, fn_8011CA08, fn_8011D224) |

### 4.3 Voice pool (acquire / free / callback)

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_8011E8D0 | 96 | `AXFreeVoice` | free one voice (also called directly by fn_80135E4C) |
| fn_8011EF98 | 632 | `AXAcquireVoice` + fn_80279D2C, fn_8027A024, fn_8027A134, fn_8027A308, fn_80279FCC, fn_80279C0C, fn_8027A1D8, fn_80279CD0 | acquire + full voice setup |
| fn_80120B44 | 376 | `AXFreeVoice` (+ int-disable/restore) | int-protected free (callers: fn_8007E89C, fn_80098E64, fn_8011DED0) |
| fn_801210C4 | 180 | `AXFreeVoice` (+ int-disable/restore) | int-protected free |
| fn_80120D14 | 524 | `DVDConvertPathToEntrynum`, `DVDFastOpen`, `AXAcquireVoice`, `DVDReadAsyncPrio`, `DVDClose` | **voice + stream open**: loads a sound from DVD into a freshly acquired voice |
| fn_80122C40 | 1708 | `OSPanic`, `memset`, `DCFlushRange`, `AXAcquireVoice` + fn_80279D78, fn_80279FCC, fn_80279C0C, fn_8027A1D8, fn_8027A024, fn_8027A134, fn_80279D2C, `AXRegisterCallback` | big alloc + voice setup + callback (the main "play this sample" workhorse) |
| fn_801232EC | 188 | `AXRegisterCallback`, fn_80279CD0, `AXFreeVoice` | deallocate + unhook callback |
| fn_80120664 | 448 | `OSPanic`, fn_80269EC0, fn_80269EF8 | error/panic path of the voice pool |

### 4.4 Stream loaders (DVD -> RAM -> ARAM -> AX)

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_8011FDD0 | 1684 | int-disable/restore, `AXFreeVoice`, fn_80279D2C, fn_80279C0C, fn_80279FCC, fn_8027A024, fn_8027A134, `memset`, `DCFlushRange`, `ARQPostRequest` | **stream loader**: copies stream data, flushes cache, posts an ARQ DMA, frees the old voice |
| fn_80123BE0 | 1328 | fn_80279CD0, fn_8027A270, `DCFlushRange`, `ARQPostRequest`, `memset` | stream/music ARAM loader |
| fn_8012156C | 184 | `DVDReadAsyncPrio` | DVD read for stream data |
| fn_80121AD4 | 508 | `DVDReadPrio`, `OSPanic` | generic DVD read path used by the loaders |
| fn_80121CD0 | 176 | `DVDCancel` | cancel in-flight stream read |
| fn_8011E9A0 | 708 | `DCFlushRange`, `OSVReport` | stream flush + report |

### 4.5 Positional audio

fn_8011F590 (1464 B) calls `fn_80271170` (**sinf**) and `fn_80270CA4`
(**sqrtf**) - the only cluster-B function using the float lib. Likely
3D/panning math (per-voice distance/angle). (See `docs/neversoft-math-lib.md`
for the float-lib map.)

## 5. Cluster C - soundtrack / track engine (0x8011D588 - 0x8011E0E4)

THUG2's selectable soundtrack exposes a "track" query object. This cluster is
the **only** user of the two 64-bit shift helpers (§1), which sit in the
MSL zone:

| Fn | Size | Calls | Role |
|---|---|---|---|
| fn_8011D588 | 324 | `strcpy`, `strlen`, `strncpy` | track-name string handling |
| fn_8011D870 | 1048 | fn_80273B68, fn_80273480 | track engine (64-bit file/offset arithmetic) |
| fn_8011DC88 | 584 | fn_80273B68, fn_80273480 | track engine 2 |
| fn_8011E0E4 | 468 | fn_80273480, fn_80273B68 | track engine 3 |

`ScriptTrackEnabled` (the script wrapper for "is track N enabled") is the
other 64-bit-shift user - the cross-reference that nailed the cluster.

## 6. Cluster D - second voice pair (0x801354B4 - 0x80135E4C)

A second, smaller AX user (frontend / trick sounds):

| Fn | Size | SDK calls | Role |
|---|---|---|---|
| fn_801354B4 | - | `AXAcquireVoice` + fn_80279D78, fn_80279FCC, fn_80279C0C, fn_8027A1D8, fn_8027A024, fn_8027A134, fn_80279D2C, `AXRegisterCallback` | voice acquire + callback (mirror of fn_80122C40) |
| fn_801358F0 | - | `AXFreeVoice`, `AXRegisterCallback` | voice free + callback |
| fn_80135E4C | - | bl fn_8011E8D0, `ARQPostRequest` | stream copy + free old voice |

## 7. Cluster E - FMV movie player (0x80124C00 / 0x80124478)

`ScriptPlayMovie` -> fn_80124C00 (32 B) -> fn_80124478 (1820 B):

| Fn | SDK calls | Role |
|---|---|---|
| fn_80124478 | `VIConfigure`, `VIFlush`, `VIWaitForRetrace`, `GXSetZMode`, `GXSetColorUpdate`, `GXSetAlphaUpdate`, `DVDGetDriveStatus`, `AXRegisterCallback`, fn_80279CD0, `LCDisable`, `OSGetTick`, `memset`, `strlen`, `strncpy` | **movie player**: VI flip + GX clears + an AX callback for the movie's audio track |
| fn_80124B94 / fn_80124BD4 / fn_80124C20+ | - | player helpers / callbacks |

## 8. Non-audio interleaved neighbors (do not attribute!)

Because the sound code shares an address band with other systems, keep these
**out** of any audio split:

- fn_8011AC40 (atan2f), fn_8011AC94 (sinf), fn_8011ADD4 (2916 B, sqrtf) -
  physics/collision math (the float-lib users of the same band)
- fn_801226B4 / fn_801227CC / fn_801229CC / fn_80124110 - GX 2D rendering
  (Z-mode/tev/viewport/texture/clip)
- fn_80118000 - fn_80119470 - `ScriptMem*` / `ScriptLoad*` / timer / config /
  platform script wrappers
- fn_80124C20 - fn_80126FF4 - movie-helpers-to-misc accessor block (dozens of
  112-116 B same-shaped functions), fn_80125AEC group
- fn_801263A0 / fn_80126468 / fn_80126698 - SDK-lib helpers (fn_8026B04C,
  `strcpy`)

## 9. Script-facing entry points (named)

`ScriptPlaySound`, `ScriptStopStream`, `ScriptPlayMovie`, `ScriptTrackEnabled`
(also `ScriptPlaySkaterStream` at 0x80160CEC - check on next probe). These are
`scope:global`-style names in `symbols.txt`, safe to rename around.

## 10. Identification method (reproducible)

1. Chunked capstone full-text disasm (64-byte slices, try/except +4; plain
   `disasm` stops at the first invalid byte) - 590,040 insns.
2. `bl` call graph over `symbols.txt` function starts (`bisect_right` for
   "function containing address").
3. Seed = the named SDK audio entry points (`AXInit`, `AXQuit`,
   `AXAcquireVoice`, `AXFreeVoice`, `AXRegisterCallback`, `ARQPostRequest`,
   `ARInit`, `AIInit`, `ARGetBaseAddress`, ...), then L1/L2 caller closure
   (L1 = 22 fns, L2 = 47, spanning 0x80017C14-0x80204E30 - too broad to
   bound a region, hence the per-function inventory).
4. Per-region symbol dumps with size + SDK-call columns; head-of-function
   disasm for suspects (e.g. fn_80135E4C starts `bl 0x8011e8d0`).
5. Cross-reference shortcuts: shared runtime-helper users (fn_80273480 /
   fn_80273B68 cluster C), direct `bl` between clusters.

## 11. Follow-ups

- **Renames (decomp-quality names, keep `scope:global` convention):**
  Sound_Init / Sound_Shutdown / Sound_Play / Sound_PlayStream /
  Sound_StopStream / Sound_Voice_Alloc / Sound_Voice_Free /
  Sound_Callback_Register / Sound_Stream_DVDRead / Sound_Track_* /
  Movie_Play / Movie_PlayerInit.
- **Matching candidates (small GPR-only, no FPR frames - safe for the M5
  pipeline):** fn_8011E8D0 (96 B), fn_8011ECA0 (160 B), fn_8011BEAC (80 B),
  fn_80120924 (168 B), fn_801210C4 (180 B), fn_8012156C (184 B), the
  fn_8001D4FC/D668 twins.
- **SDK wiring (future):** the AX module (0x802773A0-0x8027A3BC) is the only
  audio SDK region the game calls into; it is a bfbb-era copy - when wiring
  `libs/dolphin`, prefer the tww/bfbb Sep-2002 sources per the §4b-SDK recipe
  and verify per-function sizes against `symbols.txt` first.
- **Open question:** ARAM buffer addresses are not materialized as
  `lis 0x20000000` anywhere in game code - stream buffers must be addressed
  via `ARGetBaseAddress` (fn_8001D768) or a cached global from the bootstrap.