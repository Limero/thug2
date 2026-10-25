# libs/libgcc — GCC low-level runtime (ProDG `__divdi3` family)

The DOL region `0x80273480–0x80274A78` is SN's **gcc-2.95.2 `libgcc2.c`
objects, one TU per `-D L_xxx`**, compiled with small-data ON (see
`docs/parkings/43-sda-prebuilt-runtime-zone.md`). It is GCC's own runtime,
not SN newlib — so it lives here, not in `libs/runtime/` (whose charter is
"original SN newlib files via crashwoc").

## Layout

- Upstream reference (`gcc/libgcc2.c` + `longlong.h` from
  `github.com/gcc-mirror/gcc`, tag `releases/gcc-2.95.2`) is NOT kept in
  this repo (GPL sources under a CC0 tree — fetch it yourself when porting
  further TUs). The ports below copy its C-fallback *spellings* only
  (never `#include` it — its inline asm is unprobed under ngccc, and
  global header inclusion risks `__rlwimi`-style shadowing, §6ax-220e).
- `src/__divdi3.c`, `src/__udivdi3.c`, `src/__umoddi3.c` — the wired
  build inputs. Faithful **adapted ports** (not verbatim upstream — the
  verified forms need `static __inline__` helpers, the always-NULL `rp`
  param stripped, s32 union members; verbatim would not match, §6ax-217).
  Symbols keep their `fn_8xxxxxxx` names for now; rename to `__divdi3`
  etc. (sweeping caller decls) is a later pass.

## TU ↔ symbol map

| TU (`-D`) | Symbol | Range | Table copy |
|---|---|---|---|
| `L_ashldi3` | fn_80273480 | matched in game lib (src/fn_80273480.c) | — |
| `L_ashrdi3` | fn_802734C0 | matched in game lib (src/fn_802734C0.c) | — |
| `L_divdi3` | fn_8027353C | `0x8027353C–0x80273AB8` | lbl_803CBC3C |
| `L_moddi3` | fn_80273BA8 | `0x80273BA8–0x802740DC` | lbl_803CBD3C |
| `L_udivdi3` | fn_802740FC | `0x802740FC–0x802745E0` | lbl_803CBE3C |
| `L_umoddi3` | fn_802745E0 | `0x802745E0–0x80274A78` | lbl_803CBF3C |

Each TU carries its OWN `static const __clz_tab` → the distinct `.sdata2`
copies above; `-G256` is the probed SDA threshold.

## Why the TUs are ports, not verbatim wrappers (measured 2026-09-05)

Wiring `libgcc2.c` verbatim was attempted and fails on TWO independent
grounds (headers `tconfig.h`/`machmode.h`/`defaults.h`/`stddef.h`
fabricated in a scratch dir — ngccc ships none of them):

1. **Private static table.** Each TU defines its OWN `static const
   __clz_tab[256]`. It cannot be redirected to the game's extern copy
   (`lbl_803CBC3C`…): any `#define __clz_tab lbl_…` also renames the
   definition into a conflicting static (still emitted), and the emitted
   copy cannot reach the link — the ngccc rule objcopies `-R .sdata2`,
   and the auto-asm data units already carry those bytes (carving them
   out needs LCF + dtk data-surgery; the §4n wall family). The
   `extern u8 lbl_…[256]` line in each port IS the wireable form.
2. **`.text` still differs by table addressing.** Verbatim `-D L_divdi3`
   compiles self-contained (upstream auto-pulls `L_udivmoddi4` as
   `static inline` — no helper calls), but its 3 table sites emit
   `lis+addi+lbz` (1416B) where the game uses SDA-anchored addressing
   (1404B); the masked diff is a pure shift cascade from those sites.

So the ports above (upstream logic, `static inline` helper structure kept,
table via extern lbl) are the maximally-upstream wireable form. Do NOT
retry verbatim wrappers without solving table ownership first.

## Build & verify rules (all load-bearing)

- Per-object `extra_cflags=["-msdata=eabi", "-G256"]`; mw `ProDG/3.9.3`.
- Verify ONLY with `tools/sda_verify.py` (plain sweep false-DIFFs SDA21
  words; never diagnose from `flagdiff.py` alone — doc 43).
- `promote_wip.py` / `add_gen_leaves.py` only know `src/fn_*.c` + the game
  lib — libgcc promotions are manual (register + splits + rebuild + cmp).
- **Object-name rule** (the §4d gotcha): the `Object()` name must equal the
  splits unit path (`"libgcc/__divdi3.c"`), with an explicit
  `source="__divdi3.c"` since the files sit flat under `src_dir`. A bare
  `"__divdi3.c"` name silently misses the objects-dict lookup → the unit
  gets no `base_path`, no `sdk` category, and **no diff scores** (the
  functions still link byte-identical, but PROGRESS never credits them).
- Explicit non-goals: fn_80274A78/AC4 (`__save_gpr`/`__restore_gpr`,
  doc 45 — not expressible in C, stay auto-asm).
