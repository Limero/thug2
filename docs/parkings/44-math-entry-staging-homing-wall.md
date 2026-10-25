# 44 — libm entry-staging / hot-value-homing allocator wall

**Status: PART-SOLVED (→ 2026-09-01 floor + 2026-09-02 kernel_cos double promoted; 5 members improved, still gates ~2 KB of fdlibm log/fmod/sqrt/tanh + one kernel_cosf cousin).**

## Signature

The game's libm objects show two related allocator behaviors ngccc cannot
reach from any C spelling tried:

1. **Entry staging of modified doubles.** Every store of a computed or modified double goes through a staging copy while the value stays live in its incoming register, with the value staged through f0 into a frame spill slot while f1 stays live.

   Reproduced via unpinned value + staging var pinned `__asm__("fr0")` +
   `"+f"` barriers — but only in isolation.

2. **Scratch-birth → home-copy webs without pins.** Word loads land in
   scratch registers and are copied to their saved homes (`lwz r9; mr r10,r9`
   class), and hot values are homed from entry into specific
   volatile/saved registers (sqrt: hi-word loaded DIRECTLY into its saved-reg
   home; tanh: x lives in f4; log family: staged stores per above), where
   ngccc routes everything through reload scratches or neighboring registers,
   cascading whole-function role rotation.

## Resisted (per member)

Register pins (function-level pins collapse allocation — see nested-scope
pin recipe AGENTS.md §6as-3), "+r"/"+f" barriers, `-fno-regmove`,
`-fno-schedule-insns[-2]`, `-fno-gcse`, decl/statement orders, union vs
pointer-pun forms, all five ProDG versions.

One UNTESTED combination worth trying first on retry:
`-fno-regmove` + full pin set (observed `-fno-regmove` ALONE produce
both entry `mr` copies at 36% on fn_8026EAAC before the variant was
superseded).

Also note doc-28 interplay: several members additionally cache compares
across bls (mfcr/mtcrf), which is its own wall.

## Members

| Function | Identity | Size | Parked @ | Blocking detail |
|---|---|---|---|---|
| fn_8026E750 | `fmod(x,y)` fdlibm e_fmod.c (incl. inline subnormal ilogb loops) | 0x35C | **13.0% (187/215, was 10.7%)** | pure branchy integer math — floor-entry helps 1 word; needs hand rebuild |
| fn_8026EAAC | `__ieee754_log` e_log.c (0x95f64 normalize, Lp1–Lp7, x==1 fast path) | 0x2FC | **15.7% (30/191, was 7.1%)** | entry `mr r5/r11` exact, now `xoris/fsub` poly wall |
| fn_8026EDA8 | `log10` (k·L10hi/(k·L10lo + log·ivln10)) | 0x148 | **62% masked (31/82, 36 sda, was 6.1%)** | `mr r5,r9` redundancy + `rlwimi` + tail `fr31` dk homing |
| fn_8026F2CC | log-family sibling (sdata2-relative consts) | 0x290 | 0.0% | needs SDA route too (doc 43) — not re-attacked |
| fn_8026FD2C | `sqrt(f64)` — body semantically 1:1 (NaN x²+x, ±0, sNaN, subnormal normalize, two digit loops, round-to-odd tail) | 0x214 | **69.9% NEAR (77.4% with `-fno-schedule-insns2`, was 3.0%)** | **direct-homing lever found**: `lwz r9,8` pinned `var_r9 __asm__("r9")` + `lo_tmp r10→r8` fixes prologue 3→57%; full `r11/r4/r3/r12/r30` pins →69.9% |
| fn_8026FF40 | `tanh(f64)` full decode (threshold chain, Horner poly, k-indexed lfdx tables) | 0x234 | **25.5% (36/141 sda, was 14.9%)** | `x fr4` pin + `−fno-schedule-insns −fno-schedule-insns2` helps; poly FPR scheduling remains |

