# 41 — Hand-written assembly module (NeGo texture-upload subsystem)

**Status:** **MOSTLY SOLVED 2026-10-03 — this doc was badly stale. The "hard wall"
was wrong.** 5 of the region's members are now byte-identical matches. The
"I=0 is unreachable from C" premise was false: `ps_l(v,w,i)`/`ps_st(d,v,w,i)` are
**cc1 builtins with an explicit I argument** (`include/dolphin/SN_PS.h`).
**Region:** `0x8024EF18`–`0x80250834` (Neversoft texture-upload / mip-pipeline kernels).
**Boundary was WRONG until 2026-10-03:** this doc previously claimed `0x80250E6C`. The
tight wall is the I≠0 `psq` cluster. The `0x80250834`–`0x80250E6C` tail is NOT part of
this module — do not park functions there on this doc's authority.
**Related:** #06 paired-single, #35 (mfctr fingerprint overlaps),
§6av-205/§6aw-177/178, §6af-180 (asm budget).

## THE RECIPE (this is the whole trick — it transfers)

The wall was never "GQR is unreachable". It is ONE specific cc1 limitation:

> `__builtin_psq_l(p, W, I)` emits a template with a **hardcoded 0 displacement**:
> `psq_l %U1%X1 %0,0(%1),%2,%3`. The *other* load path (a plain `__ps_t` deref) is the
> only one that folds a displacement, and it **hardcodes I=0**.

So for a wanted `psq_l fN, d(rX), 0, I7` with `d != 0` there is no single C spelling —
you take **both halves**:

```c
p0 = __builtin_psq_l((void *)(S), 0, 7);          /* d=0 : builtin keeps I=7 */
__asm__ volatile("psq_l 1,4(%0),0,7\n\t"            /* d!=0 : raw asm keeps d   */
                 "psq_l 2,8(%0),0,7\n\t"
                 "psq_l 3,12(%0),0,7"
                 : : "r"((s32)(S)) : "fr1", "fr2", "fr3");
```

Stores need no asm at all — `__builtin_psq_st((void*)(D+2), p1, 0, 7)` emits the
displaced I=7 store directly. Keep the paired-single registers pinned with
`register sn_ps p0 __asm__("fr0")` (a *declaration*, emits zero insns), and take the
caller-preset regs via file-scope `register s32 f_src __asm__("r6")` pins.

**Proven on:** `fn_8024FAD0`, `fn_8024F360`, `fn_80250170` (pre-existing),
`fn_80250020` (71.4% → EXACT, promoted 2026-10-03), `fn_8024FEE0` (70.0% → EXACT,
promoted 2026-10-03). Both new promotions leave `main.dol` byte-identical.

### Still parked, and why (asm budget — NOT an expressiveness wall)

`fn_8024F794` / `fn_802503E8` / `fn_80250624` sit at **66.2–66.4%** and need **48 of 142
insns (33.8%)** from asm to close — over `promote_wip.py`'s `ASM_MAX_SHARE = 0.30`.
They are blocked by the **budget**, not by cc1. `fn_8024FAD0` (already promoted, 36.6%
true asm share) is the precedent that the guard does not actually catch these — see the
macro blindspot below. Forcing them is a maintainer call, not an agent-side move.

### The guard has a macro blindspot (worth fixing)

`promote_wip.py`'s `_asm_template_counts` scans **source text** and does not expand
macros, so an `__asm__` hidden inside a `#define` and used 8× is counted **once**.
Measured: `src/fn_8024FAD0.c` reports **0** asm insns while really emitting **64**;
`fn_80250020.c` reports **4** while really emitting **24**. True shares:
`fn_8024FAD0` 36.6%, `fn_8024FEE0` 30.0%, `fn_80250020` 28.6% — the last two sit
exactly *at* the 30% / 24-insn thresholds and pass only on the boundary. Count
macro-expanded asm when enforcing this.

## What is genuinely still hard-asm (not solved by the recipe)

