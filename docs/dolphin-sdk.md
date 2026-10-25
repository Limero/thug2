# Dolphin SDK — version, sources, and adaptation strategy

**Status:** investigation complete, DOL-verified (2026-08-14).
**Reference bases surveyed (2026-08-15):** two new SDK snapshots verified -
**tww's SDK is the exact Sep 5 2002 base** (version strings byte-identical to
thug2's DOL for all 8 base modules) and **bfbb's is an Apr 17-22 2003 rebuild**
(closest existing source for thug2's Mar-2003 AX/EXI and Feb-2003 GX drift
modules). See §6.1 for the per-module reference map.
**Wiring progress:** `os/OSAlarm.c`, `os/OSInterrupt.c`, `os/OSThread.c`,
`os/OSTime.c`, `os/OSError.c`, `os/OSContext.c`, `os/OSMutex.c`, `os/OSArena.c`,
`os/OSMemory.c`, `os/OSSync.c`, `os/OSResetSW.c`, `os/OSReset.c`, `os/OSRtc.c`,
`os/OS.c` are wired and byte-exact (M8.78–M8.90); the remaining modules are still
asm-carried.
**Companion to:** `docs/gamecube-decomp-plan.md` §5 (compiler = ProDG vs mwcc). This doc is
about the *SDK library* the game links against, not the compiler.

---

## tl;dr

- thug2 links the **Dolphin SDK library version `0x2301`**, built across
  **Sep 5 2002 → Mar 17 2003** (see table below).
- `libs/dolphin/` in this repo is a **byte-identical copy of zeldaret/tp's SDK**,
  which is the *same* `0x2301` but a **2004 build** — ~1 year newer.
- Because the SDK grows mostly by **adding** functions, the 2004 sources are
  effectively a *superset* of thug2's DOL. Adapting = **deletion + small edits**,
  not reconstruction.
- **Decision:** keep tp's SDK as the base (it is the most complete available);
  per-module, revert the post-March-2003 additions.

---

## 1. thug2's SDK version (read from the DOL rodata)

Every Dolphin module registers a version string via `OSRegisterVersion`. They are
all present in `main.dol` rodata as `"<< Dolphin SDK - <MOD>\trelease build: ... (0x2301) >>"`.

| Module | Build date | Note |
|---|---|---|
| DVD | `Oct 29 2002 09:56:49` | |
| VI / PAD / AR / ARQ / AI / CARD / DSP / SI | `Sep  5 2002` | base modules |
| **OS** | `Mar 17 2003 04:20:41` | updated |
| **GX** | `Feb  7 2003 04:01:13` | updated |
| **AX** | `Mar 11 2003 11:19:39` | updated |
| **EXI** | `Mar 11 2003 11:19:00` | updated |

So thug2's SDK is a **mix**: a Sep-2002 base with OS/GX/AX/EXI pulled up to
Feb–Mar 2003. The `0x2301` marker is the SDK *library* version and does not change
across these builds — it is the standard retail SDK value (it appears in DIOS MIOS /
Devolution logs and Dolphin forum dumps for many games).

### Reproduce

```bash
# extract every SDK version string from the DOL
tools/venv/bin/python - <<'PY'
import sys, re
sys.path.insert(0, 'tools')
import gen_leaves as gl
for m in re.finditer(rb'<< Dolphin SDK[^\x00]*', gl.d):
    print(m.group(0).decode('ascii'))
PY
```

---

## 2. The source situation: `libs/dolphin` is tp's 2004 build

`libs/dolphin/src/os/OS.c` is a byte-identical copy of zeldaret/tp's, and its
version macro is **2004**, not thug2's March 2003:

```c
#define BUILD_DATE  "Apr  5 2004"   // (also May 21 2004 / Nov 10 2004, per tp version)
const char* __OSVersion = "<< Dolphin SDK - OS\trelease build: "BUILD_DATE" "RBUILD_TIME" (0x2301) >>";
```

`libs/dolphin/src/gx/GXInit.c` is likewise `Apr 5 2004` / `Nov 10 2004`.

**Consequence:** the same `0x2301` SDK, but ~1 year of API evolution between
thug2's build and the sources. Only the *core* functions are byte-identical; the
newer APIs don't exist in thug2's DOL.

---

## 3. Verified mismatches (thug2 DOL vs the tp sources)

### 3.1 `OSAlarm.c` — disassembly-verified

`OSInitAlarm` at 0x80262908 is 0x4C bytes and its tail saves the link register, stages 8 into r3, creates an 8-byte frame and calls the exception-handler getter, then materializes the decrementer-handler address, compares it against the current handler and returns on equal, otherwise zeroes the alarm-queue tail and head words, stages 8 into r3 and calls the exception-handler setter, with no reset-function registration (the source adds a trailing reset registration call that would extend it to 0x58).

Other `OSAlarm.c` differences:
- **`OSSetPeriodicAlarm`** (tp 0x7C) — **absent** from thug2.
- **`OnReset`** (tp 0xA0) — **absent** (dead-code-eliminated because the reset
  function is never registered).
- 5 of 8 functions (`OSCreateAlarm`, `InsertAlarm`, `OSSetAlarm`, `OSCancelAlarm`,
  `DecrementerExceptionCallback`/`Handler`) are byte-identical.

### 3.2 `OSThread.c` / `OSTime.c` — size-sequence verified

thug2's thread+time block is `0x80266644`–`0x80267C54` (**0x1610** bytes) vs tp's
`0x80340AA4`–`0x80342B78` (**0x20D4** bytes). The ~0xAC4 gap is exactly the missing
functions:

- `OSSetSwitchThreadCallback` (0x74)
- `__OSPromoteThread` (0x50)
- `OSYieldThread` (0x3C)
- `OSDetachThread` (0xA0)
- `OSSetThreadPriority` (0xC0)
- `OSGetThreadPriority` (0x8)
- `CheckThreadQueue` (0x9C)
- `OSCheckActiveThreads` (0x750)
- `__OSTimeToSystemTime` (0x58)
- `OSIsThreadTerminated` is **0x1C** (thug2) vs **0x34** (tp) — one fewer comparison.

The core (`OSCreateThread` 0x1E8, `OSResumeThread` 0x288, `OSSuspendThread` 0x170,
`OSSleepThread` 0xEC, `OSWakeupThread` 0x104, `__OSGetSystemTime` 0x64, …) matches.

### 3.3 `OS.c` — tentative

`OSInit` is **0x3D8** (thug2 `0x802620D0`) vs **0x4E0** (tp), and there is an extra
0x128-byte function before it that has no tp counterpart. The *tail* of `OS.c`
(`OSExceptionInit` → `OSRegisterVersion`) maps cleanly; the head needs a closer look.
Do not treat the `OS.c` head mapping as final until it is disassembly-verified.

---

## 4. thug2 OS function address map (`fn_` → SDK name)

Useful for the eventual "wire up `os/` + rename `fn_8026xxxx` → `OS*`" pass. All
addresses are from `config/G2TE52/symbols.txt`.

### `OSAlarm.c` + `OSArena.c` (solid)

| Address | Name | Size |
|---|---|---|
| `0x80262908` | `OSInitAlarm` | 0x4C |
| `0x80262954` | `OSCreateAlarm` | 0x10 |
| `0x80262964` | `InsertAlarm` | 0x250 |
| `0x80262BB4` | `OSSetAlarm` | 0x68 |
| `0x80262C1C` | `OSCancelAlarm` | 0x11C |
| `0x80262D38` | `DecrementerExceptionCallback` | 0x230 |
| `0x80262F68` | `DecrementerExceptionHandler` | 0x50 |
| `0x80262FB8` | `OSGetArenaHi` | 0x8 |
| `0x80262FC0` | `OSGetArenaLo` | 0x8 |
| `0x80262FC8` | `OSSetArenaHi` | 0x8 |
| `0x80262FD0` | `OSSetArenaLo` | 0x8 |

### `OSSync.c` + `OSThread.c` + `OSTime.c` (solid)

| Address | Name | Size |
|---|---|---|
| `0x802665C0` | `SystemCallVector` | 0x20 |
| `0x802665E0` | `__OSInitSystemCall` | 0x64 |
| `0x80266644` | `DefaultSwitchThreadCallback` | 0x4 |
| `0x80266648` | `__OSThreadInit` | 0x158 |
| `0x802667A0` | `OSInitThreadQueue` | 0x10 |
| `0x802667B0` | `OSGetCurrentThread` | 0xC |
| `0x802667BC` | `OSIsThreadTerminated` | 0x1C |
| `0x802667D8` | `OSDisableScheduler` | 0x40 |
| `0x80266818` | `OSEnableScheduler` | 0x40 |
| `0x80266858` | `UnsetRun` | 0x68 |
| `0x802668C0` | `__OSGetEffectivePriority` | 0x3C |
| `0x802668FC` | `SetEffectivePriority` | 0x1C0 |
| `0x80266ABC` | `SelectThread` | 0x228 |
| `0x80266CE4` | `__OSReschedule` | 0x30 |
| `0x80266D14` | `OSCreateThread` | 0x1E8 |
| `0x80266EFC` | `OSExitThread` | 0xE4 |
| `0x80266FE0` | `OSCancelThread` | 0x1BC |
| `0x8026719C` | `OSResumeThread` | 0x288 |
| `0x80267424` | `OSSuspendThread` | 0x170 |
| `0x80267594` | `OSSleepThread` | 0xEC |
| `0x80267680` | `OSWakeupThread` | 0x104 |
| `0x80267784` | `OSClearStack` | 0xAC |
| `0x80267830` | `OSGetTime` | 0x18 |
| `0x80267848` | `OSGetTick` | 0x8 |
| `0x80267850` | `__OSGetSystemTime` | 0x64 |
| `0x802678B4` | `GetDates` | 0x19C |
| `0x80267A50` | `OSTicksToCalendarTime` | 0x204 |

### `OS.c` (tentative head; tail is solid)

| Address | Name | Size | Confidence |
|---|---|---|---|
| `0x80261E1C` | `__OSFPRInit` | 0x128 | tentative |
| `0x80261F44` | `OSGetConsoleType` | 0x28 | tentative |
| `0x80262094` | `InquiryCallback` | 0x3C | tentative |
| `0x802620D0` | `OSInit` | 0x3D8 | tentative (size ≠ tp 0x4E0) |
| `0x802624A8` | `OSExceptionInit` | 0x280 | solid |
| `0x80262728` | `__OSDBIntegrator` | 0x24 | solid |
| `0x8026274C` | `__OSDBJump` | 0x4 | solid |
| `0x80262750` | `__OSSetExceptionHandler` | 0x1C | solid |
| `0x8026276C` | `__OSGetExceptionHandler` | 0x14 | solid |
| `0x80262780` | `OSExceptionVector` | 0x9C | solid |
| `0x8026281C` | `OSDefaultExceptionHandler` | 0x58 | solid |
| `0x80262874` | `__OSPSInit` | 0x54 | solid |
| `0x802628C8` | `__OSGetDIConfig` | 0x14 | solid |
| `0x802628DC` | `OSRegisterVersion` | 0x2C | already named |

> Note: there is an unplaced 0x128-byte function at `0x80261F6C` and the `OSInit`
> size mismatch — resolve these by disassembly before trusting the `OS.c` head.

---

## 5. SDK evolution timeline

```
Sep  5 2002   base modules (VI/PAD/AR/AI/CARD/DSP/SI)     ← shared by WW-era + thug2
Oct 29 2002   DVD
Feb  7 2003   GX                                           ← thug2's build
Mar 11 2003   AX / EXI                                     ← thug2's build
Mar 17 2003   OS                                           ← thug2's build  (the gap)
Apr 17-22 2003  bfbb (SpongeBob BFBB) — full rebuild of 0x2301 (see §6.1)
Apr–Jul 2003  OSAlarm + OSThread API additions             ← OSSetPeriodicAlarm, full thread set
Jul 23 2003   mkdd (Mario Kart DD)
Nov 26 2003   pikmin2
Apr–Nov 2004  tp                                            ← the sources in libs/dolphin
```

---

## 6. Other decomp bases compared

| Base | OS build | Completeness vs tp |
|---|---|---|
| **tp** (in-repo) | Apr–Nov 2004 | **37 modules, all decompiled** — os 31, gx 21, ax 10+7+6, card 20, … |
| **tww** (in-repo) | **Sep  5 2002** | **the exact Sep-2002 base** — all 8 base modules present with version strings byte-identical to thug2's DOL (verified 2026-08-15); no `ax` dir (WW doesn't link it) |
| **bfbb** (in-repo) | **Apr 17–22 2003** | full SDK (incl. `ax`, `gx`); **too new for OS** (already has the post-Mar-2003 `OSSetPeriodicAlarm`/`OSPromoteThread` additions); closest source for AX/EXI/GX-drift |
| mkdd | Jul 23 2003 | GX **empty (0-byte placeholders)**, AX **missing**, os 22 files |
| pikmin2 | Nov 26 2003 | newer than thug2 anyway |
| melee / dolsdk2001 | 2001 | too old |