Cousin signature (web-color ties rather than entry staging): the
kernel_cos pair — **`fn_80271444 __kernel_cos double PROMOTED EXACT 2026-09-02`**
(`src/fn_80271444.c`, `FLAG -msdata=eabi -G8`, `LINK-SIM EXACT` via `hi:r9 lo:r10→r5/r11` + `xy:fr0 hz:fr1`) and `fn_80271948 __kernel_cosf` **improved 68%→79.7% (15→12 sda shared, 15 clean)** with `zp fr12 / hz fr8 / top fr8 shared` but `qx addis` LICM hoist still parks it.
fr-pin rule: `xy/hz` `fr0/fr1` now proven (71444); single-store `w=hx-0x01000000` vs double's two-store `w[0]/w[1]=0` explains float hoist.

## Zone constant map (for rebuilds)

.rodata2 log pool: lbl_802B2288=-inf, 2290=0.0, 2298=2^54,
**22A0=0x4330000080000000 (signed-int→double cast pool)**, 22A8=log10_2lo,
22B0=ivln10, 22B8=log10_2hi; log's own set at 2200/2208/2210/2220 + Lp table
2230–2268. The §6j-1 manual int→double dance against these REAL pool doubles
is promote-clean here (no doc-14 private-pool issue). Verified expansion
form: `srwi sign; add t=k+s; xoris t,0x8000; stw; lis 0x4330; stw; lfd;
lfd pool; fsub`.

## 2026-09-01 — PART-SOLVED: fn_8026E5DC (fdlibm floor) 93.5% → EXACT

**fdlibm `floor()` fn_8026E5DC promoted byte-exact** after being parked at
93.5% with 6 residual interior diffs (the "reload-allocator tie-break on r9"
class). Two-part recipe, both needed:

1. **Pin BOTH the load targets AND the homes to matching pairs.** The
   scratch→home web is `lwz r9,8(r1); lwz r10,0xc(r1)` (hi word into r9, lo
   word into r10) followed by copies into the saved homes. Pinning the loads
   is not enough — GCC then picks the *copy* registers arbitrarily:
   `register s32 hi __asm__("r9"); register s32 lo __asm__("r10");` for the
   `__asm__("lwz %0, ..." : "=r"(hi))` outputs AND `register s32 i0
   __asm__("r10"); register s32 i1 __asm__("r6");` for the homes forces the
   full `lwz r9/r10; mr r6,r10; mr r10,r9` web.

2. **THE lever: copy-statement ORDER in the source.** All 15 prior shapes
   wrote `i0 = hi; i1 = lo;` (hi first) and plateaued at 87/93 — ngccc
   emits `mr r10,r9` (i0's copy) before `mr r6,r10` (i1's copy), but WANT
   copies the LO word first: `mr r6,r10; mr r10,r9`. Flipping the source to
   `i1 = lo; i0 = hi;` makes ngccc emit exactly WANT's order → 93/93
   masked, DOL byte-identical. The pragmatic rule: when the home copies are
   to DIFFERENT registers, the source order of the two copy statements
   controls ngccc's mr order — try both orders even if the writes look
   independent.

Sibling wall fn_8026FD2C (sqrt) is a harder variant (hi word loaded DIRECTLY
into the saved home, no copy web at all) — the order-flip lever does not
apply there. Remaining doc-44 members unchanged.

## 2026-09-02 — PART-SOLVED x2: fn_80271444 (__kernel_cos double) → EXACT; others improved

**fn_80271444 (__kernel_cos double, 244B) promoted LINK-SIM EXACT** (`src/fn_80271444.c` with `FLAG -msdata=eabi -G8`, `DOL byte-identical` via full link). Same floor lever generalized to FPR tail: bitcast `hi:r9 lo:r10 → i0:r10 i1:r6` plus `lx=lo; hx=hi` lo-first fixed the `lwz r9/r10 vs r11/r12` web (15→0 words), and `register f64 xy __asm__("fr0")` / `hz __asm__("fr1")` fixed the per-path `{half,hz}/{one,top}` color swap (`f0↔f1/f13`). Verified via `tools/sda_verify.py -msdata=eabi -G8` (`LINK-SIM EXACT: 244 bytes`). This was the 75% cousin at `0x80271444` — the SDA-bitcast case is now solved.