The GQR drivers that CALL these kernels remain parked and are the real asm-core:
`fn_8024EF18`, `fn_8024F65C`, `fn_8024FE30`, `fn_8024F2AC`, `fn_802502C0`,
`fn_8024F9CC`, `fn_8024F4B0`. Re-probed 2026-10-03 on ngccc 3.9.3 **and** mwcc GC/1.3.2
**and** 1.2.5n: all three compilers ALWAYS save LR as `mflr r0` + `stw r0` and group
saves into `stmw` (even at exactly 2 saved regs), so the LR-in-callee-save dance and
the interleaved individual `stw` saves have **no C spelling**. All of it is reachable
via inline asm (`mflr`/`stw`/`mtlr` with `"=r"`; `register int a __asm__("r11")` gives
`7c 6b 1b 78`), but these are only 3–11% asm — well inside budget — so they are worth
a real attempt rather than a park.

### Fingerprint triage, corrected (measured 2026-10-03)

Several fingerprints in the original list are **much weaker than claimed**:

- **`mfctr` is NOT a wall at all** — 306 sites across **226 already-matched functions**
  (`fn_8001F738` has 11). Drop it from the park-trigger list.
- **`mflr`-into-callee-save is rare**: 66 sites in all of `.text`, only **2** inside a
  matched function (`fn_8025AFC0`, `fn_8025B180`) — so it is a real signal, just rarer
  than "66, none matched" claimed.
- **I≠0 `psq` is not exclusive to hand-written asm**: 128 sites live inside
  **3 already-matched functions** (`fn_8024FAD0` 64, `fn_8024F360` 32, `fn_80250170` 32).
- A bare GQR `mtspr`/`mfspr` SPR 912–919 hit is **not** evidence of this module — that
  traffic recurs in 0x8012/0x8014/0x8024/0x8025/0x8026.

Census of D-form `psq` (`OPCD|D|rA|W@15|I@12|d`) over all of `.text`: **I=0: 18,293**
(reachable from C — 204 matched fns contain them, e.g. `src/fn_800063B8.c` =
`-mps-float` + `arg1[0] = arg2[0]` → byte-identical `e0040000`).

**I≠0 needs per-opcode counting — 400 is `psq_l` ONLY** (op 56), and there is a
**second cluster outside this module**:
- `psq_l` (op 56): **400** I≠0, one cluster `0x8024EFBC`–`0x80250834`.
- `psq_st` (op 60): **278** I≠0, TWO clusters — `0x8024F0A0`–`0x80250854` (272, this
  module) and **`0x802538CC`–`0x80253B2C` (6, a separate function)**.
- Combined: **678** I≠0 sites, `0x8024EFBC`–`0x80253B2C`. A scan that tests only
  opcode 56 will wrongly report "one cluster" and miss the outlier.

## Symptom: five co-occurring fingerprints, none emittable from PURE C

Any ONE of these in want is strong evidence of hand-written asm (re-probed on ngccc
3.9.3 AND mwcc GC/1.3.2 / 1.2.5n on 2026-10-03); two or more = park immediately
**for a pure-C attempt**:

1. **CTR save-pair**: `mfctr rN` prologue / `mtctr rN; blr` epilogue around body code.
   **WEAK — demoted 2026-10-03:** 306 `mfctr`/`mtctr` sites sit inside **226
   already-matched functions** (`fn_8001F738` has 11). Do NOT treat this as a park
   trigger on its own. (fn_8025085C/9000/9097C/90A1C, fn_8024C624, fn_8024D6B0.)
2. **Individual interleaved `stw` saves instead of `stmw`** — even exactly 2 callee-saved
   regs still yields `stmw` from ngccc. Combined with an **LR dance** (`mflr r15/r18`
   held across bls, `mtlr` at exit) it is conclusive, and this one **survives re-probe**:
   ngccc 3.9.3, mwcc GC/1.3.2 and mwcc GC/1.2.5n all *always* emit `mflr r0`+`stw r0`
   and `stmw`. **Strongest remaining signal in the region.** (fn_8024F2AC, F65C, F9CC,
   FE30, 502C0, 50AC4 — the last also keeps full mfcr/mtcrf preservation with ZERO calls.)
