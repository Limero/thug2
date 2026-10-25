# runtime

SN ProDG newlib C runtime (not MSL), matching the retail build. Built with
ngccc `ProDG/3.9.3` and `cflags_game` (the game toolchain, not mwcc).
Reference source: the crashwoc decomp's `src/runtime/libc` tree — the exact
SN newlib revision; all wired functions are those sources verbatim (with
`#include "string.h"` swapped for the self-contained `types.h` +
`size_t` typedef). Do not hand-write these — copy them (doc 22 lesson:
m2c-style s32/goto reconstructions never compile back byte-exact, the
canonical newlib source with distinct pointer variables does).

## Wired (matching)

- [x] `tolower` (0x80269F30, 0x1C)
- [x] `memcmp` (0x8026AD98, 0x90)
- [x] `memcpy` (0x8026AE28, 0xA4)
- [x] `strcat` (0x8026B0E0, 0x90)
- [x] `strchr` (0x8026B170, 0x9C)
- [x] `strcmp` (0x8026B20C, 0xA8)
- [x] `strcpy` (0x8026B2B4, 0x84)
- [x] `strlen` (0x8026B338, 0x6C)
- [x] `strncpy` (0x8026B484, 0xCC)
- [x] `memchr` (0x8026F20C, 0xC0)

## Wired as named sources (matching, promoted drafts moved from `src/`)

These were solved from the doc 22 recipes but promoted as game-module
`src/fn_*.c` units; they now live here under their real names (same bytes,
`runtime` lib owns the `Object`). Unlike the crashwoc-verbatim files above
they are promoted-draft sources, not original newlib files — do not
"restore" them from crashwoc.

- [x] `vprintf` (0x8026A024, 0x34) — `vprintf.c` (`-msdata=eabi -G4`)
- [x] `memmove` (0x8026AECC, 0xEC) — `memmove.c`
- [x] `memset` (0x8026AFB8, 0x94) — `memset.c`
- [x] `strcasecmp` (0x8026B04C, 0x94) — `strcasecmp.c`
- [x] `strncmp` (0x8026B3A4, 0xE0) — `strncmp.c`
- [x] `atoff` (0x8026A058, 0x24) — `atoff.c` (`strtof(s, NULL)` wrapper, matching newlib's stdlib/atoff.c verbatim; the
  double return rides in f1, bytes match the old void form)
- [x] `rand` (0x8026AA08, 0x24) — `rand.c` (newlib LCG over
  `_reent._rand_next` @ +0x58; matches crashwoc `rand.c` semantics
  verbatim; companion `srand` is dead-stripped — 0 callers)
- [x] `free` (0x8026AA2C, 0x3C) — `free.c` (heapless stub: ignores its arg,
  OSPanics with the `*** Library error *** ... 'free'` message at
  `lbl_802B1EB4` + caller address)
- [x] `isdigit` (0x8026E57C, 0x14) — `isdigit.c` (`(_ctype_+1)[c] & _N(4)`)
- [x] `isspace` (0x8026E590, 0x14) — `isspace.c` (`(_ctype_+1)[c] & _S(8)`)
- [x] `__getreent` (0x8026E5A4, 0x8) — `__getreent.c` (returns newlib's
  `_impure_ptr`; sole active caller is errno-setting code)
- [x] `floor` (0x8026E5DC, 0x174) — `floor.c` (fdlibm logic via rodata2
  doubles; the game carries a second floor copy in the double zone,
  `fn_80270290.c` with `.sdata` constants)
- [x] `strstr` (0x8026B550, 0x68) — `strstr.c` (`-fno-gcse`; the old
  "92.9% park" note was stale — the promoted source was already wired and
  matching in the game module before the move here)

Key correction this round: `lbl_803CA420` (`.sdata`) is newlib's
`_impure_ptr` (pointer to the global `struct _reent`) — not "MSL printf
state" as older notes called it. Evidence: `rand` steps `_rand_next` @
+0x58 through it (crashwoc `rand.c` verbatim), `vprintf` reads `_stdout` @
+0x8 through it (crashwoc `vprintf.c` verbatim), `__getreent` returns it,
and `strtof`/math set `errno` through it (`reent->_errno = ERANGE`, same
idiom as crashwoc `strtol.c`).

