# Issue 06 — Paired-Single (PS) math ops

**Status:** EMISSION BLOCKER FULLY CLOSED (M5.0t, 2026-08-26) / **PARK HOME STILL ACTIVE**. Every Paired-Single opcode known in the DOL decodes and emits from plain C under ProDG 3.9.3 `-mps-float` — whole-.text census: **146 X-form indexed ops + 1,862 A-form arithmetic / 35,051 D-form quantized loads/stores** all map to verified builtins/deref forms; **zero unemittable PS opcodes remain** (see M5.0h/M5.0q/M5.0t below). The 7-function retry round (docs/parkings/06-paired-single-ops.md:856) confirmed in-body. What keeps this doc open is **NOT a PS emission wall** but the generic FPR/GPR-coloring + scheduler tie-break walls (M5.0o/M5.0r class: fn_801F7B04 29.8%, fn_801B1278 20.6%, fn_800BB9BC 2.4% ...). Those are tracked here because until this round they were masked by the opcode wall; as they are cracked they migrate to the generic docs (15/32/33). Do NOT move to `solved/` until the PS-function park count drops — this file is now the **PS knowledge base**, not a blocker doc.

## The problem

Some functions contain **Paired-Single** (PS) floating-point instructions
(`psq_l`, `psq_st`, `ps_add`, `ps_muls0`, `ps_madd`, `ps_merge00`,
`ps_sum0`, …). These are Gekko (Dolphin CPU) extensions. The project's
configured compiler was ProDG **3.7** ("2.95.3 SN BUILD v1.46"), which
cannot emit them from C — so those functions were parked as unmatchable.

How widespread: a PS-aware scan of the whole `.text` section found
**~50,310 PS instructions (≈7.5% of all text instructions) in ~895
functions**. The game was unmistakably compiled with a PS-capable SN
Systems compiler — PS is a core part of the game's math code, not a
hand-written asm corner.

## M5.0 investigation result — the compiler CAN emit PS (ProDG 3.9.3)

The repo ships **ProDG 3.9.3**, whose `cc1.exe` identifies as:

```
2.95.3 SN BUILD v1.76 for Nintendo Gamecube
```

and which contains the **full PS instruction templates** (`ps_muls0`,
`ps_madds0/1`, `ps_merge00/01/10/11`, `ps_sum0/1`, `ps_sel`, `ps_res`,
`ps_rsqrte`, `ps_cmpo0`, …) plus the internal expansion names
`b_muls0ps3`, `b_merge00ps3`, `b_sum0ps3`, `b_madds0ps3`. 3.7 (v1.46) and
3.8.1 (v1.54) have only a subset; 3.9.3 is the full compiler.

### How to emit PS from C

The SN compiler exposes PS through a builtin type `__ps_t` plus the flag
`-mps-float`:

```c
void ps_test(__ps_t *a, __ps_t *b, __ps_t *out) {
    __ps_t x = a[0];
    __ps_t y = b[0];
    out[0] = x + y;   /* ps_add  */
    out[1] = x * y;   /* ps_mul  */
}
```

```sh
SN_NGC_PATH=build/compilers/ProDG/3.9.3 \
  build/tools/wibo build/compilers/ProDG/3.9.3/ngccc.exe \
  -O2 -G0 -mcpu=750 -mps-float -fno-common -c ps.c -o ps.o
```

produces `psq_l`, `ps_add`, `ps_mul`, `psq_st` (verified). Pointer casts
like `*(__ps_t *)&scalar_local` reproduce the
game's "store scalar to stack, reload as a pair" idiom (`stfs` → `psq_l`
→ `ps_mr`).

### M5.0h — the missing idioms ARE callable: SN Systems' SNAPS intrinsics

The "no intrinsic functions" claim above was WRONG — it only tested `__ps_*`
names; SN Systems' official Paired-Single API is **SNAPS**, a header of
macros over **`__builtin_ps_*`** GCC builtins, and 3.9.3 has them all:

- `strings build/compilers/ProDG/3.9.3/cc1.exe` contains
  `__builtin_ps_muls0`, `__builtin_ps_merge00`, `__builtin_ps_sum0`,
  `__builtin_ps_madd`, `__builtin_ps_add`, `__builtin_ps_mul`, `__ps_t`,
  plus the expansion templates `ps_muls0 %0,%1,%2`,
  `ps_merge00. %0,%1,%2`, `ps_sum0 %0,%1,%2,%3`.
- The source-level interface is documented in-tree at
  `include/dolphin/SN_PS.h` (macros over the builtins above). It defines:
  - `typedef float sn_ps __attribute__((mode(PS)));`
  - `#define PS_BUILD(hi,lo) *(sn_ps*)(float[]){(lo),(hi)}`
  - `ps_muls0(x,y)` → `__builtin_ps_muls0(x,y)`, `ps_merge00(x,y)`,
    `ps_sum0(x,y,z)`, `ps_madd(x,y,z)`, `ps_mul`, `ps_add`, `ps_mr`,
    `ps_sel`, `ps_rsqrte`, `ps_res`, the `psq_l/psq_st` family, GQR
    register defines.

So the two wanted idiom shapes are directly expressible as intrinsic calls
(not compiler magic to reverse-engineer):

```c
sn_ps p = ps_muls0(a, b);        /* pair x scalar-lane-0       */
sn_ps q = ps_merge00(a, b);      /* lane merge for dot-product */
sn_ps r = ps_sum0(a, b, c);      /* horizontal sum             */
```

**Executed 2026-08-20:** the draft was rewritten with the SNAPS intrinsics
and now emits the exact `ps_muls0`/`ps_merge00`/`ps_sum0` opcodes (536B vs
564B WANT). The remaining 28B/7-instruction gap is NOT the idiom — it is the
game's **spill pattern** (products stored to a stack pair slot + base
pointer `r28`, one reloaded) which 3.9.3 does not reproduce under any source
shape or flag tried. Two tooling gotchas found while rewriting, recorded for
the next attempt:
- 3.9.3 already ships the paired-single API as **builtins** (`__ps_t`, the
  `SN_PS_type` union with `.flt.hi`/`.flt.lo`, and every `__builtin_ps_*`).
  The in-tree `SN_PS.h` header is includable (one harmless "useless keyword"
  warning — its `SN_PS_type` typedef restates the builtin union), but adds
  nothing: its `ps_*` macros just alias `__builtin_ps_*`. Call the builtins
  directly.
- Reading a float out of a PS pair via `*(float *)&pair` ICEs 3.9.3
  (expmed.c:1115); use the builtin `SN_PS_type` union instead
  (`.flt.hi` = lane 0).
The exemplar stays PARKED on the regalloc spill; see the plan doc execution
findings for the full log.

### The compiler swap is safe for non-PS code

ProDG 3.9.3 produces **byte-identical output to 3.7 for non-PS code**:
- 110+ sampled promoted functions compiled identically under both.
- A FULL project rebuild with `"mw_version": "ProDG/3.9.3"` keeps
  `build/G2TE52/main.dol` byte-identical to the original.
- Therefore the project has been **switched to ProDG/3.9.3 globally**
  (committed M5.0) with zero regressions; PS matching is now possible.

### `-mps-float` must be PER-OBJECT, never global

`-mps-float` has a serious side effect: it forces **16-byte stack frames**
whenever a function saves an FPR (`stwu r1,-0x20; stfd f31,0x18(r1)` where
3.7/3.9.3-without-the-flag emit `stwu r1,-0x18; stfd f31,0x10(r1)`). This
is *exactly the issue-01 "+8 frame" quirk* (see
`solved/01-fpr-frame-quirk.md`). Verified: adding `-mps-float` to
`cflags_game` changed 14 FPR-saving matched functions (e.g. fn_80119A54's
frame 0x18→0x20) and the DOL no longer matched — so it was reverted.

Rules:
- **Global build flags: 3.9.3, NO `-mps-float`.** (DOL byte-identical.)
  Verified that even removing the issue-01 dummy fix does NOT make the flag
  viable globally: the game's 16/8 FPR frame split is orthogonal to PS usage
  (59 PS functions have native 8-aligned frames; 97 +8-framed functions have
  no PS at all) — see `solved/01-fpr-frame-quirk.md` §M5.0a.
- **Per-object:** `Object(Matching, "fn_8020D530.c",
  extra_cflags=["-mps-float"])` in `configure.py` — `extra_cflags` appends
  to the inherited lib cflags (verified in `tools/project.py` `Object.resolve`).
- When using `-mps-float` on a function, expect the issue-01 frame quirk
  to apply (frame = ngccc-native + 8 for FPR-saving functions); keep the
  `volatile double` dummy in mind for the other half of the split.

### Why fn_8020D530 still doesn't match (the remaining gap)

A full `__ps_t` reconstruction of `fn_8020D530` (564-byte WANT) compiled
structurally close (544B) with correct PS loads/stores/madds — but two
idiom differences remain, and neither was reproduced by any tested C shape:

1. **WANT block 1** computes three products with `ps_muls0` (pair ×
   scalar-lane-0), spills each product to stack (`psq_st`), then reloads
   and adds (`psq_l` + `ps_add`). 3.9.3 instead **fuses** into
   `ps_madd`/`ps_mul` and keeps values in registers. Tried: separate
   statements, volatile locals, explicit memory round-trips, register
   pressure — the non-fused form did not trigger.
2. **WANT block 2** uses a dot-product idiom `ps_merge00` + `ps_sum0`.
   3.9.3 generates scalar `fadds`/`fmuls` for every equivalent construct
   tried (`__ps_t` lane arithmetic, struct-of-two-floats, unions).

The compiler internally *has* the expansions (`b_muls0ps3` etc.), so a
source/flag combination that drives them exists — it just hasn't been
found. **M5.0h closes this: the exact callable intrinsics were located**
(`__builtin_ps_muls0`/`ps_merge00`/`ps_sum0` verified in 3.9.3's cc1.exe,
macros in the in-tree `SN_PS.h`) — see the M5.0h section above and
`docs/plan-snaps-doc06.md` for the rewrite recipe. The "newer than v1.76
compiler build" hypothesis below is now a RED HERRING: Sims2DECOMP (same
ProDG family, Day-0 compiler A/B test, 2026-06-09) proved **all four
installed ProDG point-versions are codegen-identical** (609 functions x 4
versions, zero flips), so point-version swaps cannot fix the idiom shapes.

**Retry data point (2026-08-26):** with the SNAPS intrinsics
place the draft now emits the correct ps_muls0/splat opcodes (536B vs 564B),
so the residual is NO LONGER fusion: WANT keeps a provably DEAD `sp20`
store + dead `psq_l` reload (§6x-89 want-extra class, retail kept redundant
insns GCC always removes) and splats the scalar via a pair(arg0+0x40).hi
lane read. Best new shape found this round was product-array staging
(+3.5% → 16.3%); park stands.

## M5.0c — the PS pair-copy leaf harvest (+7 matches, 8 parked on regalloc)

A survey of the ~863 PS functions (430 "simple" — small, frameless, mostly
`psq_l/psq_st` — + 433 complex) found **15 tiny frameless pair-copy
leaves**: pure `psq_l f0, off(rA), 0, 0; psq_st f0, off2(rB), 0, 0` chains
(+ an occasional `mr rX, rY` aliasing the store base, and a trailing
`blr`). These are exactly what `__ps_t` array assignment compiles to:

```c
void fn_80107A8C(__ps_t *arg1, __ps_t *arg2) {
    arg1[0] = arg2[0];
    arg1[1] = arg2[1];
}
```