No decomp exists at thug2's *exact* composite build (Sep 2002 base + Feb/Mar
2003 OS/GX/AX/EXI). The reference map in §6.1 picks, per module, the closest of
the three available snapshots (tww = Sep-2002, bfbb = Apr-2003, tp = 2004);
**tp remains the most complete overall** and the only one with every module.

mkdd is only worth keeping cloned as a secondary cross-reference for the base
modules (`card`/`pad`/`si`/`vi`), where its Apr–Jul 2003 build *may* need slightly
less reverting than tp's 2004 build. It is **not** a replacement base — it has no GX.

---

## 6.1 Reference map (surveyed 2026-08-15, all mwcc GC/1.2.5n)

Three in-repo SDK snapshots bracket thug2's composite build (Sep-2002 base +
Oct-2002 DVD + Feb/Mar-2003 GX/AX/EXI/OS). For each module, the closest
source wins: tww needs **zero** adaptation for the base modules (its version
strings match thug2's DOL byte-for-byte, and §8.9 already proved
`SIBios.c` compiles byte-identical); bfbb is ~1 month newer than thug2's
Mar-2003 refreshes vs ~1 year for tp.

| thug2 module | thug2 build | best reference | why |
|---|---|---|---|
| VI / PAD / AR / ARQ / AI / CARD / DSP / SI | Sep  5 2002 | **tww** | version strings byte-identical to DOL; code compiles byte-exact (§8.9) |
| DVD | Oct 29 2002 | **tp** (or mkdd/bfbb as secondary) | no snapshot at exactly Oct-2002; compare per-function, pick least-revert |
| GX (stable core) | Feb  7 2003 | tww (already wired M8.105–106) | GXDisplayList/GXStubs wire from tww's Sep-2002; **GXInit 4/5 wired** (only `GXInit` main stays auto-asm — Feb-2003-only revision, see docs/parkings/21-gxinit.md) |
| GX (drift: GXFifo/GXAttr/GXPerf) | Feb  7 2003 | **bfbb** | closest to Feb-2003; tp = 2004 enums/ASSERTMSGLINE, tww = pre-add |
| AX / EXI | Mar 11 2003 | **bfbb** | Apr 17 2003 = 1 month drift vs tp's 1 year; expect only version-string edit |
| OS | Mar 17 2003 | tp (already wired, reverts done M8.78–90) | bfbb too new (has post-Mar-2003 additions) |
| DB / base / MetroTRK | – | tp (already wired) | trivial slivers |