Known objdiff artifact (same as the M4.11 r13-inline-asm undercount):
`rand` and `__getreent` read via `lwz rX,-0x7e60(r13)` inline asm, which
defeats dtk/objdiff function attribution — PROGRESS lists them `- [ ]` /
0 matched even though their bytes are in the identical DOL. `cmp` of the
linked DOL is the ground truth here, not the per-function score.

## Wired as `fn_*` (matching, no known name — kept address-based)

- [x] `fn_8026D1B4` (0xD4, printf writer twin of `fn_8026BBC4`) —
  `fn_8026D1B4.c` (`-msdata=eabi -G4`)
- [x] `fn_8026BBC4` (0xD4, printf writer twin of `fn_8026D1B4`) —
  `fn_8026BBC4.c` (`-msdata=eabi -G4`; verbatim port of the D1B4 body,
  LINK-SIM EXACT first try)
- [x] `fn_8026E5B8` (0x24, thin wrapper forwarding `_impure_ptr` to
  `fn_8026E5AC`) — `fn_8026E5B8.c` (`-msdata=eabi -G4`)
- [x] `fn_8026AA68` (0x330, `strtof` hypothesis) — `fn_8026AA68.c`
  (`-msdata=eabi -G4`; the old "66/205 park" note was stale — the promoted
  source was already wired and matching in the game module before the move
  here; name still unproven, hence address-based)
- [x] `fn_8026B5B8` (0x5C, decimal-string increment rounding helper)
- [x] `fn_8026B614` (0x4C, in-place string reverse; `strrev` candidate,
  spelling unproven)
- [x] `fn_8026B660` (0x7C, `itoa` hypothesis)
- [x] `fn_8026E5AC` (0xC, returns rodata2 table `lbl_802B218C`)
- [x] `fn_8026EDA8` (0x148, `log10`) — (`-msdata=eabi -G8`)
- [x] `fn_8026EEF0` (0x31C, Japanese encoding analyzer)
- [x] `fn_80270174` (0xE0) — (`-msdata=eabi -G8`)
- [x] `fn_80270254` (0x3C, `fabs`)
- [x] `fn_80270290` (0x15C, second `floor` copy) — (`-msdata=eabi -G8`)
- [x] `fn_802703EC` (0xB8, `frexp`) — (`-msdata=eabi -G8`)
- [x] `fn_802704A4` (0x88) — (`-msdata=eabi -G8`)
- [x] `fn_80272044` (0x50, double-side glue; sole caller is the
  `fn_802712F0` draft) — (`-fno-schedule-insns -fno-schedule-insns2`)
- [x] `fn_802731A0` (0xC8, `floorf`)
- [x] `fn_80273268` (0x11C, `scalbnf`) — (`-msdata=eabi -G4`)
- [x] `fn_80273384` (0x34, `copysignf`) —
  (`-fno-schedule-insns -fno-schedule-insns2`)
- [x] `fn_802733B8` (0x90)
- [x] `fn_80273448` (0x38, init guard calling `fn_802733B8`)
- [x] `fn_80274B10` (0x10, noreturn `abort()` stub) + `lbl_80274B20.c`
  (0x2C companion fragment; kept as separate objects — see the header note
  in `fn_80274B10.c`)
- [x] `fn_80274B4C` (0x34) / `fn_80274B80` (0x6C, init-once accessor)

All of the above moved from `src/fn_*.c` (game module) in one batch —
same bytes, `runtime` lib owns the `Object` (extra_cflags preserved).

## Deliberately left in the game module (`src/fn_*.c`)

Not everything in the `0x8026xxxx..0x80274xxx` span is runtime. Do NOT
"migrate" these without new evidence:

- The **Neversoft single-precision float math lib**
  (`0x8027052C..0x80272044`: `fn_8027052C`, `sqrtf`, `fn_80270FAC`,
  `cosf`, `fn_8027114C`, `sinf`, `fn_802712CC`, `fn_80271444`,
  `fn_80271538`, `fn_80271A34`) is **live game code** — ~600 game-code
  call sites (`ScriptSqrt/Sin/Cos`, startup table builder fn_800036C8).
  It was briefly moved here and moved back; see
  `docs/neversoft-math-lib.md`. (The double-zone `floor`/`fabs`/`frexp`
  copies below `0x8027052C` stay here — the boundary is the documented
  `0x8027052C` line.)
- `fn_80269EB0`/`fn_80269EB8` (8B GQR-setter leaves) — game/OS code,
  not newlib.