compiles (with `-mps-float`) to exactly `psq_l f0,0(r4),0,0;
psq_st f0,0(r3),0,0; psq_l f0,8(r4),0,0; psq_st f0,8(r3),0,0; blr`
— byte-identical to the game. **7 of the 15 are promoted** (fn_8002464C,
fn_800DDD98, fn_800DDDAC, fn_801025B4, fn_80107A8C, fn_80107AA0,
fn_801AEDBC; 160B total). Workflow: `/tmp/gen_ps_leaves.py` parses the
copy chains → writes `src/wip/fn_*.c` → sweep with
`test_wip_drafts.py --addr-file ... --extra-cflags "-mps-float"` →
`promote_wip.py` now detects `__ps_t` drafts, compiles them with
`-mps-float`, stamps `// extra_cflags: -mps-float` into the promoted
header, and `add_gen_leaves.py` turns that marker into
`Object(Matching, ..., extra_cflags=["-mps-float"])` in configure.py.

**The other 8 stay parked on a pure register-allocation difference:**
the game emits `mr r9, r3` once and stores via r9; 3.9.3 stores directly
via r3. Every C shape tried (volatile pointer, `register __asm__("r9")`
hint, array params, const locals) still produces direct r3 stores — GCC
2.95.2/3 ignores the hint for this trivial case. Same root as the
`or. r0,r3,r3` scheduling artifact in M5.0b: a compiler-**build**
regalloc difference, not a source-level one. The drafts keep the exact
wanted asm in their header comments; if a matching compiler build is ever
found, they promote in seconds.

## M5.0d — the larger static-offset copy harvest (+3 matches, family exhausted)

The M5.0c generator capped candidates at 64B frameless leaves, so the
**larger frameless pure copies were still stubs**. A survey of all 442
simple-PS (no `ps_muls0`/`ps_merge`/`ps_sum` ops) functions shows the
family structure:

| Sub-family | Count | Matchable? |
|---|---|---|
| Frameless pure copies (all pair counts, 20-336B) | ~55 | YES — `__ps_t` array assignment |
| Frameless arithmetic (ps_add/mul/etc.) | 4 | NO — all are unrolled loops (568-700B) |
| Framed pure copies (2-36 pairs) | ~76 | NO — every one has calls or branches |
| Framed arithmetic / mixed | rest | NO — calls, loops, or complex ops |

**The extended generator (`/tmp/gen_ps_copies.py`)** now handles any
frameless static-offset copy (no size cap), including two new shapes:

1. **Direct large copies** — 8-pair `psq_l f0,0(r4); psq_st
   f0,0x78(r3)` chains: `arg1[15] = arg2[0]; ...` → **fn_80024668 (68B)**
   promoted.
2. **Derived base-pointer copies** — the store base is loaded once from a
   field (`lwz r9, 0x30(r3)` then `psq_st f0, 8(r9)`): the C must
   materialize the pointer ONCE as a local
   (`__ps_t *dst = *(__ps_t **)((char *)arg1 + 0x30); dst[1] = arg2[0];
   ...`) — inlining the pointer deref per store makes ngccc emit a fresh
   `lwz` per store (r9,0x34/0x38/...) and breaks the match. →
   **fn_800804E4 (72B)** and **fn_801B7A48 (72B)** promoted.

**The family is now exhausted.** The 8 remaining frameless copies all have
`mr r9, r3` (store via r9) — same regalloc difference as M5.0c; the framed
ones all contain calls/branches (m2c territory, not leaf-matchable), and
all arithmetic uses are unrolled loops. Total PS harvest: **10 promoted
(160B + 68B + 72B + 72B)**. To go further in PS you must either match the
loops (m2c + `__ps_t`, large) or find the `ps_muls0`/`ps_sum0` idiom
(research direction 1 below).

## What was tried (M5.0 investigation log)

- Probed 3.7 / 3.8.1 / 3.9.3 `cc1.exe` string tables for PS opcodes,
  `__ps_t`, `-mps-float`, `b_*ps3` expansion names, compiler version IDs.
- Tested `-mps-float`, `-mcpu=gekko/750/7400`, all `-m`/`-f` flag
  variants found in the binaries.
- Compiled `__ps_t` probes: add/sub/mul/div/madd/fma patterns; scalar×pair
  (ICEs 3.7 at expr.c:858; 3.9.3 emits `ps_mul` + `lfs`, not `ps_muls0`);
  struct-of-two-floats (no auto-vectorization); union bit-reinterpret
  (fails); direct pointer-cast reinterpret (works).
- Ran a whole-DOL PS scan (`/tmp/ps_scan2.py`) to size the family: 50,310
  PS instructions, ~895 functions.
- Verified 3.9.3 ≡ 3.7 on 110+ non-PS functions, then on the FULL rebuild
  (DOL byte-identical), then proved `-mps-float` breaks FPR frames
  (14 functions changed) and reverted the global flag.
- Reconstructed fn_8020D530 with `__ps_t` (`/tmp/fn_8020D530_ps.c`):
  544B vs 564B WANT, PS loads/stores/madds reproduced; the two idiom gaps
  above are the sole remaining differences.
- **M5.0h:** found the intrinsic route (`__builtin_ps_*` verified in
  3.9.3 via `strings`; interface documented in the in-tree `SN_PS.h`). The
  `__ps_t`-arithmetic path was the wrong lever; the idioms are expressible
  as direct intrinsic calls.
  Also confirmed the doc-13 weak lead (linker): tww is the only other local
  clone sharing mwldeppc GC/1.3.2, but no clone (bfbb/mkdd/tww = Metrowerks
  mwcc, snap = IDO) shares the ngccc compiler for codegen shapes.

## M5.0h — SNAPS intrinsics: the idiom gap is RESOLVABLE (no compiler hunt)

fn_8020D530's two wanted idiom blocks are directly expressible via SN
Systems' own SNAPS macros (see the M5.0h note in "How to emit PS from C"):

1. **Block 1** (0x8020D614..64C): three `ps_muls0` products (pair x
   scalar-lane-0) spilled to stack, reloaded, `ps_add`ed — express each
   product as `ps_muls0(x, y)` instead of `__ps_t` arithmetic (which
   fuses into `ps_madd`/`ps_mul` and keeps values in registers).
2. **Block 2** (0x8020D6C8..6E4): `ps_mr f13,f11; ps_mul f13,f13,f13;
   ps_merge00 f13,f13,f12; ps_madd f0,f0,f0,f13; ps_sum0 f0,f0,f0,f0`
   — a lane-merge + horizontal-sum dot product: `ps_merge00(...)` +
   `ps_sum0(...)` calls (which 3.9.3 currently lowers to scalar
   `fadds`/`fmuls` for every `__ps_t`/struct equivalent tried).

Execution steps, marker sizes, and sweep/promote commands are in
`docs/plan-snaps-doc06.md` (steps 1-6). This is the ONLY known PS gap
left; the ~4.5k instructions in these two idiom shapes across ~895
functions become matchable once the exemplar falls.

## M5.0i — GQR fast-cast family: next unexplored PS cluster (2026-08)

The 49,296-instruction PS scan covered `ps_*` ops but NOT psq GQR-index
use. The GameCube fast-cast family (`psq_l/st` with GQR type 0x4-0x7 for
u8/u16/s8/s16 conversion, `mtspr 912..919` GQR setup) is a distinct PS
family never swept in THUG2. Both local ProDG clones document it:

- **nfsmw SDK** ships the canonical header:
  `src/Speed/GameCube/bWare/GameCube/dolphinsdk/include/dolphin/os/OSFastCast.h`
  - `OS_GQR_F32=0x0, OS_GQR_U8=0x4, OS_GQR_U16=0x5, OS_GQR_S8=0x6,
    OS_GQR_S16=0x7`, `OS_FASTCAST_U8/U16/S8/S16` = GQR index 2-5,
    and psq asm recipes (with a `//HACK to match fast cast inlines`
    note from its own decomp).
- **Sims2DECOMP walls.md** records the same family: paired-single via GQR
  save/restore (`mtspr 913..919`) and `__OSLoadFPContext` with `psq_l`.

Closed 2026-09-10 (corrected census) — see the CLOSED note below; no
sweep remains.

### SCANNED 2026-08 - FOUND: 672 fast-cast ops, GQR selectors 6/7

Capstone PS-mode scan of the THUG2 DOL (requires `CS_MODE_PS`; psq ops
do not decode in plain PPC mode, and operand access needs
`md.detail = True` or CS_ERR_DETAIL):

- `mtspr` 912-919: 912:1, 913:1, 914:3, 915:3, 916:3, 917:3, 918:5,
  919:14.
- psq_l/st total 34,505; GQR index 0 (plain PS): 33,833; **index 6:
  192, index 7: 480 → 672 fast-cast ops**. THUG2 uses GQR 6/7 (s8/s16
  per the OS_GQR type encoding) - NOT the 2-5 convention in the nfsmw
  header's `OS_FASTCAST_*` macros; read the `mtspr` immediates when
  porting (the header documents the TYPE encoding, the selectors are
  game-specific).