BFBB notes: `src/bink`, `src/rwsdk`, `src/SB` are engine/libraries thug2 does
not link (no Bink/RenderWare strings in the DOL) — skip. `eth.c` in bfbb is an
Aug 5 2003 module (thug2 doesn't link ETH). Repo: `bfbbdecomp/bfbb`
(SpongeBob: Battle for Bikini Bottom, GQPE78, Dolphin hash
`306526d90b48e99894c3138f5fc8f2716d9fecf6`), cloned at `../bfbb`.

---

## 7. Decision and strategy

1. **Keep tp's SDK as the base.** Most complete; covers every module thug2 links.
2. The SDK grows by **addition**, so the newer tp sources are mostly a *superset* of
   thug2's DOL. Per module: diff thug2's DOL disassembly against tp's source and
   **revert** the post-March-2003 deltas (delete added functions + small edits).
3. Example (verified): `OSAlarm.c` = 5/8 functions byte-identical; revert =
   delete `OSSetPeriodicAlarm` + `OnReset`, drop one line from `OSInitAlarm`.
4. The reverse (an older 2002 SDK + re-adding thug2's Mar-2003 functions) is harder
   and those bases aren't complete anyway.

### Wire-up order

**Done (M8.78–M8.89):** `os/OSAlarm.c`, `os/OSInterrupt.c`, `os/OSThread.c`,
`os/OSTime.c`, `os/OSError.c`, `os/OSContext.c`, `os/OSMutex.c`, `os/OSArena.c`,
`os/OSMemory.c`, `os/OSSync.c`, `os/OSResetSW.c`, `os/OSReset.c`, `os/OSRtc.c` —
all byte-exact, DOL byte-clean.

**Note on `os/OSMutex.c` (M8.83):** only `__OSUnlockAllMutex` (0x70 @ 0x80267D5C)
is actually linked in thug2. The other 10 OSMutex.c functions (`OSInitMutex`,
`OSLockMutex`, `OSUnlockMutex`, `OSTryLockMutex`, `OSInitCond`, `OSWaitCond`,
`OSSignalCond`, `__OSCheckMutex`, `__OSCheckDeadLock`, `__OSCheckMutexes`) are
**dead-code-eliminated** — thug2's game code does its own queue/event management
by calling `OSSleepThread`/`OSWakeupThread`/`OSInitThreadQueue` directly on its
own structures (e.g. `fn_80018400`, `fn_8001867C` @ 0x8031E7xx), so no pre-
`__OSPromoteThread` revert was needed. The tp source was reduced to the single
function that survives.

**Note on `os/OSMemory.c` (M8.85):** only 6 of the ~9 functions are actually
linked in thug2 — `OSGetPhysicalMemSize`/`OSGetConsoleSimulatedMemSize` get
inlined into `__OSInitMemoryProtection`, and `OSProtectRange` is dead-code-
eliminated, so the tp source was reduced to `OnReset`, `MEMIntrruptHandler`,
`Config24MB`/`Config48MB`/`RealMode` (asm) and `__OSInitMemoryProtection`.
thug2's build reads the simulated/physical size from `__OSSimulatedMemSize`/
`__OSPhysicalMemSize` (`AT_ADDRESS` MMIO globals at 0x800000F0/0x28), and
`__OSInitMemoryProtection` needs `padding[11]` + `size` declared before
`enabled` to match thug2's register allocation (0x50 frame, `size`→r31).

**Note on `os/OSResetSW.c` (M8.87):** only 3 of the 5 tp functions are linked —
`OSGetResetSwitchState` (trivial wrapper) and `__OSSetResetButtonTimer` are
dead-code-eliminated. The three linked functions (`__OSResetSWInterruptHandler`,
`OSSetResetCallback`, `OSGetResetButtonState`) map to `fn_802656B8`/`fn_802657AC`/
`fn_80265820` (`.text 0x802656B8–0x80265AB8`, `.sbss 0x803CAC70–0x803CAC90`), and
the 5 statics land r13-relative (`ResetCallback` −0x7610, `Down` −0x760c,
`LastState` −0x7608, `HoldUp` −0x7600, `HoldDown` −0x75f8). One Mar-2003 build
diff from tp: the reset-button timer mask is `& 0x3F` (not tp's `& 0x1F`).
Wiring it also required naming `__OSStartTime` (`.sbss 0x803CAC28`, defined in
`os/OS.c`) so the linker could resolve `OSGetResetButtonState`'s reference.

**Note on `os/OSReset.c` (M8.88):** the 5 linked functions (`OSRegisterResetFunction`,
`__OSCallResetFunctions`[static], `Reset`[asm], `__OSDoHotReset`, `OSResetSystem`,
`OSGetResetCode`) map to `.text 0x802652C4–0x802656B8` with `.sbss 0x803CAC68–0x803CAC70`
(`ResetFunctionQueue`). thug2's Mar-2003 `OSResetSystem` inlines everything into one
function (no `__OSShutdownDevices`/`KillThreads`/`OSUnregisterResetFunction`/`OSSetBootDol`
like tp) and reads the reset code from `__PIRegs[9]` (not `__OSRebootParams`). It needs
a `u32 unk[4]` dummy local to force the 0x40 frame (`stmw r26,0x28(r1)`), same trick as
mkdd's `u32 unk[3]; // dumb compiler`. Wiring it also named the callees `__OSStopAudioSystem`,
`ICFlashInvalidate`, `LCDisable`, `__OSLockSram`, `__OSUnlockSram`, `__OSSyncSram` (the last
three belong to `os/OSRtc.c`).

**Note on `os/OSRtc.c` (M8.89):** 17 of tp's 34 functions are linked (the RTC,
`__OSReadROM*`, video-mode, sound-mode-setter, language-setter, boot-mode, and
`__OSCheckSram`/GbsMode functions are dead-code-eliminated; `ReadSram` and `LockSram`
are inlined). Map to `.text 0x80265AB8–0x802665C0` + `.bss 0x803AE280–0x803AE2D4`
(`Scb`, 0x54 @ align:32). Two Mar-2003 diffs from tp: `__OSInitSram` drops the
`OSSetGbsMode(OSGetGbsMode())` tail (0x134 not 0x13C), and `UnlockSram` drops the
`if (Scb.offset <= 0x14) { gbs = 0 }` block (0x308 not 0x33C) so `WriteSram` inlines
into it. `ReadSram`/`LockSram` must be declared `static inline` — plain `static` makes
mwcc 1.2.5n emit standalone copies (extra 0x11c/0x68 .text) even though it also inlines
them. Wiring named the 8 EXI callees `EXIImm`/`EXIImmEx`/`EXIDma`/`EXISync`/
`EXISelect`/`EXIDeselect`/`EXILock`/`EXIUnlock` (size-matched vs tp: 0x25C/0xA0/0xEC/
0x24C/0x12C/0x110/0xF4/0xDC).

**Next:** `os/OS.c` (head still needs disassembly verification — see §3.3), then
the EXI library (`os/EXIBios.c`/`os/EXI.c` — the `EXIImm`/`EXIImmEx`/`EXIDma`/
`EXISync`/`EXISelect`/`EXIDeselect`/`EXILock`/`EXIUnlock` callees named in M8.89).

Each step: map addresses (§4) → `splits.txt` + `DolphinLib("os", [...])` in
`configure.py` → rename `fn_8026xxxx` → verify DOL byte-clean. Read §8 first —
two wiring gotchas will otherwise bite.

---

## 8. Wiring gotchas (learned wiring OSAlarm/OSInterrupt/OSThread)

The `os/` modules are wired via `DolphinLib("os", [...])` in `configure.py`
(`cflags_dolphin`, `-D__GEKKO__`, MSL headers copied from `../tp`, and the
`__div2i` thunk rename). Two non-obvious bugs surfaced during the first three
modules and will recur on the rest — check for them whenever a newly wired
module's data sections don't line up byte-for-byte.

### 8.1 `_stack_end` must be the END of `.sdata2`, not its start

`config/G2TE52/ldscript.tpl` hardcodes `_stack_end`. It was `0x803CAF80` — the
*start* of the `.sdata2` section — which makes `__start` compute the wrong
initial stack pointer:

```c
_stack_end  = 0x803CAF80;                         // WRONG (start of .sdata2)
_stack_addr = (_stack_end + 0xFFFF + 0x7) & ~0x7; // -> 0x803DAF80

_stack_end  = 0x803CC200;                         // RIGHT (end of .sdata2, +0x1280)
_stack_addr = (_stack_end + 0xFFFF + 0x7) & ~0x7; // -> 0x803DC200
```

The original `__start` does `lis r1, 0x803d; ori r1, r1, 0xc200` → `0x803DC200`,
so only `0x803CC200` reproduces it. This was wrong since the very first commit,
but it stayed masked until `os/OSThread.c` took over the `.bss` region — see 8.2.
It shows up as exactly 4 stray words in a DOL diff: `__start`'s
`ori r1, r1, _stack_addr@l` plus three `addi` sites referencing `_stack_addr`.

### 8.2 Stray m2c `static` declarations emit phantom `.bss` that shifts layout

Some promoted `src/fn_*.c` files carry an m2c artifact like:

```c
static s32 spC;                    // <-- phantom file-scope static (m2c's "sp+0xC")
s32 Func(...) { void *spC; ... }   // local shadows it; the file-scope one is dead
```

The dead `static s32 spC;` still emits a 4-byte `.bss` object. When a compiled
SDK module with an 8-aligned `.bss` (e.g. `os/OSThread.c`'s `RunQueue`) lands
right after it, the linker pads up to the 8-byte boundary and **every later
`.bss` symbol shifts up 8 bytes** — surfacing as hundreds of `addi` diffs (disp
+8) across `.text` plus `.data`/`.sdata2` pointers off by 8. Fix: delete the dead
static. Grep for the pattern with:

```bash
grep -rnE '^static (s32|u32|s16|u16|u8|s8|f32|f64|void \*) sp[A-F0-9];' src/fn_*.c
```

(Only `fn_800A63F8.c` had one as of M8.79, but the pattern can reappear from
`tools/gen_wip_drafts.py` on future promotions.)

### 8.3 Varargs callers must keep `...` — dropping it removes the `crclr`

When renaming an asm-carried `fn_8026xxxx` that is actually varargs (e.g.
`OSPanic`, which is `void OSPanic(const char*, int, const char*, ...)`), update
its *existing* C callers with the same `...` in the prototype. `OSPanic`'s
game-code callers (`fn_801225F8.c`, `fn_80122648.c`) were declared non-prototype
(`void fn_802640E4();`) so they emit the varargs `crclr 4*cr1+eq` before the
`bl`. Re-declaring them as a fixed-arg prototype
`void OSPanic(const char *, int, const char *);` silently **drops the 4-byte
`crclr`** from each call site, so every `.text` object after them shifts down 4
bytes per call — which then cascades 8 bytes through `.rodata`/`.data` and
another 8 into `.sdata` (via `ALIGN(0x10)`), and `tools/patch_dol.py` fails with
`Init r2 setup computes 0x... expected 0x...`. Symptom: `patch_dol` r2 mismatch
with no obvious data-size error, plus those callers dropping to ~95% fuzzy.
Keep `void OSPanic(const char *, int, const char *, ...);` (or the non-prototype
form) and the DOL returns to byte-clean.

### 8.4 `(u32)double` casts pull in the `__cvt_fp2unsigned` runtime helper

`os/OSContext.c`'s `OSDumpContext` prints FPU regs with `(u32)context->fpr[i]`,
which compiles to a call to the Metrowerks runtime `__cvt_fp2unsigned` (double →
unsigned). That helper is asm-carried at `0x8025CFB4` (size `0x48`), sitting in
the same runtime thunk cluster as `__div2i`/`__mod2i` (`0x8025D000`), and was
previously an unnamed `lbl_8025CFB4`. Wiring the module fails to link with
`undefined: '__cvt_fp2unsigned'` until you rename that label to a
`type:function size:0x48 scope:global` symbol. Grep the whole runtime cluster
for float-ops (`fctiwz`) when a float/unsigned cast shows up in a future module.

### 8.5 `__ArenaLo` is `_stack_addr + 0x20`, not `_db_stack_addr`

`config/G2TE52/ldscript.tpl` previously computed `__ArenaLo = (_db_stack_addr +
0x1f) & ~0x1f` (= `0x803DE200`), following tp/mkdd's script. thug2's original DOL
computes `__ArenaLo = 0x803DC220` in `OSInit`'s `lis -0x7fc2; addi -0x3de0`,
which is `_stack_addr (0x803DC200) + 0x20` — i.e. the arena starts right above
the boot stack, with no separate 0x2000 debugger stack between them. Fix:
`__ArenaLo = _stack_addr + 0x20;`. Only `os/OS.c` references it, so this stayed
masked until the module was wired. Same check applies to `__ArenaHi` if a later
module turns out to reference it.

### 8.6 `.data` regions mix dead strings from OTHER SDK objects

`os/OS.c`'s `.data` is `0x803090E8..0x803092E0` (0x1F8: banner, OSInit report
strings, `__OSExceptionLocations`, DBPrintf strings) — but the original region
runs to `0x803094C8`. The tail `0x803092E0..0x803094C8` is **OSAlarm.c's**
`OSCheckAlarmQueue` assert strings (dead in the linked build: zero lis+addi refs
in `.text`). Don't claim the whole blob for OS.c: keep the split `.data` end at
the last OS.c string and leave the tail auto-covered. Also note the linker pads
`.data` to 4-byte alignment (OSContext's 0x1D7 object fills a 0x1D8 split), so a
1-byte tail pad (`0x1F7` object → `0x1F8` split) is expected and fine.

### 8.8 Fixed-address MMIO globals MUST be `AT_ADDRESS` externs, not `volatile` casts

Wiring `os/OSReboot.c` (M8.91): the init block writes five fixed addresses
(`0x817FFFFC`/`0x817FFFF8`/`0x800030E2`/`0x812FDFF0`/`0x812FDFEC`). Written as
`*(volatile u32*)0x817FFFFC = 0;` the compiler schedules the stores/loads in a
completely different order than WANT (loads of `SaveStart`/`SaveEnd` deferred,
regalloc swapped). Declaring them like mkdd does —
`extern u32 UNK_817FFFFC AT_ADDRESS(0x817FFFFC);` and then plain
`UNK_817FFFFC = 0;` — reproduces WANT exactly. Use the `AT_ADDRESS` extern form
for every fixed-address access inside SDK sources; `volatile` pointer casts
break mwcc's scheduler/allocator vs the original build.

### 8.7 `.sbss` globals emit in REVERSE declaration order

`os/OS.c`'s statics (`BootInfo`, `BI2DebugFlag`, ...) land in `.sbss` in
declaration order, but the **non-static globals** (`__OSSavedRegionEnd`,
`__OSSavedRegionStart`, `__OSInIPL`, `__OSStartTime`) emit in *reverse*
declaration order. To reproduce the original addresses, declare them reversed
(`__OSStartTime` first, `__OSSavedRegionEnd` last). A wrong order shows up as
`.sbss` entries at shifted offsets plus an r2/r13 displacement diff in every
function that touches them.

### 8.9 SI: wired from tww Sep-5-2002 — hybrid extern route, NOT a revision gap

SI (`si/SIBios.c` + `si/SISamplingRate.c`) is wired byte-exact from **tww's
Sep-5-2002 sources** (same version string). The earlier "different SDK
revision / pre-vcount" conclusion in this section was wrong on both counts:
- the "revision gap" came from a **truncated disassembly** — thug2's retail
  `SIInterruptHandler` DOES have the RDST `InputBufferVcount` /
  `VIGetCurrentLine` polling block (at 0x80281B90..0x80281D00);
- the "0 structural diffs" that preceded it came from **stale orphan objects**
  (missing compile rules), the same false-positive trap as PAD.

Compiling tww's unmodified source with our flags reproduces **every retail
function size exactly** (CompleteTransfer 0x2FC, SIInterruptHandler 0x344,
SIGetResponse 0xC4, SITransfer 0x16C, GetTypeCallback 0x298, SIInit 0xB4,
SIEnablePollingInterrupt 0x98, SISetSamplingRate 0xE4, …). `SIDecodeType`/
`SIProbe`/`SIGetTypeString` are dead in thug2 (stripped at link) but must stay
in the source — they own the type-name strings that survive in retail `.data`.

**The extern-route lesson that unlocked it (see also 8.14):** externing the
big `.data`/`.bss` statics (`Si`, `Packet`, `Alarm`, `Type`, `TypeTime`,
`XferTime`, `TypeCallback`, `RDSTHandler`, `InputBuffer*`, `cmdFixDevice`)
**changes register allocation and breaks the .text codegen** (frame sizes,
`stmw` spans, load order all drift). Only the small 4-aligned `.sbss`/`.sdata`
scalars are safe to extern — they are only address-taken/`@sda21` referenced,
so codegen is identical. Final recipe:
1. Keep `.data` (version string + `Si` + `Type` + type-name strings) and `.bss`
   (Packet..cmdFixDevice) as **statics**, claimed in the split at 0x8030F780
   and 0x803C85C0 (both 8-aligned — no mwld bump).
2. Extern the 4-not-8-aligned `.sbss`/`.sdata` symbols back to auto-asm:
   `SIInterruptHandler_cmdTypeAndStatus` @ 0x803CAE80,
   `SIGetType_cmdTypeAndStatus` @ 0x803CAE84, `__PADFixBits` @ 0x803CAE88
   (all in auto unit `auto_07_803CAE7C_sbss`, `scope:global`), and
   `SamplingRate` @ 0x803CAE90 (`scope:global` — dtk then auto-covers it).
3. `__SIVersion` is special: the **pointer** is `.sdata` @ 0x803CA9A8
   (4-aligned → extern), but the **string** must stay in `.data` at 0x8030F780
   so the claimed region stays byte-exact AND the auto `.sdata` unit's
   `__SIVersion` relocation (`lbl_8030F780`) resolves. Emit it as a
   `force_active` **global** named `lbl_8030F780`:
   ```c
   extern const char* __SIVersion;
   #pragma push
   #pragma force_active on
   char lbl_8030F780[] = "<< Dolphin SDK - SI\trelease build: ... >>";
   #pragma pop
   ```
   (`static const char[]` goes to `.rodata` — wrong section; non-const array
   goes to `.data`.)
4. `SISamplingRate.c` needs a **4-byte `XY` struct** (`{u16 line; u8 count;
   u8 pad;}`) — retail indexes the tables with stride 4 (`slwi rN, msec, 2`).
   tww's 3-byte struct is a later-compiler artifact; our mwcc 1.2.5n needs the
   pad byte.

**Split ranges (verified, DOL byte-clean):** SIBios.c `.text`
0x80281678..0x80282D68, `.data` 0x8030F780..0x8030F898, `.bss`
0x803C85C0..0x803C87C0; SISamplingRate.c `.text` 0x80282D68..0x80282E70,
`.data` 0x8030F898..0x8030F930 (XYNTSC 0x30 + XYPAL 0x30 + OSReport string).
No `.sdata`/`.sbss` claims (extern route).

### 8.11 Unreferenced-but-present SDK fns/globals need `#pragma force_active on`

When wiring AR/ARQ, mwld dead-stripped two global functions thug2's DOL keeps
(`__ARClearInterrupt` @ `0x80274EAC`, `__ARGetInterruptStatus` @ `0x80274ECC`)
plus the `__ARQRequestQueueTemp`/`__ARQRequestTailTemp` `.sbss` slots. Nothing in
the game calls them — they survive in the retail DOL because the original mwld
link didn't strip them (or they were `force_active`). The symptom is a 48-byte
`.text` deficit that cascades a 40-byte `.sdata2` base shift, failing
`patch_dol.py`'s `Init r2 setup computes 0x…, expected 0x…` assert.

Fix (same mechanism `dvd.c` already uses for orphan data):
```c
#pragma push
#pragma force_active on
void __ARClearInterrupt(void) { ... }
u16 __ARGetInterruptStatus(void) { ... }
#pragma pop
```
and, for the orphan `.sbss` statics:
```c
#pragma push
#pragma force_active on
static ARQRequest* __ARQRequestQueueTemp;
static ARQRequest* __ARQRequestTailTemp;
#pragma pop
```
This restores the exact `.text`/`.sbss` sizes and the DOL is byte-clean.

**Same-deficit trap: call the LOCAL thunk, not the SDK name it wraps.**
`fn_80016E18` (`0x80016E18`, 148 B) calls the four 32-byte GX thunks
`fn_800203D4` / `fn_800203F4` / `fn_80020414` / `fn_80020434`, whose bodies are
just `GXSetTexCopySrc()` / `GXSetTexCopyDst()` / `GXCopyTex()` /
`GXPixModeSync()`. `/dev/stdin`-style drafts that name the SDK functions score
**100% (EXACT)** — `bl` targets are relocation-masked, so the compare cannot
tell which callee is referenced — but promoting that spelling leaves the four
thunks with zero callers and mwld dead-strips all 0x80 bytes of them: `.text
shrinks by 0x80`, every later section shifts, and `patch_dol.py` aborts with
`Init r2 setup computes 0x803D2F00, expected 0x803D2F80`. Declaring the thunks
locally with their real argument shapes
(`void fn_800203D4(u16,u16,u16,u16);` … — the `src/` definitions are `(void)`,
so the registers simply pass through) keeps them reachable and the DOL
byte-clean. **Rule: a masked 100% is not a link outcome.** Before promoting a
body whose calls were recovered from `bl` sites, confirm the referenced symbol
has other callers, or the promotion will silently delete it.

### 8.10 `DBPrintf` is NOT a drift — the empty `{...}` stub is 0x50 bytes

An earlier session misread thug2's `DBPrintf` (0x50 bytes) as a "real
implementation" that drifts from tww/mkdd/tp's `void DBPrintf(char* str, ...) {}`.
It isn't: at `-O4,p` (cflags_dolphin) MWCC still emits the full varargs-homing
prologue for an empty variadic body — `stwu r1,-0x70` + `bne cr1` + `stfd
f1..f8` + `stw r3..r10` + `addi r1,r1,0x70` + `blr`. The empty source compiles
to exactly the 0x50 bytes in the DOL (verified by compiling tww's stub
standalone and diffing). **db/db.c is wired byte-exact** — all 5 functions
(DBInit 0x28, __DBExceptionDestinationAux 0x48, __DBExceptionDestination 0x10,
__DBIsExceptionMarked 0x1C, DBPrintf 0x50) + `.data` 0x803090D0..0x803090E8 +
`.sbss` 0x803CABE8..0x803CABF0 (`__DBInterface` then `DBVerbose`, per §8.7
reverse order).

### 8.12 mwld 8-aligns `.sbss` — absorb the pad into the object, don't fight the linker

Wiring DSP, `dsp_task.o`'s `.sbss` (the task-queue globals `__DSP_curr_task`,
`__DSP_last_task`, `__DSP_tsp_task`, `__DSP_first_task`) must sit at
`0x803CAE64` (4-aligned), but mwld 8-aligns `.sbss` emitted from `.c` files, so
it inserted a 4-byte gap and shifted every following `.sbss` symbol by 4
(patching r13 offsets, breaking `patch_dol.py`'s SDA base).

This is independent of the linker version — both mwld 1.2.5n (Sep-2002) and
1.3.2 (current) 8-align `.sbss` from C objects, so downgrading the linker does
NOT fix it. The standard fix (what tww does for the same SDK) is to **absorb
the 4-byte pad into the object itself**: declare a `static u8 __pad[4]`
(force_active so it survives DCE) as the first `.sbss` member, then
`__DSP_curr_task` lands exactly at `0x803CAE64`. The pad gets its own symbol
(`lbl_803CAE60`) in symbols.txt so the split stays byte-clean. Rule of thumb:
whenever a newly wired module shifts the `.sbss` base by 4 and the retail DOL
keeps a gap before the module's first static, the game's original object had
an explicit pad there — mirror it rather than touching linker flags.

### 8.14 No-slack 4-aligned `.sbss`/`.rodata2`: extern the section back to auto-asm

8.12's "absorb the pad" fix works only when the retail layout has slack
**before** the module (DSP's `0x803CAE60` gap). When the module's statics start
IMMEDIATELY at a 4-not-8-aligned address with no preceding gap, absorbing fails
— the 8-aligned object lands 4 bytes late and every `@sda21` displacement
shifts by 4 (byte-dirty DOL). This is the PAD case (`pad/Pad.c` `.sbss` starts
exactly at `0x803CACAC`, right after OSReboot ends).

Verified facts:
- mwcc GC/1.2.5n emits `.sbss` as 2**3 (8-aligned) unconditionally — tested
  with plain `u32` statics, every `-align` variant (`powerpc`/`mac68k`), and
  `#pragma align`. It can NOT emit a 4-aligned `.sbss`.
- mwld (both 1.2.5n and 1.3.2) bumps a 2**3 `.sbss` input to the next
  8-aligned address (proven with a minimal 2-object link test).
- Retail's own `.sbss` is 4-aligned throughout (units at `0x803CAACC`,
  `0x803CACAC`, `0x803CAE7C` etc.), so the original objects were 4-aligned.

**The fix: keep the section in auto-asm and extern the C references.**
1. Remove the C module's `.sbss` split line (restore auto coverage).
2. Rename the auto-asm symbols in `symbols.txt` to the real variable names
   (they live at the retail addresses; dtk picks the names up on re-split).
3. Convert the C statics to `extern` declarations (file-scope externs;
   function-local statics like `recalibrated` must move to file scope).
4. The compiled code still emits `@sda21` relocs (same addressing as statics);
   the linker resolves them against `_SDA_BASE_` to the auto-asm addresses, so
   every displacement matches retail exactly. The C object simply has no
   `.sbss`, so mwld places nothing and the auto unit (`.balign 4`) keeps the
   exact retail layout — gap included.

Worked example — PAD: retail `.sbss` = `0x803CACAC..0x803CACE0` (12 slots +
`gap_07_803CACDC_sbss`). After the extern conversion the DOL is byte-clean;
`EnabledBits`/`ResettingBits`/`PendingBits`/… are auto-asm symbols at their
retail addresses and `Pad.c` references them as externs. The same route was
needed for `pad/Padclamp.c`'s `ClampRegion` `.rodata2` (retail struct + 3 pad
bytes + a 3-byte symbol at `0x802B1D05`; mwcc emits the C struct into `.rodata`
8-aligned, which can't reproduce it) — extern `ClampRegion` keeps the whole
`.rodata2` section auto.

**Validated on SI, but SI itself stays reverted (see 8.9):** SIBios's `.sbss`
`0x803CAE84..0x803CAE90` and `.bss` `0x803C85C0..0x803C87C0` are the same
no-slack case, and the extern route was proven to fix the data layout
(verified: with the externs in place the compiled `.text` matched retail with
0 structural diffs and only the `.bss` address constants left). The SI wiring
was nevertheless reverted because SIBios.c's *code* is a different SDK
revision (see 8.9) — the extern mechanism itself is correct and is the right
start for any retry.

### 8.13 VI wiring: 9-byte `.sdata` version slot, MSL shift-helper stubs, and the `.bss` base trap

Wiring `vi/vi.c` from tww (Sep-2002, byte-exact) surfaced three things worth
recording:

**1. The version slot in `.sdata` is 9 bytes; dtk needs 4-aligned splits.**
`__VIVersion` (a `const char*` pointer) is 4 bytes of `.sdata`, and the
`"vi.c"` string from `ASSERTLINE`/`OSPanic` `__FILE__` pools directly after
it inside the same object → the compiled object's `.sdata` is 9 bytes
(`{version_ptr, "vi.c\0"}`). dtk refuses non-4-aligned split boundaries, and
adding a `static u8[3]` pad to the source lands BEFORE the string pool (mwcc
emits declared statics first) for 13 bytes — wrong. The retail DOL slot is 12
bytes: the 9 real bytes + 3 bytes of linker padding to the next 4-aligned
object. Fix: split `.sdata` as the full 12-byte range (`0x803CA378..
0x803CA384`) and accept that the object provides 9 of them — the DOL stays
byte-clean because mwld zero-fills the tail. Keep the auto-asm boundary
symbols (`lbl_803CA358` shrunk to `0x20`, `__VIVersion` + `lbl_803CA384`
named) so dtk doesn't auto-generate a symbol inside the split.

**2. 64-bit shift helpers are routed through 4-byte branch stubs — name the
stubs, not the real functions.** `VIFlush`/`__VIRetraceHandler`/`VISetRegs`
compile `changed |= 1LL << (63 - i)` to calls of `__shl2i`/`__shr2u`. In the
retail DOL those are NOT linked to the real MSL runtime functions (`fn_80273480`
`__shl2i`, `fn_80273B68` `__shr2u`); mwld emits 4-byte `b <real>` trampolines
in the caller's region (`__shl2i` stub at `0x8025D004`, `__shr2u` stub at
`0x8025CFFC`, same cluster as `__div2i`/`__mod2i`). The compiled object's `bl
__shl2i` must resolve to the **stub** symbol, so add `__shl2i`/`__shr2u` to
symbols.txt AT the stub addresses (size `0x4`), and leave the real runtime
functions as `fn_*`.

**3. `.bss` base trap: derive the base from lis+addi accesses, not from
source static order.** tww's source order puts `regs[59]`/`shdwRegs[59]` before
`HorVer`, and the first guess put the VI `.bss` at `0x803ACCB0`. But the retail
accesses `regs[i]` via ONE hoisted base (`lis 0x803B; addi -0x3260` →
`0x803ACDA0`) — the base IS `regs[]`, with `shdwRegs` at `+0x78` and `HorVer`
at `+0xF0` (HorVer.timing at `+0x114`, confirmed against the compiled
object). The `.bss` range is therefore `0x803ACDA0..0x803ACEE8` (0x148), and
missing the `.bss` line entirely double-allocates it (built `.bss` grew 0x160,
shifting `.sdata`/`.sdata2` and breaking `patch_dol.py`'s r2 assert).

### 8.15 EXI wiring: `-schedule off` + `-char signed` per-module flags, and the mixed-revision split

Wired `exi/EXIBios.c` (tp base, 24 fns) + `exi/EXIUart.c` (bfbb base, 4 fns)
— DOL byte-clean, all 27 fns land at exact retail addresses (`0x80282E70..
0x80284E20`). thug2's EXI banner is **"Mar 11 2003"** — the newest SDK
component found so far (DVD Oct-2002, DSP Sep-2002). Findings:

**1. EXIBios.c was compiled with `-schedule off` — the default `-O4,p`
scheduling breaks it.** The retail `EXIImm` byte-packing loop is unrolled but
NOT software-pipelined (`lbz; subfic; slwi; slw; or` sequentially per byte);
the default compile interleaves loads and hoists shifts (73 mnemonic diffs,
same sizes). Adding `-schedule off` makes all 24 EXIBios functions match
instruction-for-instruction. Every other wired module (OS/SI/DVD/…) matched
with scheduling ON, so this is per-module, not global — and it explains why
"EXI is a different revision" was the wrong conclusion: the *source* is the
same, only the build flags differed.

**2. EXIBios.c also needs `-char signed`.** `CompleteTransfer`
(`*buf++ = data >> …` byte extraction) breaks with unsigned chars (183/191
mnemonic diffs). `-char signed` matches bfbb's `cflags_dolphin`. The `-char`
flag is first-wins, so the override must be a per-object `cflags` REPLACE
(repeating the full list) — appending `-char signed` after `-char unsigned`
does NOT work.

**3. EXIUart.c needs the OPPOSITE: default `-schedule on`.** bfbb's
`WriteUARTN` (with `OSDisableInterrupts` + inlined `QueueLength`) matches
retail only with scheduling on (schedule off → 101 diffs). So the two EXI
files were built with different flags — consistent with a mixed-revision SDK
where files were recompiled at different times. `EXIUart.c` keeps the default
`cflags_dolphin`; only the `*(s8*)ptr == 0xA` cast is needed (signed compare
→ `cmpwi`, matching retail; `*ptr == '\n'` with `-char unsigned` gives
`cmplwi`).

**4. Data slots.** `Ecb` stays a static `.bss` claim (`0x803C87C0..
0x803C8880`, 8-aligned — no mwld bump). `IDSerialPort1` + the 4 EXIUart
statics (`Chan`/`Dev`/`Enabled`/`BarnacleEnabled`) are 4-aligned `.sbss`
(no-slack, PAD-style) → extern route with `scope:global` symbols.txt entries;
`__EXIVersion` and the banner/type-name strings stay in the auto `.data`/
`.sdata` units (extern `__EXIVersion` only). `EXIGetType`/`EXIGetTypeString`
are dead in retail — removed from the source (their strings live in the auto
`.data` unit).

**5. The game-side rename ripple.** `fn_80284C04` was renamed to
`WriteUARTN` in symbols.txt; the matched game source `src/fn_8028DF3C.c`
referenced the old name and broke the link until updated.

### 8.16 AI wiring: bfbb's ai.c is byte-exact (20 fns) — only `AIReset` needs adding back

Wired `ai/ai.c` from bfbb — DOL byte-clean on the first build, all 20
functions land at exact retail addresses (`0x80276AB0..0x802773A0`). thug2's
AI banner is **"Sep  5 2002"** (0x2301), and bfbb's Apr-2003 ai.c is the
exact reference: its `AIStopDMA` + non-static `__AI_set_stream_sample_rate`
match retail byte-for-byte, whereas tww's Sep-2002 copy (older) and tp's
Apr-2004 copy (newer) both drift.

**1. `AIReset` is the one delta between bfbb and retail.** bfbb
dead-stripped `AIReset` (4 bytes: `lis r3,__AI_init_flag@ha; li r0,0;
stw r0,__AI_init_flag@l; blr`); thug2 keeps it at `0x80277030`. It's added
back from tp's source (`void AIReset(void) { __AI_init_flag = FALSE; }`). The
5 internal handlers/helpers (`__AISHandler`/`__AIDHandler`/
`__AICallbackStackSwitch`/`__AI_set_stream_sample_rate`/`__AI_SRC_INIT`) stay
`static` (`scope:local` in symbols.txt); bfbb leaves them non-static but that
does not change codegen.

**2. `__AICallbackStackSwitch` keeps its `static asm` block** (stack-switch
must save `r1`, reload it from `__CallbackStack`, `mtlr cb; blrl`, restore) —
this is bfbb's verbatim asm, not a hand-rolled hack, and it compiles to the
exact retail bytes.

**3. Data slots.** `.data` (`0x8030B8F8..0x8030B940`) holds only the version
banner string; `.sdata` (`0x803CA970..0x803CA978`) is the 8-byte `__AIVersion`
pointer slot; `.sbss` (`0x803CAD30..0x803CAD70`, 64 bytes) is 6×4-byte
scalars (`__AIS_Callback`/`__AID_Callback`/`__CallbackStack`/`__OldStack`/
`__AI_init_flag`/`__AID_Active`) + 5×8-byte `OSTime` values (`bound_32KHz`/
`bound_48KHz`/`min_wait`/`max_wait`/`buffer`).

**4. The `.sbss` chunk-boundary trap.** The auto-splitter had chunked the
8-byte `OSTime` values as 4-byte words, leaving `lbl_803CAD6C` at size `0x14`
(20 bytes) which crossed the `0x803CAD70` claim end. Split it back into
`lbl_803CAD6C` (4 bytes, inside the claim) + `lbl_803CAD70` (0x10) so the
next module's `.sbss` starts clean at `0x803CAD70`. Unlike SI/EXI there were
**no 4-aligned-scalar externs** — every AI static lives in 8-aligned regions,
so the plain static route works with no register-allocation risk.

---

## 9. Non-OS SDK modules: what the DOL actually links + prioritization

Survey run 2026-08-14. Method: dump every `<< Dolphin SDK - <LIB> release
build: <date> (0x2301) >>` banner string from the DOL rodata (each linked SDK
library ships one), then locate each library's code block by named-symbol
anchors, HW-register accesses (`lis 0xCC00` + offset), and lis+addi string
references.

### 9.1 All 13 linked modules (SDK 0x2301)

All banners live in section 9 rodata; a per-library `{source-name, banner}`
pointer pair table sits at `0x803CA2A0..0x803CA9F8` (e.g. `0x803CA2A0
"dvdfs.c"` / `0x803CA2A8` DVD banner ptr, `0x803CA37C "vi.c"` / `0x803CA378`
VI banner ptr, ...). The banner dates are per-library build dates and show the
SDK is a mix of Sep-2002 builds (VI/PAD/AR/ARQ/AI/CARD/DSP/SI) and later 2003
refreshes (OS/EXI/AX Mar-2003, GX Feb-2003, DVD Oct-2002).

| Lib | Linked | Build date | Text block (approx) | Size | Named today | tp source (complete) |
|---|---|---|---|---|---|---|
| **DVD** | ✓ | Oct 29 2002 | `0x802448E4..0x80249898` | ~20 KB | 25 fns | dvdlow, dvdfs, dvd, dvdqueue, dvderror, dvdidutils, dvdFatal, fstload |
| **GX** | ✓ | Feb 7 2003 | `0x80285050..0x8028D328` | ~33 KB | 12 fns | GXInit/Fifo/Attr/Misc/Geometry/FrameBuf/Light/Texture/Bump/Tev/Pixel/Draw/DisplayList/Transform/Perf |
| **AX** | ✓ | Mar 11 2003 | `0x80277250..0x80280B10` | ~37 KB | 0 | AX.c, AXOut, AXVPB, AXSPB, AXAlloc, AXAux, AXCL, AXComp, DSPCode |
| **SI** | ✓ | Sep 5 2002 | `0x802819D0..0x80282E70` | ~5.3 KB | 7 fns | SIBios, SISamplingRate |
| **EXI** | ✓ | Mar 11 2003 | `0x80282E70..0x802849D8` | ~7.6 KB | 12 fns | EXIBios (+ EXIUart only if referenced) |
| **VI** | ✓ wired | Sep 5 2002 | `0x80260168..0x80261BE0` | ~6.6 KB | 16 (all) | vi.c (tww Sep-2002 is byte-exact; the in-tree tp copy was Apr-2004 — see §8.13) |
| **PAD** | ✓ | Sep 5 2002 | `0x80267DCC..0x8026A024` | ~8.3 KB | 1 (__PADDisableRecalibration @ `0x80269E34`) | Pad.c, Padclamp |
| **DSP** | ✓ wired | Sep 5 2002 | `0x80280B14..0x80281678` | ~2.9 KB | 15 (all) | dsp.c, dsp_task.c, dsp_debug.c (bfbb is the exact function-set match; needs a 4-byte `.sbss` pad — see §8.12) |
| **AR + ARQ** | ✓ wired | Sep 5 2002 | `0x80274BEC..0x80276A78` (ARAM DMA, writes `0xCC00500A`) | ~7.5 KB | 17 (all) | ar.c, arq.c (bfbb's 12-static arq.c is the reference; tww is the 10-static variant. thug2 keeps `__ARClearInterrupt`/`__ARGetInterruptStatus`/`ARQReset` unreferenced — see §8.11) |
| **AI** | ✓ | Sep 5 2002 | `0x80276A78..0x802773A0` (AI regs `0xCC006C00`) | ~2.2 KB | 15 | ai.c (drift: has `AIStopDMA`, inlines `AIResetStreamSampleCount`/`AISetStreamTrigger`, DCEs `AISetStreamSampleRate`; tww's Sep-2002 ai.c lacks `AIStopDMA`) |
| **CARD** | ✓ | Sep 5 2002 | ~`0x80280E00..0x802819D0` (TBD) | ~3 KB | 0 | card/*.c (only referenced files link) |
| **DB** | ✓ wired | – | `0x80261C1C..0x80261D08` | 236 B | 5 (all) | db.c |
| **base/PPC** | ✓ wired | – | `0x80261D08..0x80261E1C` | 276 B | 22 (all) | PPCArch.c |
| **OS** | ✓ wired | Mar 17 2003 | `0x80261E1C..0x80267C54` (+ OSMutex tail `0x80267D5C`, + `__OSReboot` blob `0x80267DE8..0x80268118`) | 24 KB | all | os/*.c |

Not linked (no banner/string evidence): **SC, THP, NAND/IPC, ETH, HIO, IP, GD,
G2D, AM/AMC, MCC, DEMO, AXFX/AXART**. (MTX is *not* in this list — it IS
linked, 21 fns at `0x8025DF74..0x8025E9A4`, all wired byte-exact from C with
the `.sdata2` pool on the extern route; see §9.17.) MetroTRK is present in a
sliver (`EnableMetroTRKInterrupts` @ `0x8025A348`) plus `__TRK_*` in `.init`.

As of the M9 cleanup, `libs/dolphin/src/` contains **only the wired module
dirs** (`os dvd gx db mtx base ar ai dsp vi pad si exi card ax`); the unlinked
modules' source copies (AM/AMC, DEMO, AXFX/AXART, GD/G2D, HIO, MCC, MIX, PERF,
SEQ, SP, SYN, support, dtk, texPalette, fileCache) were deleted — they are not
in the DOL and would only rot. Their headers were pruned to match
(`libs/dolphin/include/dolphin/` now holds only the headers reachable from
wired sources — 83 files, incl. `dolphin.h`/`global.h`/`types.h`; the
unlinked modules' headers are gone too). The runtime zone is **not MSL**:
the DOL's `memcpy/memset/strlen/strncmp/…` are **SN ProDG newlib**
word-at-a-time forms compiled with the game's ngccc (GCC 2.95.2), not the
mwcc MSL revision. The unused MSL implementation sources and unrelated
headers have been pruned; only the small MSL header closure needed by the
wired Dolphin sources remains under `libs/PowerPC_EABI_Support/MSL`.
10 functions are now wired byte-exact via the `runtime` lib
(`libs/runtime/src/`, `cflags_game`, ProDG 3.9.3): `memcmp`/`memcpy`/
`strlen`/`memchr`/`strchr`/`strcmp`/
`strcpy`/`strncpy`/`strcat`/`tolower` (the legacy callers now use
exact-arity `strcpy` declarations so their codegen remains unchanged;
original SN newlib sources via the crashwoc decomp's `src/runtime/libc`
tree). `memset` (4-diff scheduling
coin-flip), `memmove`, `strncmp`, `strcasecmp` (1-insn revisions) and the
printf family stay auto-asm pending the work in
`docs/parkings/22-msl-runtime.md`. See also `docs/neversoft-math-lib.md`
for the region map.

Link order in the DOL text (deduced from block sequence + banner-table order):
`DVD → VI → OS → PAD → AR/ARQ → AI → AX → CARD → DSP → SI → EXI → GX`, with
game code + the ProDG runtime (`memcpy/memset/__save_gpr/__cvt_fp2unsigned`,
`0x8026A024..0x80274A78`) interleaved after PAD.

### 9.2 Prioritization

Total non-OS SDK text ≈ **130 KB** (≈5% of the 2.6 MB DOL `.text`), all
byte-exact-wireable with the DolphinLib pattern (§7) and tp's complete sources.
Rough bytes per effort: these are the *most mechanical* matches left in the
project — no m2c guesswork, just §8-style layout gotchas per module.

1. **DVD (~20 KB)** — do first. 25 functions already named, block fully mapped,
   mkdd's sources are `Matching` quality, and it needs no other SDK lib.
2. **SI + EXI (~13 KB)** — quick win, most functions already named; EXI is also
   a dependency for CARD, and SI's polling ties into PAD.
   - SI: **tww's Sep-2002 source is the exact match** (version string
     byte-identical; §8.9 code is 100%, only the `.sbss` ordering blocker B
     remains).
   - EXI: **bfbb's Apr-2003 source is closest** to thug2's Mar 11 2003 build —
     expect only the version-string edit vs tp's 1-year-newer copy.
3. **DSP + AI + AR + ARQ (~16 KB)** — small; **use tww's Sep-2002 sources**
   (exact match, no reverting); DSP first because AX builds its command lists
   on top of DSP task DMA.
4. **AX (~37 KB)** — biggest single library; Mar-2003 build (same refresh as
   EXI). **bfbb's Apr-2003 AX is the closest reference** (1 month drift vs
   tp's 1 year); tp's 2004 copy remains the superset fallback.
5. **GX (~33 KB)** — biggest block; mechanical but large; no hard deps besides
   OS/VI; tp's GX tree is the most complete of any base.

   **GX build-date caveat (learned M8.10x):** thug2's GX is `Feb 7 2003`,
   while **tww's GX is `Sep 5 2002`** — both print `(0x2301)`, but that is the
   SDK *library* version, constant across builds.

   **Current wiring state + per-file findings: see `docs/gx-wiring-survey.md`**
   (which file matches tww, which drifted and needs bfbb/hand-writing, the
   GXTexture .data/.sdata layout, the include fixes for GXFifo/GXMisc/
   GXLight, and the GXTev Color-family park in `docs/parkings/19-gxtev-color-sched.md`). Only the modules that did
   not change between Sep-2002 and Feb-2003 wire byte-exact from tww:
   **GXDisplayList, GXStubs** (all wired M8.105–M8.106). **GXInit is 4/5
   wired** (the peephole-off reconstruction matched all but `GXInit` main —
   see docs/parkings/21-gxinit.md); it is a Feb-7-2003-only revision
   (arithmetic tex-region init, no GXTexRegionAddrTable, inlined
   __GXInitRevisionBits) that exists in no other decomp. The rest drifted:
   - **GXFifo.c** — thug2 DCE'd `GXSaveCPUFifo`/`__GXSaveCPUFifoAux`/
     `__GXCleanGPFifo`/`GXSetCurrentGXThread` but *kept* `GXGetFifoBase`/
     `GXGetFifoSize`/`GXSetBreakPtCallback` (which tww DCE'd), and moved
     `__GXFifoLink` after `__GXWriteFifoIntReset`.
   - **GXAttr.c** — `fn_80286E5C` (0x374) and `fn_80287348` (0x1B4) match
     no single tww GXAttr function (inlining/ordering changed).
   - **GXPerf.c** — thug2 *kept* `GXReadGPMetric` (0x1A8, dead code) which
     tww's Sep-2002 source lacks entirely (it was added between the two
     builds); tp's 2004 copy exists but uses 2004 enums/`ASSERTMSGLINE`.

   So GXFifo/GXAttr/GXPerf need per-function reconstruction from disasm
   (tww as base, tp only for the functions added after Sep-2002); **bfbb's
   Apr-2003 GX (Apr 21 2003) is now the closest single reference** for
   thug2's Feb-2003 drift — diff bfbb's copies against tp's 2004 versions
   first; where they agree, the pre-2004 shape is confirmed.
6. **VI + PAD (~14 KB)** — small; **use tww's Sep-2002 sources** (exact);
   VI pairs naturally with GX.
7. **CARD (~3 KB)** — small; **use tww's Sep-2002 card/ sources** (exact);
   confirm which of the 20 card/*.c files actually reference
   (CARDInit/CARDOpen/…), depends on EXI.
8. **DB / base / MetroTRK** — trivial slivers; the OS region is now complete
   (`__OSReboot` folded in via `os/OSReboot.c`, wired as its own SDK unit).

Each module wiring repeats the §8 gotchas: split `.data` at the last live
string (dead tail strings stay auto-covered), `.sbss` global reverse-order,
frame-size padding with a dummy local, and non-`const` SDK globals that must
land in `.data`. Verify with `cmp` on the DOL after every module.

### 9.3 Remaining modules (surveyed 2026-08-16, after M8.116)

> **Update (M8.117):** `card/CARDBios.c` + `card/CARDReset.c` are now wired
> byte-exact (24 functions, progress 4740/11468). See §9.4. The remaining
> unwired CARD files (CARDStat/CARDBlock/CARDRead/CARDOpen/…), AX, and GX are
> unchanged below.

After AI (M8.116) the only unwired SDK text is the `0x802773A0..0x80280B14`
block (AX + CARD) and the `0x80285050..0x8028D328` GX block. Precise findings:

**1. CARD is wireable from tww (Sep-2002), not tp.** tww's `card/CARDBios.c`
compiles against the in-tree headers with **one** trivial addition —
`#include <dolphin/exi.h>` (the in-tree `card.h` doesn't transitively pull in
exi like tww's does; `EXI_WRITE`/`EXIImm` etc. are already declared in the
in-tree `exi.h`). Its function sizes match retail **exactly** (verified the
full 26-function list: `__CARDDefaultApiCallback` 0x4 → `OnReset` 0x50). tp's
`CARDBios.c` is Apr-2004 and carries a newer API (`CARDGetFastMode`/
`__CARDReadVendorID`/`__CARDSleep`…) — it does **not** match Sep-2002 retail.

**2. AX and CARD are *interleaved* in .text** — this is why neither wires as a
single clean block. `CARDBios.c` occupies `0x8027A3BC..0x8027B588`
(`CARDGetResultCode` 0x30 is dead-stripped) plus `__CARDSync`+`OnReset` at
`0x8027B610..0x8027B6F8`, separated by a `0x8027B588` (0x88) function from a
*neighbouring* card file. The other card files (CARDStat/CARDBlock/CARDRead/
CARDOpen…) sit in the `0x8027B588..0x8027B9B4`, `0x8027CD94..0x8027D6DC`,
`0x8027F7A0`, and `0x80280570..0x80280B14` pockets, with AX blocks in between.
So CARD must be wired **per file** (each `card/*.c` its own split unit), and AX
likewise — the linker order already interleaves them correctly.

**3. GX is blocked on a pre-existing tp header conflict, and needs bfbb.**
`__gx.h:219` declares `__GXSaveCPUFifoAux(__GXFifoObj*)` (private 34-byte
struct) while the public `GXStruct.h` `GXFifoObj` is 0x80 and `GXFifo.h:19`
declares `__GXSaveCPUFifoAux(GXFifoObj*)`. The two structs differ, so no GX
file that includes `__gx.h` compiles until this is reconciled (and `GXFifo.c`
defines the function with `__GXFifoObj`). Also **no existing GXInit.c matches**: tww's is Sep-2002 (its `GXInit`
compiles to 0x5d0 vs retail 0x890), and bfbb's Apr-2003 uses the
GXTexRegionAddrTable while retail GXInit computes region addresses
arithmetically. A full hand reconstruction was attempted 2026-08-19; 4 of 5
functions are now wired byte-exact (see docs/parkings/21-gxinit.md,
reconstruction source: src/wip/fn_80285050.c).

