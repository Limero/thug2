// STATUS 2026-10-21: 94.44% (85/90 words), object 8B SHORT of want (360/368).
//   All five residual words are the function tail: want keeps TWO `return 0`
//   sites — the `t == NULL` path exits to its own `li r3,0` placed after the
//   inner one, and the `*(t+4) == 0` / fall-through path uses a `li r3,0; b`
//   pair that jumps over it.  That is one `b` + one `li` more than this build
//   emits: cc1 cross-jumps the two identical return-zero blocks into one, so
//   the tail comes out 8B short.  Shapes measured, all still 360B with the
//   same 5 tail words: two-return form (`if (t == NULL) return 0;` +
//   trailing `return 0;`), goto form with separate `zero_a`/`zero_b` labels,
//   inner `return 0;` after the `return 1;` (that one also turns the compare
//   into a store-flag `subfc/subfe/neg` sequence), and -fno-thread-jumps /
//   -fno-expensive-optimizations / -fno-rerun-cse-after-loop / -fno-gcse on
//   the two-return form.  `-fno-crossjumping` / `-fno-jump-optimization` do
//   not exist in this cc1.  Same wall as fn_8013928C: retail keeps a block
//   this build's jump optimizer merges away.
//
// PARKED 2026-10-05: best measured verdict NEAR 92.4% (85/92 words).
// family=m2c range=0x800DF924-0x800DFA94 size=368B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Improved 39.7% -> 94.4% (was a broken m2c draft: `0;` statements, a bogus
// block_9/block_10 conversion diamond, and five undeclared callees).
// Everything from the prologue through 0x800DFA78 now matches word for word;
// the residual is the last two instructions of the tail (see below).
//
// Findings, in order of impact:
//
// 1. **The scale selection must be ONE ternary expression, not an if/else-if
//    chain.** Assigning `v` inside three separate `if` arms gives ngccc three
//    sibling blocks that all tail-merge into the float->int conversion, and
//    the FP register allocation collapses (37% -> 82%).  Spelling it as
//      k = (u32)((A || B) ? spC * SEC : ((C || D) ? spC * FRM : spC));
//    reproduces want's exact shape: the SEC arm is fully inlined (11 insns),
//    the FRM arm jumps *into the middle* of it (just before the 2^31 load),
//    and the default arm re-tests with the opposite branch polarity
//    (`bso` instead of `bns` + `b`).  82% -> 86%.
//
// 2. **`spC * scale`, NOT `scale * spC`.**  Both operands are commutative, so
//    the emitted `fmuls f0,f0,f13` is textually identical either way, but
//    ngccc picks which one keeps f0.  want loads spC into f0 and the constant
//    into f13 (`lfs f0,0xc(r1)` / `lfs f13,-0x5b5c(r11)`); the reversed
//    spelling swaps the two loads and costs ~9 points (94.4% -> 77.4%).
//
// 3. **`(u32)` is a THREE-WAY cast in ngccc, and the compare type must agree
//    with it.**  `(u32)f32val` expands to
//      fcmpu cr0, f13, f12      ; f12 = 2^31, loaded from the pool
//      cror   cr0un, cr0eq, cr0gt
//      bns / bso
//      -> fctiwz / stfd / lwz                       (v <  2^31)
//      -> fsub / fctiwz / stfd / lwz / xoris 0x8000  (v >= 2^31)
//    The `xoris` re-adds 2^31 as a raw bit, so the pair computes exactly
//    `(u32)v`.  `(s32)f32val` is the plain `fctiwz` with no compare at all.
//    See AGENTS-recipes.md 231 (the mirror-image u32->f64/s32->f64 pair).
//    This is also why the final comparison must be written UNSIGNED:
//    `fn_800AA02C(t) > (u32)k` emits `cmplw` (XO=32, L=0), while
//    `> (s32)k` emits `cmpw` (XO=0).  want is `cmplw`.  93.3% -> 94.4%.
//
// 4. **The tail must be nested `if` + early `return 1`, then `return 0`.**
//    `return (x > y) ? 1 : 0` and a `res = 0/1` chain both get if-converted
//    into the branchless `cmpw cr7 / mfcr / rlwinm` sequence, which is one
//    instruction too short and shifts the whole epilogue (81.7% - 86.8%).
//
// Pool constants (all in section 8 / .rodata2, page 0x802A):
//   0x8029A4A4 = 1000.0f          (QB_SECONDS/QB_SECOND scale, ms -> frames)
//   0x8029A4B0 = 16.666666f       (QB_FRAMES/QB_FRAME scale)
//   0x8029A4A8 = 2147483648.0     (f64 2^31, the (u32) cast bias)
//
// RESIDUAL (2 instructions, 8 bytes), re-attacked 2026-10-05:
// want's tail compares r3 against r31 for the taken exit with r3 set to 1,
// while the two fallthrough arms each set r3 to 0 (the first joined by the
// unk0x4==0 branch and the compare-false path, the second by the t==NULL
// branch) before the shared epilogue,
// i.e. a THREE-input exit phi {1, 0(A), 0(B)} that ngccc emitted as real code
// and did NOT if-convert, while it still declined to tail-merge A into B.
// Measured map of every C spelling tried (all keep want's first 340 bytes):
//   * 1 `return 0` site  (this file)          -> A/B tail-MERGED  -> 360B (94.4%)
//   * early `if (t==NULL) return 0;`         -> same merge       -> 360B
//   * `else return 0` on the unk0x4 test      -> same merge       -> 360B
//   * 2 sites, cmp-false joins the inner site -> compare if-CONVERTED:
//        subfc r3,r3,r31 ; subfe r3,r3,r3 ; neg r3,r3 (the `? 1 : 0` expander)
//        and A collapses to `b EXIT`          -> 364B (89.0%)
//   * 3 sites (both `else` arms + final)      -> same setcc       -> 364B
//   * uninitialised `s32 res` + `res = 1`     -> dead-code disaster, 288B
// So the two available tails are "merged 360B" and "setcc 364B"; want sits in
// the window where ngccc does BOTH passes' opposite jobs.  The named cause is
// a jump-optimisation heuristic (crossjumping / jump-thread / the `? 1 : 0`
// if-converter), NOT a source-shape bug: `-fno-crossjumping` is rejected by
// cc1 ("cc1: Invalid option `-fno-crossjumping'"; same for
// `-fno-thread-jumps`/`-fno-reorder-blocks`), so there is no flag lever.
// The body above is the best measured spelling; leave it alone.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029A4A4;
extern f32 lbl_8029A4B0;

s32 ContainsFlag(CStruct *arg0, s32 arg1);
s32 GetFloat(CStruct *arg0, s32 arg1, f32 *arg2, s32 arg3);
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
void *fn_800AA84C(void *arg0, s32 arg1);
s32 fn_800AA02C(void *arg0);

s32 fn_800DF924(s32 arg0, CStruct *arg1) {
    s32 sp8;
    f32 spC;
    u32 k;
    void *t;

    GetChecksum_2(arg1, QB_BUTTON, &sp8, 1);
    GetFloat(arg1, 0, &spC, 1);
    k = (u32)((ContainsFlag(arg1, QB_SECONDS) || ContainsFlag(arg1, QB_SECOND))
                  ? spC * lbl_8029A4A4
                  : ((ContainsFlag(arg1, QB_FRAMES) || ContainsFlag(arg1, QB_FRAME))
                         ? spC * lbl_8029A4B0
                         : spC));
    t = fn_800AA84C((u8 *)arg0 + 0x24, sp8);
    if (t != NULL) {
        if (*(s32 *)((u8 *)t + 4) != 0) {
            if (fn_800AA02C(t) > (u32)k) {
                return 1;
            }
        }
    }
    return 0;
}