- Sites: boot-time GQR clears at 0x80003304-0x80003320 (.init,
  matches Sims2's `__init_gqr` @ 0x80003300 pattern); game-code GQR
  2-5 setup at 0x801213F4 and 0x80142AD4; the big cluster (192+480
  sites) at 0x8024BExx-0x8024D2xx, all inside ANONYMOUS `fn_*`
  functions in the unnamed SDK stretch 0x8024B208-0x8024DD84
  (FPU-context save/restore region; OSInit is later at 0x802620D0).
   Those functions have zero names in symbols.txt → run plan Item A
   (SDK naming) first, then sweep the now-named exemplars with
   `--extra-cflags "-mps-float"`.

### CLOSED 2026-09-10 - corrected census, no C route (plan Item C executed)

   Raw-word re-scan of `.text` (no capstone): psq GQR `{0: 34341, 7: 480,
   6: 198}` = **678 fast-cast ops**; `mtspr` 912-919 at **53 sites**.
   Corrections: the game-code GQR-*setup* sites are 0x801244F4
   (fn_80124478 prologue) and 0x80145BD4 (fn_80145BB4 — already matched
   via a frozen `__asm__ mtspr` window), NOT 0x801213F4/0x80142AD4
   (plain code). All 678 fast-cast *use* sites attribute to 10 functions
   in 0x8024EF18-0x80253694 — doc-41's hand-written NeGo texture-upload
   module (unmatchable from C; cc1 hardcodes psq I=0). Flag probe: our
   3.9.3 cc1 accepts `-mfast-cast`/`-mps-nodf` but they are codegen-inert
   on float<->u8/u16 conversions. No header ported (deliberately — a
   verbatim copy was tried and deleted same day: upstream guards every
   asm body `#ifdef __MWERKS__`/empty-`#else`, so it is empty under
   ngccc and doesn't parse as C89 C; the encoding 0/4/5/6/7 is recorded
   here). No
   exemplar sweep remains — the matchable GQR code is matched or parked
   on other walls.

## M5.0e — `mr r9, r3` store-base regalloc UNPARKED (+8, family fully harvested)

**SOLVED 2026-08: the `mr r9, r3` copy is reproducible in 3.9.3 with an
empty asm clobber.** The game's compiler modeled the paired-single
`psq_l`/`psq_st` loads/stores as **clobbering r3** — so a destination
pointer living in r3 gets copied out into a scratch register (r9) once,
and all stores use r9. ProDG 3.9.3 does not model this clobber, so it
stores directly via r3.

### The fix (exact, no compiler hunt needed)

Insert an empty asm clobber **after the first copy statement**:

```c
void fn_80024FDC(__ps_t *arg1, __ps_t *arg2) {
    arg1[0] = arg2[0];
    __asm__("" ::: "r3");   /* forces mr r9, r3 between load and store */
    arg1[1] = arg2[1];
}
```

This emits the game's exact 6-instruction sequence
`psq_l; mr r9,r3; psq_st r9; psq_l; psq_st; blr`. Placement matters:
clobber after statement 0 (between the load and the store of pair 0).
Placing it before the first statement produces `mr`-first ordering
(different bytes); all 8 functions verified EXACT at clob_after=0.

### Compiler/flag archaeology that FAILED (recorded for completeness)

- **Every ProDG build** (3.5, 3.5b140, 3.7, 3.8.1, 3.9.3) emits the direct
  r3 form for the plain `__ps_t` copy — no `mr r9, r3` from any version.
- **Scheduling/optimization flags** (`-O1`, `-fno-schedule-insns`,
  `-fno-peephole2`, `-fno-regmove`, `-mcpu=*`) never produce the copy.
- **`-ffixed-r3` family**: silently ignored by the SN fork (no effect).
- **`volatile` / register-hint shapes**: spill to the stack instead of a
  clean `mr`.
- **No C++ compiler** (`ngcpp`) ships in any of the 5 ProDG dirs.

Root cause conclusion: the game compiler built PS ops with a stale r3
clobber side-effect in its instruction pattern (a pre-3.9.3 bug or a
legacy scheduling quirk), later fixed — hence the one-instruction diff.
The asm-clobber C reproduces the historical behavior exactly.

### Promoted (8):

`800063B8, 8000723C, 80007264, 80024FDC, 8002B8E8, 80081238, 802157D0,
802433BC` — 2-pair (24B ×5) and 4-pair (40B ×3) static copies, all with
the clobber at statement 0. DOL byte-identical. **The frameless static
copy family is now fully harvested: 18 total (M5.0c 7 + M5.0d 3 + M5.0e 8).**

## M5.0f — Guarded (branch) PS copies (+2, 2712/11431)

M5.0e closed the frameless static-copy family. The next family: the ~18
**unframed pure copies with a branch** (guarded copies) plus 11 framed
straight-line copies. Two guarded copies matched byte-exactly:

- **fn_800BA64C (44B)** — `if (o->flag != 1) { 2-pair copy via o->ptr; o->flag = 1; }`
- **fn_8022C778 (68B)** — `if (!src) return;` mixed struct copy: 2 ints +
  4 pairs + 1 int (the `or. r4,r4,r4` null guard reproduces exactly).

Both are byte-identical in ProDG 3.9.3 with `-mps-float`; the sweep
(project `test_wip_drafts.py --extra-cflags "-mps-float"`) confirmed EXACT
and both promoted through the `// extra_cflags` marker path.

**fn_800FDD50 (64B) SOLVED (2026-08-23, round) — the retry
suggested above WORKED.** Byte-exact with `-mps-float` via four stacked
tricks (draft: `src/wip/fn_800FDD50.c`, EXACT-verified, not yet promoted):
1. `register char *base __asm__("r9")` pins the reload home so WANT's
   second `lwz r9,8(r3)` survives;
2. a `volatile` read of that slot forces the reload to exist at all;
3. the §6l-76 asm-output wedge CREATES the derived pointer:
   `__asm__("" : "=r"(mid) : "r"(base + 0x10));` → want's lone
   `addi r11,r9,0x10`;
4. copies use sequential displacements off the two pointers
   (+0x10/+0x18 from `base`, +0x10/+0x18 from `mid`) — never re-derived
   expressions, which would coalesce back to one base register.
This closes the M5.0f partial-derived-register class: no known members
left parked on it.

**Framed straight-line copies (11: 800D51E0, 8020D190, 80036370,
80008E50, 800071D4, 800079D8, 8008757C, 8000433C, 80105C74, 801D16C0,
800FD81C) — NOT matchable via plain C.** The game's compiler built a 16B
temp on the stack via 4× `stfs` and copied it with `psq_l/psq_st` (its
struct-copy idiom under `-mps-float`). 3.9.3 emits direct `stfs`
(constant structs), `lwz/stw` GPR copies (locals), or rodata pair
constants (`psq_l` from rodata) — never the stack-temp + psq pattern.
No source shape (`Vec4` locals, `volatile` temps, `Pair2` structs)
reproduces it; these need the game's compiler build (see research
directions below).

## M5.0g — Framed PS copies WITH helper calls (+3, 2715/11431)

Probing the ~283 framed copies that contain calls found a fertile
sub-family: copies that end with (or start from) a single helper call.
All three matched byte-exactly:

- **fn_800FD4C4 / fn_800FD560 (52B each)** — 2-pair copy into dst, then
  `bl fn_800FD59C`. Uses the M5.0e `mr r9, r3` clobber trick for the
  store base. **Key find:** the trailing helper call must be declared
  OLD-STYLE and called with NO arguments (`void fn_800FD59C();` +
  `fn_800FD59C();`). A prototyped-with-args call makes 3.9.3 emit a
  `crclr cr1eq` before the call (the game compiler never does for direct
  calls) AND an extra `mr r3,r9` restore for arg passing.
- **fn_80024610 (60B)** — `bl fn_80024660` FIRST, copy 2 pairs from the
  returned pointer (r3) into dst (r30). No clobber needed — the
  parameterless call emits no `crclr`.

**fn_800D5AA8 (68B) PARKED (39.7%)** — 2-pair stack temp passed by
address + `return 1`. The want sets up the call as `mr r6,r11; li r7,0`
(&tmp in r6, 0 in r7) leaving r4/r5 unset — an odd ABI placement for a
`(o, &tmp, 0)` call that no prototype reproduces in 3.9.3 (which always
uses r4/r5). Likely a varargs/macro-style call in the game source.

**Tooling insight (crclr cr1eq):** 3.9.3 emits `crclr cr1eq` before any
call whose prototype has parameters; old-style/parameterless callees are
clean. For PS drafts with calls, write callee declarations old-style
`void f();` + no-arg calls — this is the reverse of the M4.94
`fix_fptr_proto` rule (which PROTOTYPES indirect calls to kill the
crclr there).

## M5.0j — bulk sweep of un-drafted PS functions (2026-08-20)

Swept all un-matched DOL functions that contain `ps_muls0`/`ps_sum0`/
`ps_merge00` arithmetic (opcode-4 scan, then targeted disasm) to classify
which ones 3.9.3 can match from C. ~135 candidates, bucketed by shape.

**Clean win:** the *pure dot-product → bool* shape matches byte-exact.
`fn_800A11D8` (88B) promoted: two pair loads, `ps_mul` +
`ps_merge00(const)` + `ps_madd` + `ps_sum0`, then compare the scalar
lane against a float constant. Source shape (this is the canonical idiom):

```c
SN_PS_type dot;
t = __builtin_ps_mul(C, A);
t = __builtin_ps_merge00(t, *(__ps_t *)&lbl_CONST0);
dot.ps = __builtin_ps_madd(D, B, t);
dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
return dot.flt.hi < *(f32 *)&lbl_CONST1;   // or <=, ==, etc.
```

**New systematic blocker — `ps_sub` dead spills (VERIFIED: compiler-version
artifact, NOT a flag).** Every subtraction-based variant (`d0 = A-B`,
`d1 = C-D`, then square/dot) carries DEAD `psq_st` stores: the game stores
each `ps_sub` result to a stack pair slot right after computing it, but
keeps the value in the register (never reloads it), so the store is pure
noise — 3.9.3 omits it and shrinks the frame (0x20→0x10 for `fn_8005A114`).

This is **not** the M5.0e regalloc coin-flip — it is a compiler-version
artifact, established by three independent facts (2026-08-20):

1. **It is ~universal.** 317 of 331 (96%) `ps_sub` functions in the DOL
   carry a dead `psq_st`; the 14 clean ones are where the store is
   legitimately reloaded. A source-level explanation would not be that
   uniform.
2. **No flag reproduces it.** Exhaustive sweep on `fn_8005A114`:
   `-O0/-O1/-O2/-O3/-Os`, `-fno-schedule-insns/-insns2`, `-fno-peephole`,
   `-fno-expensive-optimizations`, `-fno-delayed-branch`, `-fno-cse-*`,
   `-fno-function-cse`, `-fno-caller-saves`, `-fno-regmove`,
   `-fno-rerun-cse-after-loop`, plus 8 combinations. None emits the dead
   PS store. (`-fno-expensive-optimizations` and `-O1` do reach the 108B
   frame, but via a *worse integer* `lwz`/`stw` spill of the pair, not the
   game's `psq_st`.) The `#pragma peephole/schedule off` pragmas are
   Metrowerks-only — ngccc ignores them.
3. **No PS-capable compiler besides 3.9.3 exists here.** 3.8.1 (v1.54)
   ICEs on `__builtin_ps_sub` (optabs.c:4111, partial PS); 3.9.3 (v1.76)
   is the only full-PS build and is byte-identical across thug2 and
   Sims2DECOMP. The game was therefore built with an *intermediate*
   full-PS build (v1.54 < game < v1.76) whose PS backend emitted dead
   `psq_st` after `ps_sub`; v1.76 fixed it.

**Bottom line:** this family is unpromotable until that intermediate SN
ProDG build is recovered — not a matter of finding the right flag. Blocks
`8005A114`, `801F8170`, `801F81E0`, `8000714C`, `80005854`, `800A9200`,
`800A8D04` and ~310 more (the whole distance/normalize cluster).

**Projection/normalize near-miss.** The no-`ps_sub` scale forms
(`out = b * dot(a,b)` — `80005A90`; `out = b * (1/|a|)` with
`ps_rsqrte`/`ps_res` — `80005A18`) reconstruct structurally (correct
scalar→PS splat via `scalar.flt.hi = dot.flt.hi; ps_muls0(b, scalar.ps)`
reproduces the `stfs`+`psq_l`+`ps_mr` conversion) but still trail by the
`fmr` copy + larger frame + one trailing dead `psq_st` — the same coin-flip.
Best-effort drafts kept inert at `src/wip/fn_8005A114.c` (SNAPS
reconstruction, blocked) and `src/wip/fn_8020D530.c` (exemplar).

Takeaway: only the **pure dot-product → bool/float** family is harvestable
with 3.9.3 today; subtraction and scale/projection families remain parked
on regalloc until the game's exact scheduler is found.

### M5.0j-2r — the `ps_sub` DEAD-SPILL wall is NOT a compiler-version wall (2026-10-02, w75/0x80064294)

**The M5.0j "bottom line" above is WRONG about the cause.** 3.9.3 *can*
emit the dead `psq_st` that follows every `ps_sub` — the missing ingredient
is **addressability of the PS intermediates**, not the compiler build.

The game's shape is always: compute `d1 = A - B` as a pair, **store it to a
frame pair slot** (`psq_st f13, 16(r1)`), then *keep using the register*
(`ps_mul f13, f13, f13`) — the store is never reloaded. In C that is exactly
what you get when the intermediate is a **memory object whose value is read
back**, with the store→load pair collapsed by RTL forwarding. 3.9.3 keeps a
pure `__ps_t` pseudo in an FPR and emits no store at all (and shrinks the
frame), which is what every earlier attempt here saw.

The recipe — give the intermediates a home in a local struct, one member per
value, and keep the *result* reads going through the members:

```c
typedef struct { __ps_t d0; __ps_t d1; SN_PS_type dot; } Pair3;
...
Pair3 tmp;
__ps_t t3;
tmp.d1  = __builtin_ps_sub(D, B);          /* -> psq_st f13,16(r1)  (dead) */
t3      = __builtin_ps_mul(tmp.d1, tmp.d1);/* register only, no store */
tmp.d0  = __builtin_ps_sub(P, C);          /* -> psq_st f0, 8(r1)   (dead) */
t3      = __builtin_ps_merge00(t3, E);
tmp.dot.ps = __builtin_ps_madd(tmp.d0, tmp.d0, t3);
tmp.dot.ps = __builtin_ps_sum0(tmp.dot.ps, tmp.dot.ps, tmp.dot.ps);
d       = tmp.dot.flt.hi;                  /* -> psq_st f0,24(r1) + lfs */
```

Measured on `0x80064294` (340B, `src/wip/fn_80064294.c`): 9.4% → **65.9% at
the exact 340B size**, frame 0x30 with the pair temps at 0x8/0x10/0x18
exactly as the WANT. Independently confirmed on the M5.0j exemplar
`0x8005A114`: the same body shape produces BOTH dead `psq_st`s and the 0x20
frame that the parked note there calls unreachable (score still only 33%
because the regalloc/schedule tie-breaks below remain). **The ~317-function
`ps_sub` cluster is therefore NOT blocked on an intermediate SN build** — it
is blocked on the same M5.0o/M5.0r regalloc+scheduler coin-flip as everything
else, and is now attackable.

Do NOT write the mul/merge results back into the struct members
(`tmp.d1 = ps_mul(tmp.d1, tmp.d1)`): that adds a SECOND live `psq_st` to
d1 and one instruction per function. The mul/merge chain must stay in a
plain `__ps_t` local, with only the two `ps_sub` results and the final
`SN_PS_type dot` addressable.

Two companion semantics found on the same function (both needed to get the
surrounding bytes, and both generalise):
- **`addi r3,r3,0x68; blr` callees return the adjusted pointer and the caller
  uses the RETURN REGISTER.** `psq_l f0, 8(r3)` immediately after the `bl`
  reads from `r3`, i.e. from the call's result, not the argument. In C this
  needs **two** pointer variables (`p = f(); if (!p) return; o = g(p);`).
  Reusing one variable makes GCC park the pointer in a callee-saved register
  and emit an extra `mr r11, r3` (and a 3-register `stmw`).
- **int→float conversion order picks the `fmadds` operand order and the
  stack-temp reuse.** For `(s32)(lo + t * (hi_end - lo))` the source must
  convert `lo` FIRST: the Gekko branchless s32→double trick
  (`xoris 0x8000` + `0x43300000_80000000` − `0x4330000080000000` + `frsp`)
  then reuses ONE 0x20/0x24 word pair for both conversions. Reversing the
  operands costs the reuse (4 words instead of 2) and flips
  `fmadds f12,f12,f0,f13` to `fmadds f12,f12,f13,f0`.

Residual on `0x80064294` (29 words, all tie-breaks): a dead `mr r3, r30`
that 3.9.3 if-converts into the second early-exit test's block (shifts the
rest by one word; robust to `goto`-form returns, `!(x >= y)` predicates and
a different `p == 0` return value), and the PS regalloc colouring
(`local_alloc` priority: the accumulator wants f13, the second input f12, the
scalar reload f10; 3.9.3 gives f12/f10/f9 — unchanged by naming, reordering
or reusing the input variables).