**4. AX needs bfbb (Apr-2003).** thug2's AX banner is Mar 11 2003; bfbb's
`ax/*.c` is the closest reference (tww has no AX, tp is Apr-2004). AX's `.data`
(`0x8030b940..0x8030f3c0`, ~15 KB) carries the DSP microcode; its `.text` is
interleaved with CARD per finding 2.

**Order for the next chunks:** (a) reconcile the GX `__GXFifoObj`/`GXFifoObj`
header conflict, then wire GXFifo's remaining files; GXInit main stays parked
(docs/parkings/21-gxinit.md); or (b) wire CARD file-by-file from tww (start
with `CARDBios.c`, then map the interleaved neighbours); AX last (biggest,
needs the CARD map).

### 9.4 CARDBios.c wiring (M8.117)

thug2's CARD is the Sep-5-2002 (0x2301) build; tww's `card/CARDBios.c` is the
exact reference (same banner) and compiles with the default `cflags_dolphin`
(`-inline auto`) with one trivial addition — `#include <dolphin/exi.h>` (the
in-tree `card.h` doesn't transitively pull in exi). All 26 functions compile to
the exact retail sizes; `SetupTimeoutAlarm` (static, inlined into `Retry` and
`__CARDStart`) and `CARDGetResultCode` (inlined into `__CARDSync`) dead-strip.

**The interleave forces a two-file split.** Retail places `__CARDSync`+
`OnReset` at `0x8027B610..0x8027B6F8`, *after* a CARDStat function at
`0x8027B588` (0x88) that sits between them and the CARDBios.c main block
(`0x8027A3BC..0x8027B588`). A single object with two `.text` ranges straddling
that gap gives dtk a **cyclic link-order dependency** (`card/CARDBios.c ->
auto_01_8027B588_text`), so the file is split:

- `card/CARDBios.c` — the 22 main functions + `ResetFunctionInfo`
  (`{OnReset,127}`) + `__CARDBlock`/`__CARDDiskNone`/version string. `OnReset`
  becomes `extern BOOL OnReset(BOOL)` so `ResetFunctionInfo` can take its address.
- `card/CARDReset.c` — `CARDGetResultCode` + `__CARDSync` + `OnReset`
  (`OnReset` non-static). `CARDGetResultCode` stays here so it still inlines
  into `__CARDSync` and dead-strips, exactly as in retail.

**Data layout (extern route, like SI):** `.data` `0x8030F3C0..0x8030F418`
(version string 0x46 + `ResetFunctionInfo` 0x10) and `.bss`
`0x803C8380..0x803C85C0` (`__CARDBlock` 0x220 + `__CARDDiskNone` 0x20) are
claimed statically. The `__CARDVersion` pointer (`.sdata` 0x803CA988, 4 bytes)
and `__CARDEncode` (`.sbss` 0x803CAE48, 2 bytes) live in the auto units and are
externed; the version string is emitted via a `#pragma force_active` `char
lbl_8030F3C0[]` (so it stays in `.data`, not `.rodata`).

**Ripple renames** (symbols.txt + callers): `fn_80264710`→`OSGetFontEncode`
(still auto-asm; OSFont.c's copy isn't in the wired os/ range yet),
`fn_8027B6F8`→`__CARDGetFatBlock`, `fn_8027BAFC`→`__CARDGetDirBlock`,
`fn_8027D6DC`→`CARDUnmount` (referenced by `OnReset`).

### 9.5 CARDBlock.c wiring (M8.118)

`card/CARDBlock.c` wires cleanly with **no source edits** — the in-tree copy
(6 functions: `__CARDGetFatBlock` + `WriteCallback`/`EraseCallback` statics +
`__CARDAllocBlock` + `__CARDFreeBlock` + `__CARDUpdateFatBlock`) compiles to
the exact retail sizes. Unlike CARDBios.c there is **no interleave**: the six
functions sit contiguously at `0x8027B6F8..0x8027BAFC`, so a single `.text`
claim (no `.data`/`.bss` — it only references `__CARDBlock`, already claimed by
CARDBios.c) is all splits.txt needs, and the old `fn_8027B6F8.c` auto unit is
dropped.

**Ripple renames** (the three externs CARDBlock.c calls that were still auto
units): `fn_8027BD60`→`__CARDCheckSum` (CARDCheck.c), `fn_802632DC`→
`DCStoreRange` (OSCache.c), `fn_80280AB0`→`__CARDWrite` (CARDRdwr.c).

**Per-file revision trap (important for the remaining card files).** The
in-tree `libs/dolphin/src/card/*.c` were bulk-copied and are a *mix* of
revisions — only compile-and-compare decides. Verified while wiring this file:

- `CARDBlock.c` needs the **bfbb/tp** shape (`__CARDFreeBlock` lives here;
  tww's CARDBlock.c has no such function at all). Correct as copied.
- `CARDStat.c` needs the **tww** shape: retail `CARDGetStatus` is 0x12C and
  calls `__CARDAccess`/`__CARDIsPublic`; the in-tree copy uses bfbb/tp's
  `__CARDIsReadable`/`__CARDIsWritable` and compiles to 0x114 (wrong).
- `CARDRdwr.c` needs the **tww** shape: retail `__CARDRead`/`__CARDWrite` are
  0x64 each and use hardcoded `>> 9`/`>> 7` (`/512`, `/128`); the in-tree copy
  uses `card->pageSize` (bfbb/tp) and compiles `__CARDWrite` to 0x68 (wrong).
  Retail addresses: `BlockReadCallback` 0x80280894, `__CARDRead` 0x80280970,
  `BlockWriteCallback` 0x802809D4, `__CARDWrite` 0x80280AB0.

### 9.6 CARDRdwr.c wiring (M8.119)

`card/CARDRdwr.c` is the tww source swapped in for the in-tree bfbb/tp copy
(hardcoded `/512` + `/128` instead of `card->pageSize`; `CARDGetXferredBytes`
dropped — it's dead-stripped in retail). Four functions, contiguous at
`0x80280894..0x80280B14` (`BlockReadCallback`/`BlockWriteCallback` are
statics), zero new dependency renames — `__CARDReadSegment`, `__CARDWritePage`
and `__CARDPutControlBlock` were already wired in CARDBios.c. This is the
cleanest card file so far: a single `.text` claim, default `cflags_dolphin`,
no `.data`/`.bss`, first-build and force-recompile both DOL byte-clean.

### 9.7 CARDStat.c wiring (M8.120)

`card/CARDStat.c` is the tww source swapped in (as predicted in §9.5): retail
`CARDGetStatus` is 0x12C and calls `__CARDAccess`/`__CARDIsPublic`; the
in-tree bfbb/tp copy (`__CARDIsReadable`/`__CARDIsWritable`) compiles to 0x114.
Four functions contiguous at `0x8027F154..0x8027F634` (`UpdateIconOffsets` is
static). Ripple renames for the three auto-asm callees:
`fn_8027BC9C`→`__CARDUpdateDir` (CARDDir.c), `fn_8027DFE0`→`__CARDAccess`,
`fn_8027E078`→`__CARDIsPublic` (both CARDOpen.c). `CARDGetStatus`/
`CARDSetStatus` are public API and get called by game code (the WIP drafts at
0x80016114/0x800161C4/0x80167818 picked up the real names). First-build +
force-recompile both DOL byte-clean.

### 9.8 CARDDir/CARDWrite/CARDGetEncoding (M8.121–M8.123)

`card/CARDDir.c` (M8.121, `0x8027BAFC..0x8027BD60`) and `card/CARDWrite.c`
(M8.122, `0x8027EBDC..0x8027EF58`) both wired straight from tww — no source
edits, no `.text` interleave, single `.text` claim each. `CARDGetEncoding`
(M8.123) is a one-off worth flagging: it sits **alone at `0x8027B588..0x8027B610`**,
sandwiched between `CARDFreeBlocks` (CARDBios.c) and `__CARDSync` (CARDReset.c).
It must stay **in `CARDBios.c`** (appended after `CARDFreeBlocks`) because retail
compiles it with `__CARDPutControlBlock` **inlined** — the compiler only inlines
that when `CARDGetEncoding` is in the same translation unit as
`__CARDPutControlBlock` (the bfbb/tp layout). A standalone file declaring
`__CARDPutControlBlock` extern compiles to 0x58 (a `bl` call) vs retail's 0x88
(inlined `OSDisableInterrupts`/`OSRestoreInterrupts`). tww's CARDBios.c predates
`CARDGetEncoding` entirely, so this is a bfbb/tp function grafted onto the tww
file. `CARDGetMemSize`/`CARDGetSectorSize` are **not linked** (dead-stripped),
so they are left out. CARDBios.c `.text` claim extended to `0x8027B610`;
caller `fn_80015B94.c` renames `fn_8027B588`→`CARDGetEncoding`.

### 9.9 CARD module completion (M8.124–M8.130)

The rest of `card/` wired file-by-file; every file is now byte-exact and the
whole CARD block `0x8027A3BC..0x80280B14` is C source. Per-file notes:

- **CARDCheck.c** (M8.124, `0x8027BD60..0x8027CCC8`): in-tree copy already tww
  shape. `VerifyID/VerifyDir/VerifyFAT` statics, `__CARDVerify`,
  `CARDCheckExAsync`, `CARDCheck`; `CARDCheckAsync/CARDCheckEx` dead-strip.
- **CARDMount.c** (M8.125, `0x8027CCC8..0x8027D788` + `.data 0x8030F418..0x8030F458`):
  reverted bfbb/tp → tww (dropped `__CARDDisable` + the `__CARDReadVendorID`/
  `pageSize` DoMount block so `DoMount` compiles 0x410). `SectorSizeTable`/
  `LatencyTable` statics in `.data`. Ripple: `fn_8027F9A8`→`__CARDUnlock`,
  `lbl_803CA990`→`__CARDVendorID`.
- **CARDFormat.c** (M8.126, `0x8027D788..0x8027DF78`): tww swap.
- **CARDOpen.c** (M8.127, `0x8027DF78..0x8027E3C4`, `extra_cflags=["-char signed"]`):
  tww swap (`__CARDIsPublic`, no FastOpen/IsOpened). **CARD needs `-char signed`**
  (like DVD): the signed-char compare in `__CARDCompareFileName`/`__CARDGetFileNo`
  compiles 0x68/0x150 vs 0x60/0x148 under `-char unsigned`.
- **CARDCreate.c + CARDRead.c** (M8.128, `0x8027E3CC..0x8027EBDC`): tww. `__CARDIsOpened`
  (a 0x8 `return FALSE` stub at 0x8027E3C4) folds into CARDOpen.c (bfbb layout).
  CARDCreateAsync uses the wired runtime `strlen`/`strncpy` implementations.
- **CARDDelete.c** (M8.129, `0x8027EF58..0x8027F154`): in-tree already matched.
  `CARDFastDeleteAsync/CARDFastDelete` dead-strip.
- **CARDUnlock.c** (M8.130, `0x8027F634..0x80280894` + `.data 0x8030F460..0x8030F5C0`
  + `.sdata 0x803CA998..0x803CA99C`): the last card file, wired with **no source
  edits** (in-tree copy is tww-semantic — `CARDFreq` = `EXI_FREQ_16M` = the
  hardcoded `4`, `DOLPHIN_ALIGNMENT` = 32). Six linked functions: `bitrev`
  (0x16C), `ReadArrayUnlock` (0x144), `DummyLen` (0xC4) statics, then
  `__CARDUnlock` (0xB58, the only global), `InitCallback` (0x70), `DoneCallback`
  (0x324). `exnor_1st`/`exnor`/`GetInitVal`/`CARDRand`/`CARDSrand` are inlined
  into `__CARDUnlock` (their standalone static copies dead-strip — this is why
  the in-tree `.o` shows them but retail has only six functions). Data: the
  352-byte `CardData` DSP microcode blob in `.data` and the `next` LCG seed
  (`static u32 next = 1`) in `.sdata` at `0x803CA998` — split the 8-byte auto
  `lbl_803CA998` into `next` (4B, scope:local) + `lbl_803CA99C` (4B, stays auto).

**All 14 card files are now wired** (CARDBios, CARDReset, CARDBlock, CARDDir,
CARDCheck, CARDMount, CARDFormat, CARDOpen, CARDCreate, CARDRead, CARDWrite,
CARDDelete, CARDStat, CARDUnlock, CARDRdwr). CARDRename/CARDRaw/CARDProgram/
CARDErase/CARDStatEx/CARDNet are **not linked** in retail (dead-stripped), so
they stay unwired.

### 9.10 AX module start: AXAlloc.c (M8.131)

AX (`0x802773A0..0x8027A3BC`, 64 fns, ~15 KB DSP microcode in `.data`) is the
last SDK block besides GX. Retail AX is **Mar 11 2003** (same day as EXI);
bfbb is Apr-17-2003, so most files have small drifts and need per-file matching.

`ax/AXAlloc.c` is the clean file — **all 10 functions match bfbb byte-exact**
(no source edits beyond include adaptation `#include <dolphin.h>`→
`<dolphin/dolphin.h>` and `"ax/__ax.h"`→`"__ax.h"`). The in-tree (tp) copy is
the *refactored* revision (`AXSetVoicePriority`/`__AXCheckStacks`/
`__AXInitVoiceStacks` added, the `__AXPopFreeStack`/`__AXPushStackHead`/
`__AXPopStackFromBottom` helpers made non-inline) and does **not** match.

`.text 0x80277410..0x802778D8` (contiguous, sits between `AXInitEx`/`AXQuit`
and `__AXAuxInit`). Data: `__AXStackHead[32]` (`.bss 0x803AF310`, 0x80),
`__AXStackTail[32]` (`.bss 0x803AF390`, 0x80) — `AX_PRIORITY_STACKS`=32, so
retail's `__AXAllocInit` clears 32 entries not 4 — and `__AXCallbackStack`
(`.sbss 0x803CAD80`, 4 B). Each required splitting an auto object
(`lbl_803AF390` 0x90→0x80+`lbl_803AF410`; `lbl_803CAD80` 0x8→0x4+`lbl_803CAD84`).
One ripple rename: `fn_802799D0`→`__AXSetPBDefault` (AXVPB.c, called by
`AXFreeVoice`/`AXAcquireVoice`; still auto-asm, not wired yet).

Known drifts in the other AX files (for the next chunks): `AXInitEx` 0x3C vs
bfbb 0x4C (retail doesn't pass `outputBufferMode` to `__AXOutInit`),
`__AXOutInit` 0x340 vs 0x3A0, `__AXVPBInit` 0x1FC vs 0x200, `__AXServiceVPB`
0x708 vs 0x74C, `__AXSyncPBs` 0x268 vs 0x278, `__AXSetPBDefault` 0x3C vs 0x40.

### 9.11 AXAux.c (M8.132) and AXCL.c (M8.133)

`ax/AXAux.c` (13 fns, `0x802778D8..0x80277D60`) is bfbb-clean: 13 statics in
`.sbss 0x803CAD88..0x803CADBC`, `__AXBufferAuxA/B[3][480]` in `.bss`
`0x803AF420`/`0x803B0AA0` (0x1680 each).

`ax/AXCL.c` is **not** pure bfbb — bfbb is missing two functions retail has.
Retail `AXCL.c` (`0x80277D60..0x80278498`, 7 fns) = bfbb's 5
(`__AXGetCommandListCycles`/`__AXGetCommandListAddress`/`__AXNextFrame`/
`__AXClInit`/`__AXClQuit`) **plus** `AXSetMode` (0x14, `0x8027847C`) and
`AXSetCompressor` (0x8, `0x80278490`) appended after `__AXClQuit`. tp's copy
has these but its `__AXWriteToCommandList` is non-`inline` (extra 0x18 fn) and
its `AXGetMode`/`AXGetCompressor` dead-strip — so the right source is bfbb +
the two setters grafted on. Data: `__AXCommandList[2][384]` (`.bss 0x803B2120`,
0x600), 4 statics + `__AXClMode` (`.sbss 0x803CADC0..0x803CADD4`, 0x14).

Ripple renames this forced (all still auto-asm, now correctly named):
`fn_80278B84`→`__AXGetStudio` (AXSPB.c), `fn_802799C4`→`__AXGetPBs` (AXVPB.c),
`fn_8027904C`→`__AXGetNumVoices` (AXVPB.c), `lbl_8030BA60`→`__AXCompressorTable`
(AXComp.c `.data` 0x1A40). **Trap:** `__AXGetPBs` is the `lis+addi` 0xC fn at
`0x802799C4` (returns the `__AXPB` array base), NOT the 0x8 `lwz` fn at
`0x8027904C` — that one is `__AXGetNumVoices`. Disassemble the callee before
naming the small AXVPB getters.

### 9.12 Remaining AX files: exact ranges + drifts

Full remaining AX map (after M8.133):

| file | .text range | notes |
|---|---|---|
| `ax/AX.c` | `0x802773A0..0x80277410` | **wired M8.135** — `AXInit` 0x3C + `AXQuit` 0x34 byte-clean. bfbb's `AXInitEx(u32 outputBufferMode)` is the *newer* revision; retail's `AXInit(void)` drops the arg (calls `__AXOutInit(void)`). Version string `"<< Dolphin SDK - AX\trelease build: Mar 11 2003 11:19:39 (0x2301) >>"` in `.data 0x8030B940`, pointer `__AXVersion` in `.sdata 0x803CA978` |
| `ax/AXOut.c` | `0x80278498..0x80278B84` | **wired M8.136** — 9 fns byte-clean after reverting bfbb's `outputBufferMode` feature: `__AXOutBuffer[2][320]` (not bfbb's `[3][320]`), no `__AXOutputBufferMode` static, `__AXOutInit(void)`/`__AXOutNewFrame` take the pre-`lessDspCycles` form |
| `ax/AXSPB.c` | `0x80278B84..0x8027904C` | **wired M8.134** — 5 fns byte-clean (`__AXGetStudio`/`__AXPrintStudio`/`__AXSPBInit`/`__AXSPBQuit`/`__AXDepopVoice`), `.bss` `__AXStudio` 0x36 + `__AXSpbAL..ABS` (9×4) in `.sbss 0x803CAE00..0x803CAE24` |
| `ax/AXVPB.c` | `0x8027904C..0x8027A374` | **remaining** — 4 drifted core fns + a different voice-setter set. `__AXServiceVPB` 0x708 vs bfbb 0x74C, `__AXSyncPBs` 0x268 vs 0x278, `__AXSetPBDefault` 0x3C vs 0x40, `__AXVPBInit` 0x1FC vs 0x200. Retail has 2 fns bfbb lacks: `fn_80279D78` 0x254 (loop-copies u16s into `p+0x14A` until 0 — an older `AXSetVoiceSrc`-style ratio copier) and `fn_80279FCC` 0x58 (copies 2 halfwords into `p+0x19C/0x19E`, sets flag `0x200` — `AXSetVoiceAdpcmLoop`). bfbb instead has three `0x54`-byte setters retail dead-strips. See §9.15 |
| `ax/AXProf.c` | `0x8027A374..0x8027A3BC` | **wired M8.137** — 1 fn `__AXGetCurrentProfile` 0x48 byte-clean; `AXInitProfile`/`AXGetProfile` dead-strip in retail. 4 `.sbss` statics (`__AXProfile`/`__AXMaxProfiles`/`__AXCurrentProfile`/`__AXProfileInitialized` @ `0x803CAE38..0x803CAE44`) stay auto-asm via the extern route |
| `ax/AXComp.c` | data only | **wired M8.137** — `__AXCompressorTable[3360]` `.data 0x8030BA60` (0x1A40), bfbb byte-identical (compressor table didn't drift) |
| `ax/DSPCode.c` | data only | **wired M8.137** — `axDspSlave[0xF90]` `.data 0x8030D4A0` (0x1F20), extracted from retail (bfbb drifts from byte 4); `axDspSlaveLength` (u16 0x1F20) + 6 B pad stay auto-asm `.sdata 0x803CA980` (extern route). `AX_DSP_SLAVE_LENGTH` corrected 0xF80→0xF90 in ax.h |

`__AXStudio` (`.bss 0x803B6F40`) is `static struct _AXSPB` with `ATTRIBUTE_ALIGN(32)`;
retail's slot is 0x40 but bfbb's struct is 0x36 (fields end at 0x36), so the 0xA
is alignment padding before `__AXPB` (`0x803B6F80`, 32-aligned). mwld does **not**
pad a 32-aligned section to its alignment — it lays the next blob down at
`.balign 8` of `0x803B6F76`, i.e. `0x803B6F78`, which shifts every later `.bss`
object 8 bytes and (after `.sdata ALIGN(0x10)`) lands `.sdata2` 0x10 early,
failing `patch_dol.py`'s r2 check. **Fix (M8.134):** declare `__AXStudio` as a
union `{ struct _AXSPB studio; u8 pad[0x40]; }` so the object is 0x40 in `.bss`,
keep `sizeof(struct _AXSPB)` (0x36) for the `DCFlushRange` call, and route field
accesses through `.studio.` (offset 0, so `.text` is byte-identical).

### 9.13 AXOut.c wiring (M8.136)

`ax/AXOut.c` (`0x80278498..0x80278B84`, 9 fns) is the hardest of the AX
revisions — bfbb/tp are **newer** (they carry `__AXOutputBufferMode` and a
`[3][320]` triple buffer, which add 0x60 to `__AXOutInit` and 0x30 to
`__AXOutNewFrame`). The source is a hand-revert:

- `static s16 __AXOutBuffer[2][320]` (0x500, not bfbb's `[3][320]` 0x780),
  `static s32 __AXOutSBuffer[160]` (0x280), `static u16 __AXDramImage[8192]`
  (0x4000), `static DSPTaskInfo __AXDSPTask` (0x50), `AXPROFILE
  __AXLocalProfile` (0x38).
- `.sbss` externs stay in auto-asm via the extern route: `__AXOutFrame`
  (0x803CADD8), `__AXOutDspReady`, `__AXOsTime` (OSTime), `__AXUserFrameCallback`,
  `__AXDSPInitFlag`, `__AXDSPDoneFlag`, `__AXDebugSteppingMode`,
  `__AXOutThreadQueue` (OSThreadQueue). These replace the old
  `lbl_803CADD8..lbl_803CADF8` run; note the **descending** r13 offsets
  (`__AXOutThreadQueue` at `-0x7488` up to `__AXOutFrame` at `-0x74A8`).
- `.bss` layout (verified against the retail `__AXOutInit` memset):
  `__AXOutBuffer` 0x500 @ `0x803B2720`, `__AXOutSBuffer` 0x280 @ `0x803B2C20`
  (**not** `0x803B2A20` — that was an off-by-0x200 guess; retail clears it at
  `r31+0x500`), `__AXDSPTask` 0x50 @ `0x803B2EA0`, `__AXDramImage` 0x4000 @
  `0x803B2EF0`, `__AXLocalProfile` 0x38 @ `0x803B6EF0`; the 0x18 run
  `0x803B6F28..0x803B6F40` is alignment padding for `__AXStudio` (32-aligned),
  kept as `lbl_803B6F28` (auto `.bss` object `auto_05_803B6F28_bss.o`).

Four ripple renames so AXOut.c links against still-auto-asm siblings:
`fn_8027975C`→`__AXSyncPBs` (AXVPB.c), `fn_8027A374`→`__AXGetCurrentProfile`
(AXProf.c), `lbl_8030D4A0`→`axDspSlave` (DSPCode.c `.data` 0x1F20, u16[]),
`lbl_803CA980`→`axDspSlaveLength` (u16 0x1F20) + `lbl_803CA982` (6 B pad).

**Trap:** `axDspSlave`/`axDspSlaveLength` are the retail **Mar-2003** microcode
(bfbb's Apr-2003 `axDspSlave` differs from byte 4 — `0x0E76` vs retail
`0x0EB3`), so DSPCode.c is *not* a clean swap; the data stays auto-asm.

### 9.14 AXProf.c + AXComp.c + DSPCode.c data (M8.137)

The three remaining *clean* AX pieces land together:

- **AXProf.c** is a single function. Retail `AXProf.c` = `__AXGetCurrentProfile`
  (0x48) only — `AXInitProfile`/`AXGetProfile` are dead-stripped (the game never
  calls them), so the 0x6C fn at `0x8027A308` is *not* `AXInitProfile` (it's an
  AXVPB voice setter). Its 4 `.sbss` statics sit at
  `__AXProfile` 0x803CAE38 / `__AXMaxProfiles` 0x803CAE3C /
  `__AXCurrentProfile` 0x803CAE40 / `__AXProfileInitialized` 0x803CAE44
  (descending r13 offsets `-0x7448..-0x743C`), externed from C.

- **AXComp.c** is pure data and byte-identical to bfbb (the compressor table is
  a fixed lookup — it didn't drift across the SDK revision).

- **DSPCode.c** data is **not** clean from bfbb: retail's `axDspSlave` is
  0xF90 u16 (0x1F20 B) and differs from bfbb at byte 4 (`0x0EB3` vs `0x0E76`).
  Generate it by dumping retail's `.data` (see `tools/` pattern: read the DOL,
  `struct.unpack` the u16 run). `axDspSlaveLength` is a 2-byte initialized u16
  (`0x1F20`) followed by 6 B of 8-byte-alignment padding — **leave both
  auto-asm** (extern `axDspSlaveLength` from DSPCode.c). Claiming just the 2 B
  `.sdata` in the split leaves a 6-byte `auto_06_803CA982_sdata` object at a
  2-aligned address, which objdiff rejects (`Invalid alignment for split`) —
  the `.sdata` section is 4-aligned, so a 0x6 remainder can't stand alone.
  `AX_DSP_SLAVE_LENGTH` was `0xF80` (tp's value); retail needs `0xF90`
  (`0xF90*2 = 0x1F20 = axDspSlaveLength`).

### 9.15 AXVPB.c wired (M8.138) — the last AX file, all 17 fns byte-exact

`ax/AXVPB.c` is now wired: `.text 0x8027904C..0x8027A374`, `.data
0x8030B988..0x8030BA60`, `.bss 0x803B6F80..0x803C8380`, `.sbss
0x803CAE28..0x803CAE34`, `.sdata2 0x803CC060..0x803CC064` (the `65536.0f`
constant in `AXSetVoiceSrcRatio`). All 17 functions match byte-exact on the
first build *and* a force-recompile.

**The earlier drift table was wrong.** It was produced by compiling bfbb's
AXVPB.c against the *pre-lpf-removal* `ax.h`. The actual retail layout uses
an `AXPB` that is **0xEC bytes** (no `AXPBLPF lpf`), and once that field was
removed the bfbb source falls into retail shape almost everywhere. Correct
voice-setter map (derived from asm offsets, not sizes):

| retail | size | name |
|---|---|---|
| `0x80279C0C` | 0xC4 | `AXSetVoiceSrcType` |
| `0x80279CD0` | 0x5C | `AXSetVoiceState` |
| `0x80279D2C` | 0x4C | `AXSetVoiceType` |
| `0x80279D78` | 0x254 | `AXSetVoiceMix` (18×u16 copy + mixerCtrl, *not* a ratio copier) |
| `0x80279FCC` | 0x58 | `AXSetVoiceVe` (currentVolume + currentDelta) |
| `0x8027A024` | 0x110 | `AXSetVoiceAddr` (4×u32 + format switch 0/10/25) |
| `0x8027A134` | 0xA4 | `AXSetVoiceAdpcm` (10×u32 copy) |
| `0x8027A1D8` | 0x98 | `AXSetVoiceSrc` (7×u16 copy) |
| `0x8027A270` | 0x98 | `AXSetVoiceSrcRatio` (`65536.0f * ratio`, clamp 0x40000) |
| `0x8027A308` | 0x6C | `AXSetVoiceAdpcmLoop` (3×u16 copy) |

**Gotcha worth remembering:** the voice setters are identified by their
*source-struct offset* in the `AXVPB` (e.g. `0x14A` = `pb.mix`, `0x1B6` =
`pb.adpcm`, `0x1EC` = `pb.adpcmLoop` = `0x138` + the `AXPB` field offset),
not by size — two of them are 0x98. The `65536.0f` is the **only** float in
the file and lives in `.sdata2` at `0x803CC060`, referenced via r13
(`R_PPC_EMB_SDA21`, `lfs f0, -0x6220(r13)` with `_SDA_BASE_ = 0x803D2280`).

### 9.16 GXPerf.c wired (M8.139) — first GX file beyond the stubs

`gx/GXPerf.c` is now wired: `.text 0x8028C860..0x8028D324`, `.data
0x80310968..0x80310AB0` (3 switch jump tables). All 4 functions match
byte-exact: `GXSetGPMetric` (0x848), `GXReadGPMetric` (0x1A8),
`GXClearGPMetric` (0x10), `GXReadXfRasMetric` (0xC4). Replaces 4 auto-asm
units + 4 WIP drafts.

**Source pick:** tww's Sep-2002 `GXPerf.c` for the 3 shared functions (byte-
exact), and tp's `GXReadGPMetric` adapted (`__GXData` → `gx`, drop
`ASSERTMSGLINE`, which is compiled out under NDEBUG anyway). It was dropped
from tww/bfbb/mkdd and only survives drifted in tp.

**Gotcha 1 — `#pragma scheduling off`:** the four `__GXReadCPCounterU32`
busy-wait loops reorder under `-O4,p` scheduling (the loop body loads HI
before LO, and the next read's address setup gets hoisted into the combine).
Wrapping the function in `#pragma scheduling off` / `#pragma scheduling reset`
restores the exact retail order (LO-then-HI per the inline) and the exact
`__cpReg` register (r10). Same pattern `GXReadXfRasMetric` already uses.

**Gotcha 2 — dead-strip cascade:** nothing in the game calls
`GXReadGPMetric`, so mwld strips it. That alone breaks the DOL byte layout in
a confusing way: `.text` shrinks, the sibling functions shift up, the GXPerf
`.data` jump tables vanish, and `.data`/`.bss`/`.sdata`/`.sdata2` all shift
0x1E0 bytes early, which trips `patch_dol.py`'s init-r2 sanity check
("Init r2 setup computes 0x803D2DA0, expected 0x803D2F80"). Fix is the
standard `#pragma force_active on` used by `ar/arq/card/dsp/dvd/si`.

**Gotcha 3 — non-contiguous splits are impossible:** you cannot wire 3 of 4
functions and leave the middle one auto-asm. A split unit's `.text` must be
contiguous in the link; a hole between two ranges makes dtk fail with
"Cyclic dependency encountered while resolving link order:
gx/GXPerf.c -> auto_XX_8028D0A8_text". Either match the whole file or split
it into multiple objects.

### 9.17 mtx module — 21/21 wired byte-exact (complete)

`mtx/mtx.c` (13 fns), `mtx/mtxvec.c` (2), `mtx/mtx44.c` (2), `vec.c` (5)
cover `.text 0x8025DF74..0x8025E9AC` (21 functions). **All 21 are wired from C
at 100%** (mtx.c 12, mtxvec.c 2, mtx44.c 2, vec.c 5); **C_MTXFrustum
(0x8025E774) was the last park and is now solved**: per-site `(2.0*n)`
product temps (`prod0`/`prod1`, `prod * tmp`) fix the two swapped `fmuls`
operand pairs with no allocation drift — a single reused temp rotates the
allocation, anonymous inline products swap the fmuls back
(`docs/parkings/solved/39-mtx-c-mtxfrustum.md`). Split re-claimed to
`0x8025E774..0x8025E8A8`.
C_MTXLightOrtho was un-parked 2026-08-20: SFA-Decomp's mtx.c (lines 480-517)
proves the SDK original was an inline-asm body - the plain-C coin-flip was a
phantom C form. DOL is byte-clean. The names were
already committed to `symbols.txt` (PSMTXIdentity/PSMTXCopy/…/
PSVECCrossProduct, plus `cosf`/`sinf` = fn_80271070/fn_80271170).

**The extern route solved the pool (SI §8.9 precedent):** retail's `.sdata2`
pool carries dead-function constants a fresh compile cannot reproduce, so any
C literal in the mtx sources emits a compact pool at the wrong addresses and
shifts the r2/r13 base. Instead the C objects emit **no `.sdata2`**: all
constants are `extern` into inner labels split out of the auto-asm blob
(`lbl_803CAF8C` shrunk to 0x24; per-constant labels `lbl_803CAFB0/B4/C0`,
`lbl_803CB010/14/18/1C`, `lbl_803CB06C/70` in `.sdata2`; Unit01
`lbl_803CA358/360` in `.sdata`). This works because the build's patch step
converts r2→r13 accesses and the auto-asm pool stays at its retail addresses.

**The last parked function** was a pure-regalloc coin-flip (doc-10 class): for
C_MTXFrustum, the `tmp`-statement form compiled with retail's exact registers
but 2 `fmuls` emitted commutative operands swapped (2 words off). Inlining the
division after the product fixed the order but rotated the allocation (11
diffs). The solved form names each site's product in its own temp
(`prod0`/`prod1`, `prod * tmp`) — no rotation, no swaps. Full analysis in
`docs/parkings/solved/39-mtx-c-mtxfrustum.md` (the wired source is canonical;
pre-solution reconstructions were removed, surviving in git history).

### 8.17 `__ppc_eabi_init.c`: `#pragma peephole off` + the `_ctors`/`_dtors` mwld trap

Wiring the runtime-init sliver (0x80267C54..0x80267D5C: `__init_user`,
`__init_cpp`, `abort`, `exit` (with inlined `__fini_cpp`), `_ExitProcess`)
hit two traps:

1. **`#pragma peephole off` is REQUIRED.** Retail keeps two dead
   `b .+4; b .+4` chains before the loop-entry branch, and schedules the
   `lis/addi` address load *after* the full prologue. The peephole pass
   removes both (one clean `b test`, `lis` hoisted to the top), producing a
   4.8%-off function that is structurally unfixable by source form alone.
   With the pragma, the plain `for (constructor = _ctors; *constructor;
   constructor++)` body is byte-exact. tww's `__ppc_eabi_init.cpp` shows the
   same `#pragma peephole off` around `__init_cpp`.

2. **Never reference the linker-generated `_ctors`/`_dtors` names from C.**
   The declared externs (`__declspec(section ".ctors") extern void
   (*_ctors[])();`) make mwld crash with `internal linker error: File:
   'ELF_PPC_EABI.c' Line: 2687` — even after defining `_ctors`/`_dtors` in
   `ldscript.tpl`. The tables are empty (all-NULL) and live in auto-asm as
   `lbl_80310AB8`/`lbl_80310AC0`; reference those labels directly from C
   instead. Bytes are identical (relocations resolve to the same addresses),
   and `symbols.txt` keeps the `_ctors` label purely for readable WANT asm.

---

## References

- `docs/gamecube-decomp-plan.md` §5 — the *compiler* discovery (ProDG ngccc vs mwcc).
- `AGENTS.md` — operational handoff (build/verify commands).
- zeldaret/tp (`../tp`) — source of `libs/dolphin` (2004 build).
- zeldaret/tww (`../tww`) — the **exact Sep-2002 base** (8 modules, byte-identical version strings; see §6.1).
- bfbbdecomp/bfbb (`../bfbb`) — Apr-2003 rebuild of 0x2301, closest source for AX/EXI/GX-drift (see §6.1).
- doldecomp/mkdd (`../mkdd`) — Jul-2003 SDK, incomplete (GX empty).
