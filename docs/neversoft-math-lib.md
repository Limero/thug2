# Neversoft math library — identification of the DOL math region

**Status:** identification complete, DOL-verified (2026-08-16).
**Region:** `0x80269EB0`–`0x80274A78` (tail of `.text`). This doc records which
functions belong to the game's own float math library vs. dead-linked MSL
baggage, and who calls them.
**Companion to:** `docs/dolphin-sdk.md` (SDK library, not math),
`docs/gamecube-decomp-plan.md` §4b/§5 (ProDG compiler).

---

## 1. tl;dr

- The DOL's math region contains **two distinct libm layers**:
  1. **MSL double-precision fdlibm** (`0x8026B550`–`0x8027052C`): **zero callers
     in the whole `.text` and zero data pointers** — dead-linked MSL baggage
     (fdlibm doubles mirroring
     (the corresponding in-tree MSL fdlibm source snapshot has since been
     pruned; the DOL classification is based on the disassembly and zero-call
     evidence).
  2. **The game's own single-precision float math library**
     (`0x8027052C`–`0x80272044`): hand-written float libm with **~600 call
     sites** across game code (shared-callers; sinf has 67, cosf 70, sqrtf 50).
     This is the "Neversoft math library".
- The float lib is **pure single-precision**: bit-trick exponent probing
  (`stfs`/`lwz`/`clrlwi`), single-precision constants in `.sdata2`, no double
  promotion anywhere. It is *not* MSL — MSL's float wrappers promote to double.
- The game builds **precomputed sin/cos lookup tables at startup** using sinf/cosf
  (fn_800036C8 + siblings, §4); the script engine's `Script*Math` commands and
  engine code consume both the lib and the tables.

---

## 2. Region map (`0x80269EB0`–`0x80274A78`)

| Range | Contents | Status |
|---|---|---|
| `0x80269EB0`–`0x80269EF8` | tiny redirect stubs (8/0x38 bytes) | MSL glue |
| `0x80269F30`–`0x80269F4C` | `tolower`, varargs prologue helper | MSL |
| `0x8026A024`–`0x8026AD98` | `vprintf`, printf family, `memcmp`, `memcpy`, `memmove`, `memset` | MSL |
| `0x8026B04C`–`0x8026B4FC` | string functions, `strlen`, `strncmp`, `strncpy` | MSL |
| `0x8026B550`–`0x8027052C` | **MSL double libm** (fdlibm: e_asin/e_acos/e_pow-shaped) | dead-linked, 0 callers |
| `0x8027052C`–`0x80272044` | **Neversoft float math lib** (§3) | live, ~600 call sites |
| `0x80272044`–`0x80274A78` | double/strtod-shaped helpers (0x80272094 0x888, 0x8027291C 0x884, …) | dead-linked, 0 callers |
| `0x80274A78`+ | `__save_gpr`/`__rest_gpr` runtime glue | runtime |

Function sizes inside the double zones (0x4E8, 0x1444, 0x12F4, 0x888, 0x884,
0x57C, 0x534, 0x4E4, 0x498) are the classic fdlibm/strtod-sized bodies; they
are forced into the link by the CRT archive even though nothing calls them.

---

## 3. The Neversoft float math library

### 3.1 Public API functions (single caller each verified via full-text caller graph)

| Addr | Identity | Direct callers in `.text` | Evidence |
|---|---|---|---|
| `0x80270CA4` | `sqrtf` | **50** | `ScriptSqrt` (`bl 0x80270CA4`) + 49 engine fns |
| `0x80271070` | `cosf` | **70** | `ScriptCos` (`bl 0x80271070`); startup table builder fn_800036C8 |
| `0x80271170` | `sinf` | **67** | `ScriptSin` (`bl 0x80271170`); fn_800036C8 |
| `0x8027124C` | `tanf` | 6 | `ScriptTan` (`bl 0x8027124C`) |
| `0x80270D9C` | `atanf` | 3 | `ScriptATan` (`bl 0x80270D9C`); π/2-quadrant constants at `0x803CA6F0` |
| `0x80270A84` | `atan2f` | 8 | takes f1,f2 (y,x); NaN/Inf guard vs `0x7F800000`; x==1.0 → `bl atanf` |
| `0x8027060C` | `acosf` | 12 | `ScriptACos` (`bl 0x8027060C`) |
| `0x80270858` | `asinf` | 4 | `ScriptASin` (`bl 0x80270858`) |

### 3.2 Internal kernels (called only from the API tier)

| Addr | Identity | Callers |
|---|---|---|
| `0x80271948` / `0x80271A34` | sinf/cosf argument-reduction/poly kernels | `0x80271070`, `0x80271170` |
| `0x80271AE0` / `0x80271CF4` | tanf kernels | `0x8027124C` |
| `0x8027052C` | helper (2 callers) | fn_802548F8, fn_80254E80 |
| `0x80270FAC` | float classify/magnitude helper (1 caller; loads `1e30` = `0x7149F2CA` from `-0x7B44(r13)`) | fn_800BFDD8 |
| `0x80271444`, `0x80271538`, `0x802715E4` | shared helpers | fn_80270174 (double side) + `0x8027052C` |
| `0x802712CC`, `0x802712F0` | double-side classification glue (physically inside the float run) | fn_802704A4/fn_8026F55C/fn_80272094 |

### 3.3 Signature traits (how to recognize the float lib in other Neversoft games)

- **Pure single precision**: every op is `f*`+`s` (frsp/fmuls/fadds/fdivs), and
  float bits are probed via `stfs` to stack + `lwz` + `clrlwi` (never
  `fctiwz`/double load).
- **Own `.sdata2` constant pools** (r13-addressed), e.g. the atan/atan2 quadrant
  table at `0x803CA6F0`–`0x803CA73C`: 0.5, ±π/4, ±π, ±π/2, ±3π/4, 1.5e-7,
  1e30, 1, 2, 1.5, −1.
- **Single callers from the `Script*` command wrappers** (ScriptSin/Cos/Tan/Sqrt/
  ATan/ACos/ASin) plus the 0x80003xxx boot-time trig-table builders.

---

## 4. Startup trig-table builders (the fast-trig layer on top of the lib)

A family of early `.text` functions precomputes interleaved sin/cos lookup
tables using sinf/cosf:

| Addr | Behavior |
|---|---|
| `0x800036C8` | builds table at `0x80290AE0` (rodata2): per-`0x10`-byte entry, `f1 = i·(range)`; `bl 0x80271170` (sin) → `stfs f1,0(r31)`; `bl 0x80271070` (cos) → `stfs f1,4(r31)`; 0x10-byte stride = interleaved [sin,cos] pairs; loop `cmpwi r30,0x76; ble` |
| `0x80003830`, `0x80003E0C`, `0x80003EB0`, `0x80003F54`, `0x80003FF8`, `0x80004404` | siblings sharing the same sinf/cosf call pattern (callers of `0x80271070`/`0x80271170` each) |

`ScriptRotateVector` (`0x8010F5E0`, size 0xD8C) calls `0x80003E0C`/`0x80003F54`
directly — the script engine consumes the precomputed tables, not the lib.

---

## 5. Methodology notes (reusable)

- **Full-text caller graphs: capstone `md.disasm` on the whole `.text`
  stops silently at the first invalid byte** (decoded only 473 insns to
  `0x80003C00`). Use a chunked loop with try/except around 64-byte slices to
  reach the end (590,040 insns, last `0x8028E034`). See the scripts used in
  this investigation (kept in `/tmp` conventions, §5 tools hygiene).
- **Caller attribution**: `bisect_right(function_starts, call_addr) - 1` over
  `symbols.txt` function starts; direct `bl` only (indirect `mtlr`+`blrl`
  dispatch is handled separately).
- **Dead-link check**: a cluster with zero direct `bl` callers AND zero pointer
  words in non-`.text` sections is dead-linked archive baggage (MSL double
  libm here). Note the rodata2 pointer run at `0x8028FF0C`+ (111+ words of
  `0x802740DC`, a thunk to `0x80274B20`) is the script-command table, not math.

---

## 6. Follow-up candidates

- **Rename symbols**: add `scope:global` names (e.g. `Sinf`, `Cosf`, `Sqrtf`,
  `Atanf`, `Atan2f`, `Asinf`, `Acosf`, `Tanf`) for the 8 API functions so
  `gen_leaves`/`promote_wip` auto-name future matches (M6.76 rename workflow:
  `tools/rename_script_cmds.py` pattern or manual symbols.txt edit).
- **Matching**: the 8 API functions are FPR-saving (the §4c frame quirk
  applies; `volatile double _dummy;` recipe / M5.0b auto issue-01 sweep).
  sqrtf/sinf/cosf with 50–70 callers each are the highest-value anchors in
  this region, but are mid-size kernels (argument reduction + polynomial
  evaluation) — m2c draft + NEAR loop is the realistic path.
- **Double libm**: leave as dead asm-carried baggage; do not wire MSL
  `Double_precision/` sources unless the rodata2 script table or another
  indirect dispatch is proven to reach them.

---

## 7. Provenance proof vs stock newlib (2026-09-29 — the "still libc?" challenge)

Liveness alone cannot prove authorship (game code calls `memcpy` too), so
the float lib was diffed algorithm-for-algorithm against newlib's actual
single-precision sources (`libm/mathfp/sf_sqrt.c`, `sf_sine.c` —
Cody & Waite lineage, vintage 1998, stable since). It matches none of them:

| trait | newlib mathfp | DOL float lib |
|---|---|---|
| `sqrtf` special values | `numtestf` switch + `errno = EDOM/ERANGE` | raw exponent compare (`rlwinm`/`lis 0x7f80`); NaN via `x-x`; **no errno** |
| `sqrtf` core | `frexpf` → `y = 0.41731 + 0.59016·f` → 2 Heron iterations → `ldexpf` | `k = i>>0x17` halve + subnormal shift loop, pure bit ops |
| `sqrtf` calls | ≥3 (`numtestf`, `frexpf`, `ldexpf`) | **0 — verified leaf** (`readelf -r`: only intra-`.text` REL14/REL24) |
| `sinf` structure | single `sinef`: `N = y·(1/π)±½`, `y = fabs(x)−XN·π`, inline 4-term Horner | dispatcher: small-arg fast path (`ix ≤ 0x3F490FD8`), NaN guard, hi/lo **pair** from reducer `fn_80271CF4`, `switch & 3` into kernels `fn_80271A34`/`fn_80271948` |
| `sinf` constants | `HALF_PI`, `ONE_OVER_PI`, `YMAX`, 4-term `r[]`, `errno` | none of these; no `errno`, no doubles anywhere |

The kernel ABI itself (`s32` flag + `f32` hi/lo pair) exists in no shipped
libm (newlib, fdlibm, MSL — whose float wrappers promote to double, which
this lib never does). Conclusion stands: bespoke single-precision game
libm, game module. It shadows libc names at the C ABI (`sqrtf`, `sinf`,
…) but shares no source with them — which is exactly why "called from
game code" and "looks like libc" were both true and both insufficient.

Date objection closed (2026-09-29): the compared files predate the game —
git history shows `sf_sqrt.c` functionally unchanged since 2000-03-13
(one-line `#ifdef` fix) and `sf_sine.c` untouched since its 2000-02-17
import, so every 2001–2003 newlib snapshot (incl. SN's) contained the
compared sources verbatim. "SN shipped a modified newlib" remains
logically possible but unevidenced and uneconomical: vendors port newlib
via machine layers (the wired crashwoc-verbatim libc files prove SN's
tree == upstream for libc), and a rewrite that also drops `errno`
(newlib sets `EDOM`/`ERANGE` unconditionally in-source; this lib never
touches `_impure_ptr`) would be a ground-up redesign, not a tune.
Falsifier, if ever available: byte-identical implementations in another
studio's ProDG-built DOL would prove toolchain origin.