- `fn_80273480`/`fn_802734C0` (`__ashldi3`/`__ashrdi3`) +
  `fn_80273500`/`fn_80273B68`/`fn_802740DC` (in-span helpers) — libgcc
  TUs inside `0x80273480..0x80274A78`; they belong in `libs/libgcc/`
  (follow-up), not here — see `libs/libgcc/README.md`.
- `fn_80274A78`/`fn_80274AC4` (`__save_gpr`/`__restore_gpr`) — EABI
  runtime glue claimed by neither lib README; leave alone (doc 45).

## Hypotheses for the parked drafts (not renamed — tooling globs `fn_*`)

File renames of parked `src/wip/` drafts are deliberately deferred: promotion
tooling only globs `fn_*.c`, so a renamed draft would miss sweeps. Rename on
promotion instead (callee tokens for already-wired names are updated then;
the `strtof` draft already uses `isspace`/`isdigit`/`__getreent`).

- [ ] `fn_8026A07C` (0x98C) — HIGH: `qsort` (Bentley/McIlroy; algorithm map
  verified in the draft header)
- [ ] `fn_8026B660` (0x7C) — MEDIUM: `itoa(value, buf, base)` (digit table
  `lbl_8030B1C4` = `"0123...xyz"`, sign handling, calls the reverse
  helper; called by the float→ASCII core for exponents; `utoa`/`ltoa`
  spellings not excluded)
- [ ] `fn_8026B6DC` (0x4E8) — MEDIUM: float→ASCII core (`ecvt`-class; calls
  `floor`, `fmod`, the increment helper and `itoa`; 5-arg worker shape has
  no standard name — do not force `ecvt`/`fcvt`)
- [ ] `fn_8026BBC4` (0xD4) + `fn_8026D1B4` — MEDIUM-LOW: buffered
  stdout/stderr writers (both 212B twins flushing via the EXI debug
  channel `fn_8028DFE8`; direction assignment unproven)
- [ ] `fn_80269F4C` (0xD8) — unknown varargs helper, m2c baseline

### Parked drafts exist (`src/wip/`, not yet promotable)

- [ ] `fn_80269F4C` (0xD8) — varargs/`__va_arg` helper, m2c baseline
- [ ] `fn_8026A07C` (0x98C) — printf-family formatter driver; structural
  rebuild complete, parked on the big-function allocator wall (want stmw
  r17 / frame 0x48 vs ~4 saved regs reachable)
- [ ] `fn_8026B660` (0x7C) — MEDIUM: `itoa(value, buf, base)` (digit table
  `lbl_8030B1C4` = `"0123...xyz"`, sign handling, calls the reverse
  helper; called by the float→ASCII core for exponents; `utoa`/`ltoa`
  spellings not excluded)
- [ ] `fn_8026B6DC` (0x4E8) — structural rebuild: %e/%f float→ASCII;
  walls are doc-14 pool routing + shared fctiwz-slot schedule + doc-28 CR
- [ ] `fn_8026BC98` (0xD8) — printf float-dispatcher → `__svfprintf_r`
- [ ] `fn_8026BD70` (0x1444) — `__svfprintf_r` (own TU; duplicate literals
  prove the float/no-float engine split)
- [ ] `fn_8026D288` (0x12F4) — `__svfiprintf_r` (own TU)
- [ ] `fn_8026E750` (0x35C) — fdlibm `__ieee754_fmod` hand rebuild
- [ ] `fn_8026EAAC` (0x2FC) — fdlibm `__ieee754_log`
- [ ] `fn_8026EDA8` (0x148) — `log10` (hand-tuned from the floor lever)
- [ ] `fn_8026EEF0` (0x31C) — Japanese encoding analyzer, m2c baseline

### Notes

- The printf engines are an SDA small-data zone (doc 43): verify via
  `tools/sda_verify.py` with `-msdata=eabi -GN`, promote by manual
  `Object(extra_cflags=...)` registration — standalone sweeps false-DIFF
  on unmasked SDA21 words.
- Past `memchr` (`0x8026F2CC+`) the neighbors are libm, not libc:
  `fn_8026F55C` (pow), `fn_8026FD2C` (sqrt), `fn_8026FF40` (tanh) —
  doc 44 wall (entry-staging/homing). The Neversoft float lib past
  `0x8027052C` is game code, not runtime (`docs/neversoft-math-lib.md`).
- Full zone analysis, recipes and history: `docs/parkings/22-msl-runtime.md`.