3. **GQR quantized paired-single streams**: D-form `psq_l/psq_st` with **I≠0** (I is a
   3-bit GQR selector at `(w>>12)&7`, W at `(w>>15)&1`). **SOLVED — see THE RECIPE
   above.** cc1's `psq_l` builtin hardcodes a 0 displacement while the plain-deref path
   hardcodes I=0; take each half from a different path. NOTE: correct psq field layout is
   `OPCD|D|rA|W(1b)|I(3b)|d(12b)` — tools/ps_disasm.py printed a wrong I field. Indexed
   X-form pairs (`__builtin_psq_lux`) ICE in cc1 ("unrecognizable insn"), so there is no
   X-form route. Matched: FAD0, F360, 50170, 50020, FEE0. Still budget-blocked:
   F794, 503E8, 50624.
4. **Non-ABI fixed-register interfaces**: args passed in r11/r12/r15, float multiplier
   out-of-band in f8 (`lfs lbl_8024FD8C`), prologue-less fragments reading caller-preset
   regs. Internal conventions between asm kernels — but **not a wall**: file-scope
   `register s32 x __asm__("r11")` pins reach them from C (this is exactly how
   `fn_80250020`/`FEE0`/`FAD0` pass). (F65C/F794/F9CC/FE30; fragments 503E8/50624.)
5. **ABI-conformance saves**: callee saves 11 callee-saved regs it never uses, to honour
   the ABI its asm CALLERS assume (fn_8024F4B0) — the exact inverse of what a compiler
   does. Only 3% of F4B0's insns, so **worth attempting**, not a park.

## What IS matchable inside the region

Frameless leaf kernels that only *look* exotic can still fall to file-scope register vars:
`register u32 g_a2 __asm__("r5"); g_a2 = arg2; g_a2 <<= 4;` forces IN-PLACE param
mutation (local pinned aliases split the web through r0) — cracked `fn_8024FD90`
(dcbst mip-flush, FLAG pair `-fno-schedule-insns -fno-schedule-insns2`) and
`fn_8024F5C0` (39/39, caller-preset inputs homed r20-r27, zero prologue) this way.
`dcbz`/`dcbst` emit cleanly via volatile asm with `"r"` inputs.

## The inline-asm question, answered (2026-10-03)

Yes — and the region has since been largely converted. The trade-off that still governs:

- **A few non-C insns in an otherwise-C function: sanctioned.** This is the recipe
  above (3 displaced `psq_l` per chunk) and the `"r3"`-clobber trick in
  `src/fn_800063B8.c`. Both are promoted, byte-identical matches.
- **Whole-body transcription: still banned** (`AGENTS.md` §5, and
  `promote_wip.py`'s `ASM_MAX_SHARE`/`ASM_MAX_BLOCK`). The trio F794/503E8/50624 would
  need 33.8% and must wait for a maintainer decision — with the macro-blindspot caveat
  above, since the guard would not actually catch them.
- **The `fn_8024EF18`/`F65C`/`FE30`/`F2AC`/`502C0`/`F9CC`/`F4B0` drivers are only
  3–11% asm.** They are inside budget and are the best remaining targets here.

## Retry hints

- **Read THE RECIPE at the top before touching any member.** Most of this region is
  already solved; the stale "hard wall" note cost multiple sessions.
- Do NOT re-prove "cc1 can't do GQR" — it can, via `ps_l`/`ps_st` builtins plus asm for
  the displaced loads.
- Do NOT re-prove "pure C can't do this" — measured and recorded above.
- Cheap screens: (a) count `mflr` into a callee-saved register across `.text` (66 sites,
  only 2 inside matched fns); (b) check whether an address falls in the single I≠0 `psq`
  cluster `0x8024EFBC`–`0x80250834`.
- `0x80250834`–`0x80250E6C` is **outside** this module despite the old boundary claim.
- The two EXACT-masked-msdata neighbours (`fn_8024EE00`, `fn_8024EE6C`) are NOT part of
  the asm module: they are plain-C heap init/free-pair functions whose one remaining
  word is an R_PPC_EMB_SDA21 reloc unverifiable standalone — promote via the §5q manual
  registration route (twin: `src/fn_80252C3C.c`).