Batch re-attack of remaining members (7 parallel agents, `tools/sda_verify.py` + `gen_leaves.compile_fn` masked scoring):

| Function | Before | After | Best lever this round | Remaining wall |
|---|---|---|---|---|
| fn_8026EAAC (__ieee754_log, 0x2FC) | 7.1% (16/191) | **15.7% (30/191, 912B)** | floor `hi:r9 lo:r10→r5/r11` lo-first fixed entry `stwu/fmr/lwz/mr` exact (0x0-0x17), first diff `or.` vs `lis` | poly `fsub f3=x-1.0` staging `fr0` pin + `xoris 0x3ff0`/`or` scheduling; `dk=(double)k` `xoris 0x8000` dance `fsub` |
| fn_8026EDA8 (log10, 0x148) | 6.1% / 75 sda mism | **62% masked (31/82, 36 sda mism, 324B)** | `-fno-regmove` + `hi:r9 lo:r10 hx:r5 lx:r11` + `fr.d volatile struct -0x20` + `memory` barrier fixed `li/lis` hoist; `e20->r0 carry->r11 kplus->r0` pins | `mr r5,r9` after 3rd reload redundant (hx already in r5), `rlwimi` vs `clrlwi+or`, tail pool `lis r9` reuse + `dk` `fr31` homing |
| fn_8026FD2C (sqrt, 0x214) | 3.0% | **69.9% NEAR (77.4% with `-fno-schedule-insns2`, 532B)** | **NEW direct-homing lever**: `lwz r9,8(1)` pinned `var_r9 __asm__("r9")` direct + `lo_tmp __asm__("r10") → var_r8` with `memory` barrier fixed prologue `stwu/stmw/lis/sign/fmr/stfd/lwz/mr` from 3%→57%; `ex:__asm__("r11")` + `clrtmp:r0` + full `r11+r4+r3+r12+r30` pins → 69.9% | `sign r6≠r31`, `add r8,r8,r8` vs `slwi`, `srawi r10` vs `r6`, final `stw r5/r6; lfd` tail |
| fn_8026FF40 (tanh, 0x234) | 14.9% / 131 sda | **25.5% (36/141, 105 sda mism)** | `register f64 x __asm__("fr4")` + `fmr/stfd/lwz` floor-entry `hi/lo` via `fmr 0,%2` → 21% → `−fno-schedule-insns −fno-schedule-insns2` → 25.5% | `x` `fr4` homing still `fr6` got, poly `t2/t4/num/den` FPR scheduling |
| fn_8026E750 (fmod, 0x35C) | 10.7% / 190/215 | **13% (187/215, 900B)** | floor-entry for both `x,y` via `fmr 0,%2` → `hi/lo` + `1× volatile double` → 187 vs 190 | m2c `unkspC` phantom + `sp8` bit-pun structure; needs hand rebuild |
| fn_80271948 (__kernel_cosf float, 236B) | 68% / 19 sda | **79.7% masked (47/59, 12 sda shared / 15 clean)** | exhaustive 4096 FPR combos: `zp fr12 / hz fr8 / top fr8 shared` → 12/59 (frame `0x20`); clean `0x18` remains 15/59; `qx` `addis r0,r11,-0x100` LICM hoist resists `+r hx`/`volatile cvt`/`r0` pin | `qx` single-store vs double's two-store `w[0]/w[1]=0`; `half/one`/`zp` FPR tie |

All drafts remain `src/wip/` (inert, `DOL byte-identical`); only `fn_80271444` is promoted. The `−fno-regmove + full pin set` untested combo is now tested on log family (no gain over floor lever alone) and on `log10`/`tanh`/`fmod` (no gain or regression). Sibling `fn_8026F2CC` (0% SDA log) not re-attacked this round — route via `doc 43` pending.