**Family exhaustion scan (2026-08-20):** the harvestable family is now
provably EMPTY beyond `fn_800A11D8`. Exhaustive scans of all un-matched PS
functions confirm: the only small (≤250B) leaf bool-returning functions are
`8005A114`/`801F8170`/`801F81E0` (all `ps_sub`-blocked); the only
non-blocked dot-idiom functions are ≥400B and complex (the smallest,
`800C70A4`, is a guarded multi-dot setup routine with 12 branches); and the
two "dot→float" lookalikes (`800FFAB8` = conditional indirect call,
`800FD2D0` = table copy with `ps_mr`) are not dot products. No further
harvest is possible without breaking the `ps_sub`/`ps_muls0`/`ps_rsqrte`
walls.

**UPDATE 2026-08-23: one of the two lookalikes FELL.**
`800FFAB8` is now EXACT-verified in wip (`src/wip/fn_800FFAB8.c`, not yet
promoted): it IS a conditional vtable call, but its pair math is plain
`__builtin_ps_mul` (xo5=25 — see the ps_diff.py opcode-table fix below)
over `volatile __ps_t sp8[2]` stack temps, with a named alias pointer
(`pv`) used in ARRAY form for lane 0 (`sp8[0] = ...`) and POINTER form for
lane 1 + the call arg (`pv[1] = ...; f(..., pv)`) — that split is what
reproduces want's mixed array-displacement vs addi-address stores.
`800FD2D0` remains parked (regalloc cascade). The exhaustion-scan
conclusion stands for the *dot-product* family only.

## M5.0k — hand-match of `800C70A4` (guarded multi-dot, 400B): 30→10 diffs (2026-08-20)

Took on the 400B guarded multi-dot function (`800C70A4`, the best remaining
candidate from the M5.0j exhaustion scan) and cut it from the raw m2c draft
(464B, far off) to a **400B reconstruction with only 10/100 word diffs
(90.0% NEAR)** — all ten confined to the fill-loop guard/preheader regalloc.
Three transferable findings:

1. **Fill-store rotation trick (fills section now byte-exact).** WANT emits
   per-block `stfs` order `[0],[3],[1],[2]` with the *next* block's pointer
   `addi` interleaved between stores, using a fresh pointer register per
   block. ngccc right-rotates independent `stfs` and reuses one pointer
   register. Fix: write four pointer variables `q1..q4` (forces the four
   `addi`s, which then land in WANT's positions) and write the per-block
   stores in **rotated source order** so ngccc's rotation lands on WANT:
   - blocks 1–3: source order `qN[1]; qN[2]; qN[3]` → emitted `[3],[1],[2]`
   - block 4: source order `q4[2]; q4[1]; q4[3]` (the last block rotates
     differently; only `[1]/[2]` swap)
2. **Volatile base load reproduces WANT's in-loop reload.** WANT reloads
   `lwz r9, 0x2F0(r3)` (the pointer table entry) every iteration even
   though it is loop-invariant; ngccc hoists it (float store vs int load =
   no-alias). `*(char *volatile *)((char *)obj + 0x2F0)` forces the reload
   and matches WANT's position exactly.
3. **Loop semantics:** WANT's fill loop = `cnt = orig; if (cnt != 0) {
   cnt--; do { reload base; store(base + cnt*480 + 0xA4, fill); cnt--; }
   while (cnt >= 0); }` — the pre-decrement guard + store-at-cnt==0 makes
   it 3 iterations for orig=3, and `while (cnt >= 0)` prevents the CTR
   countdown conversion (`do {..} while (cnt != 0)` CTR-izes to
   `mtctr`/`bdnz`).

**Residual 10-diff wall (the loop guard/preheader):** WANT has
`cmpwi r11,0; addi r11,-1; beq` guard, a `fmr f0,f13` materializing
`fill` (from the already-loaded zero in f13), a separate `cmpwi`+`addi`
loop test, and a `bne` back-branch. ngccc emits `beq; addi` (guard order),
`lis r9,0; lfs f0,0(r9)` (literal-pool load instead of the fmr copy),
merged `addic.` (test+decrement), and `bge`. None of the flag variants
(`-fno-peephole`, `-fno-strength-reduce`, `-fno-schedule-insns/-insns2`)
flip these — same regalloc/scheduling coin-flip class as M5.0e. The
reconstruction is kept inert at `src/wip/fn_800C70A4.c` with the residual
noted in the header.

## M5.0l — fill-loop family sweep: `800C2284` + 3 siblings (2026-08-20)

Applied the M5.0k loop tricks (base+dt reloaded INSIDE the loop via volatile
base; `do {} while (cnt >= 0)` with pre-decrement guard to avoid the CTR
countdown conversion; empty-then-else form for `>= zero` compares so ngccc
emits `blt`+`fneg` instead of `cror`+`bns`) to the other four members of the
480B-object fill-loop family:

| addr | size | result |
|------|------|--------|
| `800C2284` | 156B | 55.3% NEAR (guard/loop-back coin flips; loop body byte-exact) |
| `800C4734` | 184B | 75.6% NEAR (same residuals) |
| `800C47EC` | 180B | DIFF (29/45 positional; extra `f1*o[0xFC]` multiply scheduling + fmr copy) |
| `800C48A0` | 172B | 58.5% NEAR (same residuals + one fmr copy) |

All four are now genuine float reconstructions (the pre-existing m2c drafts
were garbage: `*(s32*)` casts turned every float op into integer mullw/divw).
The residual diffs in every case are the same documented coin-flip classes:
guard order (`addi r11,-1` before `beqlr`), loop-back merged to
`addic.`+`bge` (WANT `cmpwi`+`addi`+`bne`), relocation-masked lis/lfs const
loads, and one register-allocation `fmr` copy. `-fno-schedule-insns` flips
the `fabs`/`fmuls` order in `800C47EC` but breaks the load ordering
elsewhere, so it is not usable per-function. The family is pinned on the
same regalloc wall as `800C70A4`; drafts kept inert for future reference.

## Research directions for an external AI

1. **DONE (M5.0h): find how the game emitted `ps_muls0`/`ps_merge00`/
   `ps_sum0` from C.** The answer is the paired-single intrinsic interface
   (`SN_PS.h`: `sn_ps` = `float __attribute__((mode(PS)))`, `PS_BUILD`,
   `ps_muls0`/`ps_merge00`/`ps_sum0` macros → `__builtin_ps_*`), verified
   present in 3.9.3's `cc1.exe`.
   The old "newer SN BUILD version" hypothesis is a dead end: same-compiler
   A/B testing (Sims2DECOMP, 609 fns x 4 ProDG versions) shows point
   versions are codegen-identical.
2. **Infer idioms from the other ~895 PS functions.** Disassemble a sample
   (e.g. matrix/quaternion math — `ps_muls0`+`ps_merge00`+`ps_sum0` is the
   classic dot-product/transform pattern) and note which PS forms appear
   together; that reveals the source operations. SDK hand-asm shape
   references for the math: `bfbb/src/dolphin/src/mtx/{psmtx,vec,quat}.c`
   (same files again in nfsmw `bWare/GameCube/dolphinsdk/src/mtx/`) and
   `tww/src/JSystem/J3DGraphBase/J3DTransform.cpp` — these show
   `ps_muls0` scale / `ps_madd`+`ps_sum0` mag/dot shapes in context.
3. ~~SN SDK math headers~~ — **FOUND**: the paired-single interface is
   documented in-tree (`include/dolphin/SN_PS.h`).
   Local GC clones are NOT useful cross-references for PS codegen: bfbb/
   mkdd/tww/tp are Metrowerks mwcc (PS in hand-written `asm {}` blocks
   only), snap is N64 IDO. The same-compiler references are nfsmw and
   Sims2DECOMP (both ProDG GCC 2.95.3).
4. **Fallback (last resort):** matching a small PS math library as a real
   assembly source file (not an asm-in-C stub — see AGENTS.md §4g). The
   ~895 functions likely cluster into a few math libraries, so a handful
   of `.s` files with proper attribution could cover many at once.
5. **GQR fast-cast cluster (M5.0i - SCANNED 2026-08, FOUND):**
   psq_l/st with a non-zero GQR index + `mtspr 912..919` setup.
   Result: 672 fast-cast ops (GQR 6/7: 192/480), cluster at
   0x8024BExx-0x8024D2xx inside anonymous SDK functions, boot clears
   0x80003304-0x80003320, game GQR2-5 setup at 0x801213F4/0x80142AD4.
   Header + recipes in nfsmw `.../dolphin/os/OSFastCast.h` (selectors
   adapt: THUG2 uses 6/7); same family documented in Sims2DECOMP
   walls.md. Next step: plan Item A naming, then port + sweep (plan
   Item C).

## M8.xx — session: asm-pin trick PROVEN, fusion asymmetry park (+3)

Three findings from the 800CCB94-800D5624 batch (AGENTS.md §6j):

1. **`__asm__("" : "+r"(tp));` pins a base pointer's register home** for
   paired-single copies through stack temps with MIXED r1/r11 addressing.
   Source shape (PROMOTED byte-exact, fn_800D51E0):

   ```c
   volatile __ps_t t[2];
   /* ... derive tp from sp/arg ... */
   __asm__("" : "+r"(tp));      /* forces the game's addi r11,r1,8 */
   t[0] = *(__ps_t *)src; dst0[0] = t[0]; ...
   ```

   Generalizes M5.0e's empty-clobber r3 trick: an empty inline-asm with a
   `"+r"` constraint is a zero-code register-home selector for ANY variable.

2. **psq_l fusion asymmetry = NEW PARK PRECEDENT.** The game FUSES
   pair-load + SINGLE-lane store into `psq_l` + one `stfs`; ngccc 3.9.3
   always narrows pair loads to plain `lfs` when only one lane is used.
   fn_800CD7CC / fn_800CD83C parked at 85.7% on this alone (their int paths
   are byte-exact). Don't burn time re-trying single-lane copies of pair
   loads without SNAPS intrinsics.

3. **Direct `__ps_t` pair copies via a member-derived base** (`p =
   arg0->field_C; p[0] = src[0];`) promoted byte-exact (fn_800D5364) —
   confirms M5.0d's derived-base rule holds for PS member bases too.

## Where to look

- Exemplar: `fn_8020D530` (564B, PS throughout) — draft at
  `src/wip/fn_8020D530.c`.
- Execution plan for the remaining idiom gap: `docs/plan-snaps-doc06.md`.
- Cross-clone reuse (SDK naming, GQR scan, flag experiments): executed
  2026-09-10; outcomes in AGENTS.md §4b/§4r, doc-15 (Item D verdict),
  and the M5.0i CLOSED note above.
- Paired-single header (the source API): `include/dolphin/SN_PS.h`.
- GQR fast-cast header: `../nfsmw/src/Speed/GameCube/bWare/GameCube/
  dolphinsdk/include/dolphin/os/OSFastCast.h`.
- `config/G2TE52/symbols.txt`: functions with PS body ranges.
- Compiler: `build/compilers/ProDG/3.9.3/cc1.exe` (v1.76, full PS);
  3.7 = v1.46 (no PS), 3.8.1 = v1.54 (partial).
- Build wiring: `configure.py` `cflags_game` + `Object(..., extra_cflags=...)`.
- History: AGENTS.md §4c (issue-01 frame quirk — same `-mps-float`
   side effect), `docs/gamecube-decomp-plan.md` §5.13.

## M5.0m — session: asm-output wedge, "+f" barriers, decode rules (+6 PS fns, 2026-08-22)

Six paired-single functions promoted byte-exact in one round
(`800B7D00`, `800B7D4C`, `800BD050`, `800BDE4C`, `800BE3C8`, `800BDF64`),
plus the two hand-written stubs that seeded them. New durable techniques:

1. **asm-output pointer wedge** (AGENTS.md §6l-76): an empty inline-asm
   whose OUTPUT binds a freshly computed pointer
   (`__asm__("" : "=r"(mid) : "r"(arg0 + 0x20));`) forces ngccc to emit the
   game's derived-base `addi` into the exact register and route only SOME
   accesses through it. This is the fix for M5.0f's parked partial-derived-
   register class (fn_800FDD50 — SOLVED 2026-08-23, see M5.0f above). The
   older M8.xx trick pins
   an existing var ("+r"); this one CREATES the pointer.
2. **`register f32 v __asm__("frN")` + `"+f"` barriers pin FP webs exactly**
   (fr prefix, NOT "f" — same finding as AGENTS.md §6k-67, found
   independently here). The new half: an input-only `"+f"` asm barrier
   between uses blocks float copy-propagation so BOTH of WANT's
   `fmr f0,f13` copies survive (`fn_800BD050`, 336B EXACT).
3. **Input-only integer asm barrier blocks constant-folding**: keeps a
   `subfic` guard alive where GCC would fold `0x3B - x == C` to `cmpwi`
   (`fn_800BD050`; generalizes §6l-77).
4. **Decode rules (see tools/ps_disasm.py / tools/ps_diff.py):**
   - opcode 59 words = SCALAR fmadds/fmuls/fdivs/fres/fsqrts — not PS.
     Decode before parking something as "paired-single".
   - primary opcode 4 words = Gekko PS arithmetic; emittable via SNAPS
     `__builtin_ps_*` per M5.0h, EXCEPT XO5=6/7 encodings: an exhaustive
   probe (full `__builtin_ps_*` dump of cc1.exe v1.76, compile-test of
   every builtin and header macro) found **no construct in any
      ProDG build that emits XO5=6/7**. Functions containing them
      (`800BB9BC`, `800BC968`, ~146 game-wide) are hard-walled until those
      ops are identified — do not burn time on source shapes or flags.
       Additions (2026-08-22): `fn_8014E440` contains **XO5=8**
      words — absent from all Gekko PS tables and the same SNAPS probe
      set — so the wall extends to that encoding too. Park immediately on
      undecodable primary-opcode-4 words; verify with tools/ps_disasm.py.
      **CORRECTION (M5.0q, 2026-08-24): the xo5=8 sightings above are
      decode artifacts — see the M5.0q section at the end of this file.**
      **CORRECTION (M5.0t, 2026-08-26): the xo5=6/7 sightings above are
      ALSO decode artifacts — see the M5.0t section at the end of this
      file. ZERO true A-form xo5=6/7 words exist DOL-wide (census).**
   - capstone stalls at the first PS word, so `tools/disasm.py` prints
     NOTHING for pure-PS functions — use `tools/ps_disasm.py`.
5. **PS pair copies with mixed direct/derived addressing**: when WANT does
   some pair stores through `arg0` directly and some through a derived
   `r9 = arg0 + K`, write all pairs through named locals but bind ONE
   mid-pointer via the wedge (technique 1) and split the copy list at the
   game's switch points (`fn_800B7D00`: loads 1-4 + 7-8 via arg reg,
   5-6 via mid; `fn_800B7D4C` mirrored for stores).
6. **Escaped stack temps force reload-before-store**: passing `&spA` to a
   callee makes every subsequent `spA[i] = ...` re-read the slot address,
   which is exactly the game's idiom in guard+copy bodies
   (`fn_800BDF64`).

## M5.0n — session: stale-register ps_merge00 blocker (+0, 2 parks,
2026-08-22)

Two Script* wrappers in the 0x80110Bxx-0x80111Bxx zone park on a new
sub-pattern of mixed scalar/PS code that no source shape reproduced:

- `fn_80110B84` (ScriptKillAllTextureSplats, 716B, best 14.6%): the tail
  copy block is paired-single and its THIRD `ps_merge00` consumes the
  STALE f0 left behind by the preceding SCALAR clamp code. Portable C
  has no way to name "whatever register the scalar code happened to
  leave in f0" - GCC either schedules a fresh definition into f0 or
  merges differently.
- `fn_80111BE0` (fn_80111BE0, 812B, best 6.9%): same disease -
  `psq_l/ps_merge/psq_st` runs around 0x80111DE4-DF8 interleaved with
  stale-register merges inside the pixel loop, before the ~100-word
  scalar body could even be attempted.

SNAPS intrinsics do NOT help here: the blocker is not emitting the merge
opcode (M5.0h solved that) but reproducing an input operand whose value
is an artifact of unrelated scalar-code scheduling. Both drafts were fully
regenerated against disasm first (correct protos, struct discipline, clamp
forms per AGENTS.md §6m) before parking; fn_80110B84 additionally has a
12-store init block resisting every permutation tried (rule 24 family).

Future angle: if a source form is ever found that reproduces one
stale-input merge (e.g. exact statement order forcing f0 reuse across the
scalar/PS boundary), re-test both functions together - their blockers are
the same shape.

## M5.0n — update (2026-08-23)

Parallel sweep of the 0x800FC56C–0x8010048C batch (50 fns, 26 EXACT in
wip, nothing promoted). PS-relevant outcomes:

**Solved this round (details above):**
- `fn_800FDD50` — M5.0f partial-derived-register class closed.
- `fn_800FFAB8` — exhaustion-scan "lookalike" matched via
  `__builtin_ps_mul` + volatile pair stack temps + array/pointer alias split.

**Tooling fix: `tools/ps_diff.py` opcode tables were shifted.** The op4
XO5 tail was one low (`ps_sel`@22 … `ps_nmadd`@30) and op59 had a bogus
`fsqrts`@22 with 30/31 name-swapped. Correct Gekko map: sel=23, res=24,
mul=25, rsqrte=26, msub=28, madd=29, nmsub=30, nmadd=31 (op59 mirrors it
with fsels/fres/fmuls/frsqrtes). Cross-checked against cc1.exe
`__builtin_ps_*` encodings — `__builtin_ps_mul` emits xo5=25. Earlier doc
sections that name-decoded raw opcode-4 words pre-fix may carry shifted
labels; the WORDS were always right, only the names moved.

**Newly-confirmed parked members by wall class (best drafts in
src/wip/, all verified compiling):**
- Framed-copy/interleave idiom: `fn_800FC884` (psq pairs interleaved with
  int field loads — scheduler hoists the loads into the pair window),
  `fn_800FCAA4` (member-wise stfs stack-temp construction + interleaved
  list load).
- Spill/regalloc class: `fn_800FD074`, `fn_800FD198`, `fn_800FD698`,
  `fn_800FD81C`, `fn_800FD9A8` (analysis-only sketch), `fn_800FD2D0`.
- Store-weave scheduling: `fn_800FDDA0` (int stores must interleave
  exactly one-per-pair; ~35 orderings resisted), `fn_800FDC50`
  (lfs/stfs order + FPR temp numbering; update 2026-10-09: const-float tried,
  63.5→69.2%, wall class unchanged, still parked).

## M5.0o — update (2026-08-23)

- fn_801611C4 (ScriptPlaceObject) **EXACT** under `-mps-float`: unconditional
  global load pinned into dead-arg r3 via `"+r"` barrier (§6s-3), plain
  `__ps_t` pair copies, `register count __asm__("r11")` pin (§6o-1),
  two-statement dst split to keep ONE address web, `s32 sp8[4]` for the
  frame slot. No new PS opcodes needed.
- fn_8015E868 (ScriptSetSkaterVelocity) parked at **83.6%** (-mps-float):
  every `ps_mr` (XO10=72) pair move IS emittable via `__ps_t` assignment —
  opcode emission is fully solved for this shape. Remaining 18-word diff is
  pure FPR-coloring clusters (which fN holds which lane temp), same wall as
  M5.0n. Treat "ps_mr wall" claims as obsolete; the wall is register coloring.

## M5.0p — update (2026-08-24, skater-state zone)

- fn_801792D4 (896B) parked at 4%: FIVE opcode-4 words with **xo5=8**
  (ps_abs-class) — reconfirms the M5.0h probe result that xo5=6/7/8 have no
  emittable construct (extends the fn_8014E440 data point to a
  second function). Plus psq stack-pair traffic and an int→double rodata2
  union dance; do NOT redraft without a new builtin discovery.
  **SUPERSEDED by M5.0q — the xo5=8 words are X-form ps_mr; RETRY this fn.**
- fn_801786EC (412B) parked at ~7.8% (-mps-float): PS distance block FULLY
  decoded (ps_sub/mul/merge00/madd/sum0/rsqrte/res vs rodata zero-pair
  lbl_802A8F88, threshold 1800.0f — all builtins verified in cc1). Wall is
  NOT opcode emission: double-spill pattern suggests the original INLINED a
  helper, plus mixed-polarity guard layout. Retry angle: find/construct the
  inlined-source shape.
- fn_8017B268 EXACT under -mps-float via plain `__ps_t` pair copies +
  chained idiom + role pins — another confirmation that pair-copy shapes
  are fully emittable.

## M5.0q — the "xo5=8 wall" was a DECODE ARTIFACT (2026-08-24)

**Status: the xo5=8 park reason is INVALID. Retry fn_801792D4, fn_8014E440,
fn_801B19DC (and any function parked on "xo5=8").**

Root cause: X-form PS words were being read through an A-form lens. An
X-form word `op4 VD VB 0 XO10` with XO10=72 (`ps_mr`) has low five bits = 8
— exactly what earlier rounds recorded as "xo5=8". There is no unknown A-form
encoding; the words are plain pair moves.

Verified today by probe + want decode:
- `ps_mr` = op4, XO10=72, e.g. want `13E00890` / `11406090` in fn_801B19DC.
- Emitted by ngccc when a `__ps_t` VALUE must move between FPR registers —
  canonical shape: a `__ps_t` parameter copied to a callee-saved pair to
  survive a call (`void t(__ps_t x){ gv = x; callee(); gv = x + gv; }`
  emits `13E00890` = ps_mr f31,f1...). Plain `__ps_t` assignment between
  register-resident pairs works too (M5.0o already proved this shape).
- Bonus builtins verified in cc1.exe v1.76 today:
  `__builtin_ps_abs` → XO10=264, `__builtin_ps_nabs` → XO10=136,
  `__builtin_ps_neg` → XO10=40.

Decode discipline going forward: before parking ANY function on an
"undecodable opcode-4 word", re-decode it as BOTH forms with
tools/ps_diff.py's tables: A-form (VD VA VB xo5@26-30 rc) AND X-form
(VD VB 0 XO10@21-30). XO10 values seen in real code so far: 72=ps_mr,
528/592=merge00/01, plus the §6r-91 A-form map. Only park if the word fits
NEITHER form's tables.

The genuinely-open question shrinks to: do any TRUE A-form xo5=6/7 words
exist in the DOL? Re-scan candidates with the two-form decoder before
answering; fn_800BB9BC/fn_800BC968 and the ~146-function list predate this
correction and need a re-decode pass too.

## M5.0p — update (2026-08-23, PS zone 0x801AD-B0)

EXACT under `-mps-float`: fn_801AF37C (duplicated sentinel-fixup blocks +
crossjump; `outp[1]` array form for mixed psq_st addressing) and
fn_801AFE44 (four `__ps_t[2]` assignments off a chained return). No new
opcode gaps.

Parks in the PS zone this round — note the wall has moved UP a level:
opcode emission is solved; the residuals are scheduler/allocator:
- fn_801AD5DC (~2%): XO5=8 words remain the hard wall (M5.0h reconfirmed).
- fn_801AE4CC / fn_801AE5A4 (~30/23%): all pair-copy shapes match; ngccc
  batches the four SCALAR row-product fmuls (opcode 59) differently than
  want under every shape tried (volatile, temps+commit, clobber barriers,
  interleaved copies, statement reversal, pointer wedges).
- fn_801AEBA4 (31%): quaternion->matrix leaf; FP allocator tie-breaks
  (div target f3-vs-f0, w/x/y reload order).
- fn_801AE688 (~5%): structure fully reconstructed; needs saved-reg
  web-shaping session — want uses exactly 5 webs with r31 SHARED between
  call-dest and store base, ngccc allocates 6 + displaced const-stores.

Retry hint: before more shape grinding on these, check whether a
register-pin set can force the FPR roles directly (`register f32 v
__asm__("frN")`, recipe 67) — untried on AE4CC/AE5A4.

## M5.0r — update (2026-08-24, PS-saturated script zone
0x801CB7B8–0x801D0BCC: 23 EXACT incl. 3 -mps-float / 21 parked)

**Emission is fully solved; every residual is scheduler/allocator.** This
round confirmed `__builtin_ps_muls0` emits ps_muls0 natively and went EXACT
(fn_801CCF08 — the "unknown xo=396" was plain ps_muls0; capstone decodes it,
manual XO slicing misleads because the XO field includes C-register bits).
Decode discipline per M5.0q reconfirmed; two NEW tooling traps: capstone
prints PSQ displacements in DECIMAL (`928(r1)` = 0x3A0), and on big bodies
it mislabels primary-opcode-4 words as VMX names (vmhaddshs/vsel/maddhd) —
they are paired-single.

### New wall #1 — unstaged `[ps_neg][fcmpu]` guard (NOT expressible from C)
want applies ps_neg to a pair (or SNAPS member) and fcmpu's the result with
no intervening store. Every C route fails:
- `SN_PS_type` member reads spill to stack (+8 frame vs want);
- `*(f32 *)&pair` / `*(double *)&pair` ICE cc1 at expmed.c:1115;
- relational operators on `__bs_t`/`__ps_t` ICE at optabs.c:3515;
- cast-through-union rejected by cc1.
Suspect origin: C++ operator inline (project language policy keeps us in C).
Members this round: fn_801CE098 (×1), fn_801CF0E4 (×2), fn_801CDE9C.
Contrast: when want STACK-STAGES the negated value first, the compare IS
expressible (fn_801CC75C rebuilt to 16% before hitting coloring).

### New wall #2 — inline PS contraction-tree scheduling
Vector-math chains mixing ps_mul/madd/sum0/sum1 (opcode-4 + opcode-59 mix)
have no C shape whose contraction + scheduling matches want
(fn_801CF7F8 ~10% rebuilt, twin fn_801CF9B0). All ops emittable; the
fmadd/fmuls association tree under the pair loads refuses every grouping,
temp+commit staging, and clobber-barrier layout tried. Same class as the
M5.0p scalar row-product note, one level up.

### FPR-coloring residual (M5.0o) — more members
fn_801CE3E4 (SNAPS body FULLY reconstructed: __builtin_ps_mul/merge00/madd/
sum0/muls0 + asm ps_mr — all emittable; residual is pure FPR-coloring),
fn_801CEE28 (twin-arm mr/muls0/sub/add, needs pin/grind pass),
fn_801CBC78 (~120 PS insns across 8 auto-vectorized clamp/distance blocks +
3 long-range CR webs doc-28; retry hint: crack one distance-block chain in
isolation on a smaller sibling first), fn_801CD414 (~40%), fn_801CBBD0
(psq_l quantized pairs → ps_sub/mul/madd/sum0/rsqrte/res → value-form
compare; full decode in header).

### Doc-06 gap status after this round
- ps_muls0: CLOSED as an emission gap (builtin emits it; EXACT achieved).
- ps_sum0/rsqrte/res: emit fine; parks are coloring/scheduling only.
- Remaining open walls: unstaged neg-guard (#1 above), contraction-tree
  scheduling (#2), FPR-coloring under heavy PS traffic (M5.0o).

## note (2026-08-24): two NEW unemittable-word classes

- **xo10=332 (VC=10)** opcode-4 words (e.g. fn_801ED5F0 m3/m4): NOT merges
  (528-624), NOT mr (72), NOT any A-form op, ABSENT from cc1.exe 3.9.3's
  entire `__builtin_ps_*` string table. DOL-wide: ~300 hits, zero inside
  promoted functions - treat as a hard wall until a construct is found.
- **xo10=6** word 0x1169000c (fn_801EDD7C @0x801EE49C) - doc-06 XO5=6 class
  reconfirmed at a second site.

Also confirmed here: capstone mislabels ps_add(21)/ps_sub(20) as
vsel/vmsumshm and misprints psq_l displacements - hand-decode raw words
(AGENTS.md 7b-140/7c-155).

## M5.0r — update (2026-08-24)

- Authoritative opcode-4 map + capstone-mislabel warning moved to AGENTS.md
  §6ai-152/153 — check there FIRST before declaring any wall in PS zones.
- New emittable forms proven: xo5=8 neg/abs/nabs (`__builtin_ps_neg/abs/
  nabs`), merge01 (C=17), ps_sub pairs via __ps_t arithmetic
  (fn_801D6500 EXACT).
- frN pins work across PS builtins for CALL RESULTS (`register f32 x
  __asm__("fr1")`) but NOT for builtin outputs (§7a-137) — split scopes.
- cc1 ICE trap: comparing punned __ps_t lanes kills cc1 (-mps-float);
  use union members.
- Zone status: 9 EXACT / 34 parked; the parked majority are m2c
  statics-DCE husks needing hand-rebuilds (threshold ~600B), plus a
  recurring "lane-read pair [lfs f0][fmr]" coloring wall (D17E4/D19E0/
  D2D94 siblings) — treat that trio as one root cause to crack together.

## M5.0s — update (2026-08-25, zone 0x801F67xx–0x801FA1xx)

Two more PS functions went EXACT-in-wip with the new technique stack
(AGENTS.md §6am-189..194): `fn_801F8170`/`fn_801F81E0` (twins) — mode(PS)
`register psf x __asm__("frN")` pins on PAIR webs + asm-anchor sandwich
(lis @ha early / lfs @l late wedges) + input-only `"m"` keep-alives for
dead pair stores. `fn_801F98B4`/`fn_801F99D8`/`fn_801F9DC8`/`fn_801F9E38`
also matched PS-heavy bodies (psq_lu walker idiom §6am-195; volatile-memory
lane extract §6am-190).

Wall reconfirmations this round:
- **XO5=6/7 hard wall**: two NEW members at high ceilings — fn_801F77B8
  (~98.6% ceiling, 3 words) and fn_801F7B04 (~98.4% ceiling, 5 words +
  doc-28 CR-liveness). Both also m2c statics-DCE husks; rebuild only if
  the wall ever opens.
- **Contraction-tree scheduling wall (#2 of M5.0r)** recurred at
  fn_801F7608 (47.3%): all ops emittable (xo5=20/21 = __builtin_ps_sub/
  add), prologue/frame match, but ngccc batches the row-product chain
  differently under every shape tried; K-const homed into pinned fr30.
- **FPR-homing-vs-spill wall** at fn_801F8250 (~2%): want spills dh/dl/est
  to r1+8/10/18/20 around a call while ngccc homes them in callee-saved
  FPRs; two more optabs.c:3515 ICE signatures catalogued (§6am).
- fn_801F8430 stays an unrebuilt statics-DCE husk (structure documented in
  header).

## M5.0s — update (2026-08-24)

NEW dead-insn sub-case (fn_80215C30, parked 5.7%): want contains two
PROVABLY DEAD instructions inside the PS block — a `psq_l` zero-pair load
and a `ps_sub` toward (0,0) — which plain C can never emit (GCC DCEs
effect-free code; only raw asm could). Combined with the M5.0o
FPR-coloring cluster this makes the SNAPS-husk rebuild route
structurally incomplete even after a perfect decode. Full staged retry
plan lives in src/wip/fn_80215C30.c header.

## M5.0t — the "XO5=6/7 hard wall" was a DECODE ARTIFACT too (2026-08-26)

**Status: the xo5=6/7 park reason is INVALID — the last open question of
M5.0q is answered: NO true A-form xo5=6/7 words exist in the DOL. Retry
every function parked on this class: fn_800BB9BC, fn_800BC968,
fn_801B1278, fn_801F77B8 (~98.6% ceiling), fn_801F7B04 (~98.4% ceiling),
fn_801E3D70 (xo5=8/12 citations; 8=ps_mr per M5.0q and 12=A-form muls0 is
emittable per the §75-171 map) — plus any of the ~146-function pool.**

Root cause (same family as M5.0q's xo5=8): Gekko PS X-form words put a
**9-bit XO at bits 22–30 plus a `w` pair-half bit at bit 21**, where the
A-form lens reads only bits 26–30 as `xo5`. The indexed quantized memory
ops have XO values that COINCIDENTALLY read as xo5=6/7:

| instruction | XO(bits 22-30) | reads-as-xo5 | emits from |
|---|---|---|---|
| `psq_lx fD, rA+rB, w` | 6  | 6 | `t.p = *(__ps_t *)(a + b)` with BOTH lanes consumed |
| `psq_stx fS, rA+rB, w` | 7  | 7 | `*(__ps_t *)((char *)a + b) = v;` |
| `psq_lux fD, rA+rB, w` | 38 | 6 | walker post-inc (psq_lu idiom §6am-195; verified in-batch fn_80257704 cluster) |
| `psq_stux fS, rA+rB, w` | 39 | 7 | walker post-inc store form |

Verified by probe (ngccc 3.9.3 `-mps-float`, plain C, no builtins):
indexed store emits `1023200E` = psq_stx verbatim; FOUR independent load
shapes all emit `100xxxxx` = psq_lx (element index `((__ps_t*)a)[b]`,
walker `p += b`, masked byte-index `(b & ~7)`, volatile load). CAVEAT:
pair loads narrow to scalar `lfs` when only ONE lane of the result is
consumed after a union pun — keep both lanes live (e.g. sum them) or read
via `.flt.lo/.flt.hi` members.

Census (whole .text): exactly **146 opcode-4 words are psq_lx/stx/lux/
stux**; **0 words** have an xo5-reading of 6/7 that is not one of these.
The doc's old "~146 game-wide functions" hard-wall pool was this same
misdecode. capstone additionally prints these words as VMX garbage
(`vmrghh v10,v3,v6` for a psq_lux cluster at fn_80257704) — decode raw
words before believing ANY opcode-4 label.

Decode discipline update (supersedes M5.0q's two-form rule): decode every
opcode-4 word as A-form (VD VA VB xo5@26-30 rc) AND X-form (rD rA rB w@21
XO9@22-30 rc). Only park if it fits NEITHER table — and today no such
word is known to exist.

Remaining genuine walls in this doc are unchanged: doc-29 VMX (V-form
words), the dead-insn sub-case (M5.0s), contraction-tree scheduling
(M5.0o/M5.0r #2), FPR-homing-vs-spill (M5.0o), doc-14 pool routing.

### M5.0t post-batch update (2026-08-26, 7-function retry round)

All seven former xo5=6/7-parked functions were rebuilt from disasm under
`-mps-float`; every former wall word emitted from plain C in-body —
**zero opcode-emission walls remain anywhere in this doc's scope**.
Results: fn_801F7B04 29.8% (doc-28 CR machinery REPRODUCED from plain C
en route), fn_801B1278 20.6% (prologue/call chains/gates/fill loop
byte-exact), fn_8025784C 7.9% (size-exact), fn_802575CC/7704 ~5%,
fn_801F77B8 2.3%, fn_800BB9BC 2.4%, fn_800BC968 1.6%. Residuals are now
exclusively FPR/GPR coloring + scheduler tie-breaks (M5.0o/M5.0r class)
— per-function register maps and retry recipes live in each draft header.

**VERIFIED builtin argument mapping (param-based probe, cc1 v1.76):**
builtin args mirror the ASM-SYNTAX operand listing `ps_xxx d,A,C,B`
(skipping d) — NOT the mathematical expression order:
- `__builtin_ps_mul(a,b)` / `muls0(a,b)`: a→frA, b→frC ⇒ a*b (.lo)
- `__builtin_ps_madd(a,b,c)` / `madds0(a,b,c)`: a→frA, b→frC, c→frB
  ⇒ **a*b(.lo) + c — multipliers are args 1-2, addend arg 3**
- `__builtin_ps_sum0(a,b,c)`: same fields ⇒ {a.lo + b.lo, c.hi}
When porting a want word `ps_madd fD,fA,fC,fB`, call
`__builtin_ps_madd(A_val, C_val, B_val)` (swap slots 2/3 vs field order).
This SETTLES §63-168's confusing "multiplier pair is third" note: that
describes the field-order→arg-order swap, not the math.

New tooling traps catalogued this round:
- `__builtin_psq_lx/stx/lux` EXIST in cc1 but compile rc=0 to a SILENTLY
  EMPTY ~284B stub object (cc1 dies inside wibo, no stderr). Check object
  SIZE, not exit code — same signature as a silent ICE; bisect by
  truncation with size checks.
- NgcAs REJECTS the `psq_lux` mnemonic ("Missing / misplaced comma") even
  in cc1's own template form — use `.long 0x…` if a raw word is ever
  needed. psq_lux itself is unreachable from plain C (walker forms give
  displacement psq_lu); only psq_lu/lx/stx emit naturally.
- capstone yields ZERO disasm on ProDG `.o` sections — decode raw words.
- tools/ps_diff.py prints psq D-form displacements signed with phantom
  `I1` fields (`0xC00(r31)` → "-1024 I1") — trust raw words only.
- Scalar→PS broadcast `K = (__ps_t)*kp++;` emits bare `lfsu` consumed
  directly as a PS operand — works on 3.9.3 ONLY (3.5/3.7/3.8.1 ICE at
  expr.c:858): a compiler-version discriminator for game codegen.
- Builtin results are NOT volatile — dead retail PS code DCEs from any C
  form (frozen asm is the only route for provably-dead blocks).
- Duplicate-mul preservation: identical `t*k` feeding two sum builtins
  CSEs to one mul; mixing forms (`t*k` + `__builtin_ps_mul(t,k)`) keeps
  two muls like want.
- Plain `__ps_t` locals do NOT inflate frames in straight-line code
  (refines §63-173's +8-per-local rule: it applies to live-across-call /
  address-taken cases).
- PSU unions inside frame structs drag 16-byte alignment (padding shift);
  frame members must be raw `f32[2]` arrays with punned access. Union
  `.w[]` lane WRITES also ICE cc1 (extends §7c-163).
- `(f32)pairvar` casts extract lane0 IN-REGISTER (want's fcmpu-on-pair
  idiom); union puns split to lwz or ICE.

## Addendum 2026-09-19: the 16-byte pair-copy trio (two ngccc residuals)

`fn_800699A8` / `fn_80069C58` / `fn_8007D330` (32/32/36B, `main/auto_*` gaps)
are all `dst = (__ps_t *)(arg0 + OFF + arg1*0x10); dst[0] = arg2[0];
dst[1] = arg2[1];` (plus `return 1;` for D330) with OFF = 0xA8 / 0xD8 / 0xA0.
Retail first shifts the index left by four, performs a paired-single load of the first pair from offset zero of the source pointer, adds the base register in, and materialises the destination by adding the 0xA8 (respectively 0xD8 and 0xA0) byte offset. It then stores the first pair at destination offset zero, loads the second pair from source offset eight, and stores that pair at destination offset eight, with the paired loads and stores using the default word-zero/immediate-zero quantisation mode.

Parked at 7/8, 7/8 and 2/9 words. Two residuals, both ngccc policy:

1. **psq_st displacement fold.** ngccc folds the +OFF into the store
   displacement (`psq_st f0,168(r4)` / `176(r4)`), retail materializes it
   (`addi r4,r4,0xA8`, then disp 0/8). Tried: struct-member array, element-scaled
   pointer, `s32` address, `volatile __ps_t *`, `__ps_t *base` indexing,
   `return arg0` to keep r3 live, and a compiler sweep (`psver.py`:
   3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3) — every combination folds. Not a
   point-version effect (README background agrees).
2. **psq_l hoist.** ngccc schedules the first `psq_l` above the `slwi`; retail
   keeps the address computation first. `-fno-schedule-insns`,
   `-fno-schedule-insns2`, `-O1`, `-O3` all keep the hoist.

The `psq_stx` variant (`(__ps_t *)(arg0 + OFF) + arg1*2`) is worse (indexed
store, no `add` at all) — the closest form is the base-indexed
`base[0x15 + arg1*2]` with OFF/8 pre-added to the index constant.

---

## M5.0u — 2026-09-28: three of the members above are NOT blocked; two decode traps

Four members of the "unpromotable / ~310 more" list above moved. Two of the
movements are **retractions of conclusions in this doc**, and both traps are
cheap to fall into again.

### 1. `psq_l f0, 8(rN)` where `rN = r1+8` is the SECOND pair temp, not the first

fn_800A08C0 (360B) was parked as a §6x-89 "**WANT keeps provably-dead
insns**" member. It is not dead: the reload is `psq_l f0, 8(r27)` with
`r27 = r1 + 8`, i.e. **`0x10(r1)` = `v[1]`**, not `v[0]`. Reading it as `v[0]`
makes a live spill look provably dead and manufactures a fake wall. The
2026-09-25 header here had done exactly that.

> **Rule: when the base is a frame-derived pointer, `8(reg)` means
> `0x10(r1)`, not `0x8(r1)`.** Any stack-slot map built from the raw
> displacement without resolving the base register is off by one slot.
> This invalidates slot maps generally, not just here.

Body shape that matched: `acc0(0x58) += v[0]` (forwarded reg) **and**
`acc1(0x60) += <reloaded v[1]>`; the scalar broadcast slot must be an
**8-byte** local written through its 4-byte union member
(`union { f32 f; __ps_t p; } sN; sN.f = f;` — a plain
`__ps_t s0 = *(__ps_t *)&f;` folds onto `f`'s slot and the frame collapses);
and the acc1 addend must be read through a named `__ps_t *p = v;` while both
spills use the array — that alone forces the `addi r27,r1,8`, the 5th saved
GPR, the `r1`-displacement spills and the `8(r27)` reload.

### 2. A `volatile __ps_t` stack array reproduces the DEAD `psq_st` — this doc's "impossible" claim is WRONG

Above: *"still trail by the fmr copy + larger frame + one trailing dead
`psq_st` — the same coin-flip"*, and *"this family is unpromotable until that
intermediate SN ProDG build is recovered"*.

fn_800A9200 (152B) is now EXACT under `-mps-float -fno-schedule-insns2`, and it
contains **both** a dead `psq_st` at sp+8 and a live one at sp+16, reproduced
byte-for-byte by a **`volatile __ps_t loc[2]`** local. Retail's
store/reload round-trip is exactly what a volatile PS local does; a plain
local is DCE'd or forwarded and the spill disappears. The real residue for
that fn was elsewhere (a `lis` hoisted to the block head instead of a delay
slot, and a 2-pair transposition) — not the dead spill.

**Re-test the ~310 listed members with a `volatile __ps_t` stack temp before
believing the "intermediate ProDG build" story.** Two more ingredients that
fn needed, both cheap:
* the `psq_l f0,16(r1)` must be a **named** temp feeding BOTH the field store
  and the reassignment of the PS variable (writing `a = d1; out[5] = loc[1];`
  costs 2 words and re-colours everything);
* the tail union scalar goes in the **`.flt.lo`** lane, not `.flt.hi`.

### 3. Opcode/table corrections (needed to decode by hand)

* `psq_l` = primary opcode **4 / XO 56**, **`psq_st` = 4/60**, **`psq_stu` =
  4/61** (not 4/56 for the store). `tools/ps_disasm.py` mislabels 60/61.
  `psq_stu + 8(r11)` genuinely **updates** r11.
* True layout is `OPCD|D|rA|W(1b)|I(3b)|d(12b)` with `I = (w>>12)&7`;
  `ps_disasm.py` prints a wrong I field. cc1 hardcodes I=0 for `__ps_t`
  derefs, so GQR1-7 quantized (D-form, I≠0) streams stay unreachable — but
  *indexed* X-form pair ops are emittable (see AGENTS §6ax-218).
* PS→SF extract emits `ps_mr`+`fcmpu` for **element 0** only. Using
  `.flt.lo` there gives `fmr` + a union spill + an `lwz/stw/stw` GPR round-trip
  and costs a word. (fn_800B2748, 164 insns.)
* cc1 never emits `ps_mr` for a PS↔SF conversion feeding a **store** — only for
  compares and builtin args. A 1-insn `__asm__("ps_mr %0,%1" : "=f"(x) : "f"(y))`
  wedge is the only route (documented in that draft's header).
* GCC 2.95 leaves a **4-byte gap between a `volatile __ps_t` array and an
  SF→PS register home** (`home = array_end + 4`), and the SF/PS store-load
  modes come out **inverted** vs retail. Budget the frame for it.

### 4. fn_800C9350 (368B) — SOLVED: split the FIRST pair copy into load + store

Want's `addi r10/r11/r29` sit **between** the `psq_l` and the `psq_st` of the
first `__ps_t` copy. Written as one fused `arg0->unk0x0 = arg1->unk0x0;`, ngccc
emits `psq_l`+`psq_st` back-to-back and hoists pair #2's `psq_l` into the
window. Keeping the pair live across the three base computations forces them
into the `psq_l`/`psq_st` latency slot:

```c
__ps_t t0;  t0 = arg1->unk0x0;
temp_r10 = (char *)arg1 + 0x28;
temp_r11 = (char *)arg0 + 0x28;
temp_r29 = (char *)arg0 + 0xA8;
arg0->unk0x0 = t0;
```

3 source lines, no flags, no asm. (The relative order of the addis vs the load
is itself not load-bearing — both orders reach 100%.)

### 5. fn_800A8D04 (152B) — the old park note's stack-slot map was off by one

Same class as (1): the draft's decoded map was built assuming `8(r9)` =
`0x8(r1)` with `r9 = r1+8`, i.e. every access was really `0x10(r1)`. With the
map corrected, `volatile __ps_t t[4]` + a `volatile` walking object pointer
+ a non-volatile second chain took it 2/38 → 31/38 words, size-exact.

---

## M5.0v — 2026-09-28: PS store-run permutation, the staging-pointer reload, and "the barrier is the bug"

Three more members, two of which correct how this doc frames two families.

### 1. A run of N identical `psq_st`s is a FIXED POSITIONAL permutation, not want's emit order

`fn_80091B00` (284B, 88.7% → byte-exact). ngccc reorders its twelve 255.0
`psq_st`s by a **fixed positional permutation of the SOURCE statements**:

```
p = [1, 0, 2, 3, 4, 5, 11, 6, 7, 8, 9, 10]      (N = 12)
```

verified identical for three different source orders, so it is positional and
NOT displacement-driven. To invert it, write the source in

```
0x28, 0x30, 0x38, 0x40, 0x58, 0x60, 0x68, 0x70, 0x48, 0x50, 0x78, 0x80
```

**and** give the RHS a strictly **alternating `bp[0]` / `bp[1]` lane phase** in
source order. The two lanes hold identical bytes, so the choice is
semantically free — it only decides which address pseudo (`8(r1)` vs `8(r10)`)
feeds the `psq_l`, and the scheduler keys the permutation on that. Flipping the
lane phase on the last six changes `p` to `[1,0,2,3,4,5,10,11,6,7,8,9]` and
drops the score to 80.3%.

**Do not permute to want's emit order** — that is a no-op, the scheduler
re-sorts. Invert the positional permutation instead. (Compare the integer
store-run rules: §4p-24 reverse, §6k-64 rotate-right, §6an-198 per-class
rotation. PS runs are their own, positional thing.)

And L4 (the AGENTS earlier float-literal lever) **does apply inside PS
blocks**: spelling 255.0f as the C literal instead of `extern f32
lbl_80297170;` moves the `lfs f0` back above the `psq_l f11,8(r10)` it must
precede — the last 2 words. Verified value-identical via
`src/r2d_802970FC.c`.

### 2. Under `-mps-float`, a `psq_st` whose PS source is a PSEUDO collapses — re-read through a staging POINTER

`fn_800BA704` (708B, 25.4% → 89.3%). If you take the register
(`t = P; … = t;`) or read the slot by array name, GCC forwards the value and
the whole tail collapses to 9 words per loop. What works is re-reading the
staged slot **through the staging pointer, non-volatile**:

```c
*(__ps_t *)tp = pp[0];        /* NOT  t = P;  … = t;  and NOT  volatile pairs[2] */
```

That single spelling restored the exact 10-word tail in all three loops and
fixed the instruction count. Loop 3 additionally needs **its own counter
variable** (`m`, not the shared `n`) so the count retires into r11 and
`mulli r10,r11,0x28` emits first (85.9 → 89.3%).

Also confirmed here: **`register __ps_t x __asm__("frN")` is silently DROPPED
by cc1 2.95.2/3.9.3** — PS/vector register vars do not bind at all (positive
control: pinning to r10 changed nothing). So PS colour fixes must come from
the source shape, never from a pin. Residual is doc-32-class: retail assigns
{sentinel, pp, out} = {r6,r7,r8} in creation order and cc1 reverses them.

### 3. A stale `"+f"` barrier is often the CAUSE of a hoist, not a fix

`fn_801B26D8` (288B, 95.8% to byte-exact). The residual was a 3-word transposition of two independent constant materialisations: the build order loads the rodata page anchor into r9, stores r3 to offset 0x54, loads the double into f13, loads constant high 0x4330 into r0 and then advances r3, while retail loads 0x4330 into r0 first and interleaves the same store, page load, double load and address advance in a different order.

The draft already carried `__asm__("" : "+f"(magic));` on the operand, and
**that barrier was hoisting the `lis r9`+`lfd` pair above the `lis r0,0x4330`**.
The fix is to make BOTH constant births opaque 1-instruction anchors
(`__asm__ volatile("lis %0,0x4330" : "=r"(bias));` and a `@ha` anchor for the
real rodata2 double) and **delete the pre-existing barrier** — keeping it caps
the function at 97.2%. Both anchors are value-preserving and carry no
relocation, so no private `.rodata` is synthesised and the real rodata2 double
is still the one subtracted.

**Rule: when a barrier is already in the draft and the residual is an
interleaving involving that operand, the first experiment is to DELETE the
barrier.** Barriers added in an earlier session are load-bearing for the score
they produced and are frequently load-bearing for the *wrong* order afterwards.
This is the barrier-side twin of AGENTS §6aq-222 ("remove a stale FLAG the
moment it stops being needed").

## Addendum 2026-10-02: under `-mps-float` **both** `f32` members of a
## `union { f32 lo, hi; __ps_t ps; }` land at **offset 0** (fn_800C6EC0)

Sharpens the "frame members must be raw `f32[2]` arrays with punned access"
note above: the reason is *not* only a 16-byte alignment/padding shift — ngccc
3.9.3 puts **every** `f32` member of a PS union at byte offset 0, so `.hi`
silently aliases `.lo` in MEMORY. Probe (one TU, `-O2 -G0 -mcpu=750
-mps-float`, `volatile` struct so nothing is folded):

```c
typedef union { f32 lo, hi; __ps_t ps; } PU;
typedef struct { u8 pad[8]; PU p; f32 a[2]; } S;
PU v; v.ps = gv; v.lo = f; v.hi = f; S s; s.p.lo = f; s.p.hi = f; s.a[0]=f; s.a[1]=f;
/* emits:  psq_st f0,16(r1)   stfs f1,0x10(r1)   stfs f1,0x10(r1)   <-- same offset twice */
/*         stfs f1,0x10(r1)   stfs f1,0x10(r1)                          <-- PU.lo and PU.hi */
/*         stfs f1,0x18(r1)   stfs f1,0x1c(r1)                          <-- f32[2] is correct */
```

(`f32 a[2]` in the same struct is correct, and so is `struct {f32 hi,lo;}` when
it is *not* in a union with a PS member.) This is invisible for a **register**
local — which is why the promoted `SN_PS_type dot; ... dot.flt.hi` spellings
(§7q) are fine — and only bites a PS union used as a **volatile frame member**.
Symptom seen in fn_800C6EC0: every half-lane `stfs` lands one slot low
(`0x68` for want `0x6c`, `0x78` for want `0x7c`) while the 8-byte `psq_st`
lands right, which looks like a scheduling bug and is not.

**Rule: in a PS frame template, express two-lane slots as `f32[N]` arrays
(8-byte slots via `*(volatile __ps_t *)&fs.slot = v`) and never as
`union { f32 lo, hi; __ps_t ps; }`.** Same conclusion as the earlier note,
now with the mechanism and the exact probe.

## Addendum 2026-10-18: probe-verified PS sub-opcode (XO) map + two idioms (fn_800EA2CC)

Probe compiles against ngccc 3.9.3 (`-O2 -G0 -mcpu=750 -mps-float`), one
builtin per function, raw words read back (llvm-objdump mis-decodes PS words
as Altivec -- read the hex). Field layout is the A-form (frD 6-10, frA 11-15,
frB 16-20, frC 21-25, XO 26-30, all MSB-numbered):

| builtin | XO | notes |
|---|---|---|
| merge00/01/10/11 | 16 | variant in frC = 16/17/18/19 |
| muls0 / muls1 | 12 / 13 | |
| madds0 / madds1 | 14 / 15 | |
| madd | 29 | madd(a,b,c) = a*b+c with frA=a, frC=b, frB=c |
| msub | 28 | |
| sum0 / sum1 | 10 / 11 | |
| div | 18 | |
| sel | 23 | |
| res | 24 | reciprocal estimate |
| rsqrte | 26 | rsqrt estimate |
| neg | 40 | |
| ps_mr builtin | -- | ICEs (optabs.c:4116); plain C pair copies emit ps_mr instead |

Idiom 1 -- cheap sqrt by composed estimates: `res(rsqrte(x))` (rsqrte first,
then res of the result) approximates sqrt(x); seen as `sum0; rsqrte; res`
with all operands in one FPR.

Idiom 2 -- frame structs need NO leading pad: the compiler leaves sp+0..7
empty on its own (minimal probes, ProDG 3.5/3.7/3.8.1/3.9.3 all agree, with
and without calls and named smalls), so the first pair member of a frame
template lands at sp+8 by itself. A leading `_00[8]` shifts every pair slot
8 too high (and declaration order does not move it). Size the 12 bytes of
named smalls to land after the pairs instead.
