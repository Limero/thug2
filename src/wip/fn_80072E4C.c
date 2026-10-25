#include "types.h"
// PARKED 2026-09-30: 5.8% -> 72.5% (NEAR) — hand-rebuilt from the DOL
// family=m2c range=0x80072E4C-0x80073594 size=1864B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: official `test_wip_drafts.py --addr 0x80072E4C` = NEAR 72.5% (128 masked
// diffs of 466) and the object's .text is now the EXACT 1864B = want's size, so
// the masked compare is correctly aligned and every remaining diff is a local
// one. Audited per §6bw: 5/5 intra-function R_PPC_REL14 targets correct, all 53
// R_PPC_REL24 call relocations in want's order. Object carries only .text +
// .rodata (cc1's own 8-byte int->double pool; `tools/fix_fp_pool.py` retargets
// it to the real lbl_80295590 at promote time, so this stays promote-clean).
//
// LAYOUT (byte-exact vs want):
//   stwu -0xb8 | stfd f27..f31 at 0x90,0x98,0xa0,0xa8,0xb0 | stw r0,0xbc.
//   Locals via ONE frame-template struct (§6q-86):
//     struct { f32 a20..a38; s32 g4; s32 col; char t[0x24]; } fr;
//   lands the 7 write-only f32 at 0x20..0x38, col at 0x40, the region tail at
//   0x44..0x67, and lets cc1 put its DFmode conversion temp at 0x70/0x74 — all
//   exactly want. The struct must be ONE object: as separate scalars the
//   non-address-taken ones are DCE'd and the frame is wrong.
//
// THE THREE WINS OF THIS ROUND (all plain C, no flags, no pins, no barriers):
//
// 1. THE REPEATED 0.5 ARGUMENT NEEDS DISTINCT ADDRESS WEBS (§6u-6 / §6bt web
//    identity) — this is what made the LENGTH exact. want re-loads
//    lbl_802955C8 into the f3 argument slot at EACH of the four
//    `fn_8001F0F8` call sites, off ONE shared page anchor (r26). Writing the
//    plain symbol at all four sites lets cc1 hoist it once into a callee-saved
//    FPR and emit `fmr f3, fN` at the rest, which is 1 load instead of 4 and
//    costs 2 instructions overall. Fix: give the first THREE sites three
//    different address expressions and keep the plain symbol at the fourth:
//      fn_8001F0F8(m0, m1, lbl_802955C8);
//      fn_8001F0F8(m3, m0, *(f32 *)((char *)&lbl_802955C4 + 4));
//      fn_8001F0F8(m3, k2, *(f32 *)((char *)&lbl_802955C0 + 8));
//      fn_8001F0F8(m0, k2, lbl_802955C8);
//    The aliases resolve to the same address (verified in .rela.text:
//    `lbl_802955C4 + 4` and `lbl_802955C0 + 8`), so the link is byte-identical
//    and the masked score cannot be fooled. Swept all 81 combinations over
//    {plain, C4+4, C0+8}: the six winners are exactly the ones with three
//    distinct webs in sites 1-3 and the plain symbol at site 4 (1864B/173
//    diffs); every other pattern is 1856-1860B. A 4-distinct-web variant and
//    the `lbl_80295508 + 0xC0` style alias (same 64K page, so the `lis` is
//    shared) were also tried and are much worse (1892B/456 diffs).
//
// 2. THE SEVEN FRAME FLOATS MUST **NOT** BE `volatile` (§6fa). The struct is
//    already address-taken (the colour pack takes `&fr.col`), so the stores are
//    un-DCE-able without the qualifier — and with it, `sched` treats each store
//    as unschedulable and sinks the four `lis` page anchors *between* them.
//    Plain `*(f32 *)&fr.aXX = ...;` emits want's [4 lfs][cmpwi][stfs run].
//    Worth +3.6 points on its own. (A `"memory"` fence either side of the run
//    is inert, and `"(f32 *)"` with an extra `"m"(fr.a30)` pin is much worse.)
//
// 3. THE COLOUR PACK (0x80073070-0x80073084) needs 3 emitted asm statements.
//    want's `clrlwi/slwi/rlwimi/rlwimi/ori` masked-insert chain is a §6x-89
//    "want keeps a provably-dead insn" case — cc1 3.9.3 folds it to
//    `rlwinm/slwi/or/ori` (4 insns, one word short). Reproduced with
//    clrlwi + 2 rlwimi on a masked `a` and a separate accumulator `d`. The
//    pure-C, `"+r"`-barrier, union (incl. `struct {u32 hi:8;m1:8;m2:8;lo:8;}`)
//    and reordered-union spellings all fold.
//
// INLINE-ASM ACCOUNTING (§4g / §6af-180): 3 EMITTED instructions of 466 =
// 0.64% — the clrlwi and the two rlwimi of the colour pack, all three of which
// are the exact instructions retail emits. The file also carries
// `register f32 k2 __asm__("fr28");`, a register-variable *attribute* which
// emits no code; it is kept only because splitting k2 out of the shared `f32`
// declaration list is worth 2 diffs as a §6ec declaration-order effect (the
// pin itself does not bind — see the rejected list).
//
// RESIDUAL — 4 local clusters, all identified:
//   (a) 6 words, the int->double magic. want materialises the high half in the
//       ENTRY block (`lis r29,0x4330` at 0x80072E7C, live across both calls,
//       hence a callee-saved reg) and reloads the pool double early
//       (`lis r9,-0x7fd7; lfd f31,0x5590(r9)`); cc1 emits both at the use
//       (`lis r0,0x4330`, `lis r11,0`, `lfd f13,0(r11)`). lbl_80295590 IS the
//       real 2^52 magic in .rodata2, so the §6j-1 manual union dance looks
//       right — but it MEASURES WORSE (58.4-59.3% in all four spellings:
//       function-local, volatile, struct-member at +0x70 replacing cc1's temp,
//       and the volatile-lvalue variant), because removing cc1's DFmode temp
//       moves the frame. The 0x4330 word is `const0_df_operand` inside the
//       expander, so no source expression can change its liveness.
//   (b) 2 words, one `stw` one slot off at 0x80072F5C (the q[]/q1[] init tail).
//   (c) ~11 words, the FIRST `fn_8001F0F8` window at 0x800733A4-0x800733D8:
//       want keeps 0.5 in the f3 arg slot and computes the two `addi` bases
//       AFTER the call; GOT still hoists 0.5 into f29 there and emits the
//       addi pair before the bl.
//   (d) ~7 words, the 0.5 load at sites 2/3 comes out as `lfs f3, 4(r9)`
//       (shared anchor + displacement) where want has `lfs f3, 0x55c8(r26)`
//       (a pure @l reference).
//   (c)+(d) are one FPR/GPR pool rotation in the 88-instruction tail: want has
//   k0@f27, k2@f28, k1@f31, the 0.5 in the f3 scratch and the 0.75 loop
//   accumulator in f30; cc1's pool comes out rotated (k2@f31, k1@f28, 0.5 in
//   f29/f30). The store runs and the loop structure all match.
//
// MEASURED AND REJECTED (do not re-grind):
//   * 22-flag sweep on the FINAL body (§6bx: flags must be re-measored after
//     the semantic round) — every one neutral or worse. -fno-schedule-insns
//     48.9%, -fno-schedule-insns2 46.8%, -Os 5.2%, -O1 23.2%, -O3 neutral,
//     -mcpu=603 47.6%, -fno-expensive-optimizations 1.5%, -fno-strength-reduce
//     53.0%, -fno-branch-count-reg 52.2%, and -fno-gcse/-fno-sched-spec/
//     -fno-sched-interblock/-fno-thread-jumps/-fconserve-space/
//     -foptimize-register-move/-fbranch-probabilities all exactly neutral.
//     (-fno-rerun-cse-after-loop, -fno-crossjumping, -fno-reorder-blocks,
//     -fno-if-conversion, -fno-tree-pre, -fno-tree-fre do not exist in cc1.)
//   * FULL 7! = 5040 permutation search on the seven frame stores: a 4216-way
//     plateau at 168 diffs, and the plain ascending source order is already one
//     of the optima. Recipe 280's plateau walk is EXHAUSTED here — the store
//     run is no longer the residual.
//   * 6 permutations of `register f32 kX __asm__("frN")` on k0/k1/k2 and all
//     6 declaration-order permutations of {sc,k0,k1}: inert (the pins do not
//     bind a derived web, §6cw/§7a-137). Any k0 pin costs 21-22%.
//   * "m"(pad) on a `char pad[N]` array materialises the array's ADDRESS
//     (`addi rX,r1,K; stw rX,off(r1)`) = 2 wasted insns; scalar s32 pads emit
//     nothing but their total is quantised to 8 with a fixed +4 phase, so
//     `stmw` can only land at 0x6C/0x74/0x7C/0x84/0x8C — want's 0x78 is
//     unreachable by that route. The frame-template struct is what works.
//   * int->double: `(f32)(f64)ret` gives ONE fsub + a private pool (correct);
//     `(f32)((f64)ret - lbl_80295590)` gives TWO fsubs (3.0%);
//     `volatile` on the cvt union moves its slot to 0x18 and costs the frame.
//   * 13-argument varargs call fn_8001F2D8(6,9,1,0xD,1,0xE,1,0xF,1,0x10,1,0xB,1)
//     with `(s32, ...)` is REQUIRED (it creates the 5-slot outgoing-arg area),
//     and the per-site 3-arg `void fn_8001F0F8(f32,f32,f32)` is required (a real
//     leading s32 emits a spurious `li r3,0x80`).
//   * the `if/else` arms are NOT duplicates: the taken arm passes arg7 = 2 (r10)
//     and the skipped arm 0.
s32 fn_80016EC4(s32);
s32 fn_80016EAC(s32);
void set_blend_mode(s32, u32, s32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void fn_8001F2D8(s32, ...);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E5DC(u32, s32, s32, s32, s32);
void fn_8001E66C(s32, u32 *);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32, s32, s32);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F200(f32, f32);
void fn_8001F0F4(void);

extern const double lbl_80295590;
extern const f32 lbl_80295598;
extern const f32 lbl_8029559C;
extern const f32 lbl_802955A0;
extern const f32 lbl_802955A4;
extern const f32 lbl_802955A8;
extern const f32 lbl_802955AC;
extern const f32 lbl_802955B0;
extern const f32 lbl_802955B4;
extern const f32 lbl_802955B8;
extern const f32 lbl_802955BC;
extern const f32 lbl_802955C0;
extern const f32 lbl_802955C4;
extern const f32 lbl_802955C8;
extern bool lbl_80301650;
extern const f32 lbl_80301654;
extern const f32 lbl_80301658;
extern f32 lbl_80301640[4];
extern f32 lbl_803773E0[4];
extern f32 lbl_803773F0[4];
extern f32 lbl_80377400[8];

void fn_80072E4C(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    struct { f32 a20, a24, a28, a2C, a30, a34, a38;
             s32 g4; s32 col; char t[0x24]; } fr;
    f32 v, t, u, w, c10, c11, sc, k0, k1, k3, k4, m0, m1, m2, m3;
    register f32 k2 __asm__("fr28");
    f32 *p0, *p1, *d0, *d1, *q0, *q1;
    s32 i, n;

    fn_80016EC4(arg0);
    fn_80016EAC(arg1);
    v = (f32)(f64)fn_80016EC4(arg1);
    if (arg1 == 0) {
        v = v * lbl_80295598;
    }
    *(f32 *)&fr.a20 = lbl_802955A0;
    *(f32 *)&fr.a24 = lbl_802955A4;
    *(f32 *)&fr.a28 = lbl_802955A8;
    *(f32 *)&fr.a2C = lbl_802955AC;
    *(f32 *)&fr.a30 = lbl_802955A8;
    *(f32 *)&fr.a34 = lbl_802955A4;
    *(f32 *)&fr.a38 = lbl_802955A0;
    if (lbl_80301650 == 0) {
        f32 *q;
        t = ((lbl_802955AC - lbl_802955A8) * lbl_80295598) /
            (lbl_802955A8 + lbl_802955AC);
        lbl_80301650 = 1;
        u = t + lbl_802955B4;
        w = lbl_802955B0 - t;
        q = lbl_803773E0;
        q[1] = -u;
        q[2] = u;
        q[3] = w;
        lbl_803773E0[0] = -w;
    }
    p0 = lbl_803773E0;
    p1 = lbl_80301640;
    if (arg2 == 6) {
        p0 = lbl_80301640;
        p1 = lbl_803773E0;
    }
    set_blend_mode(0, 0, 0);
    fn_8001EEE0(4, 0, 4, 0, 0);
    fn_8001F2D8(6, 9, 1, 0xD, 1, 0xE, 1, 0xF, 1, 0x10, 1, 0xB, 1);
    fn_8001E248(4, 1, 0, 0, 0, 0, 2);
    fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
    fn_8001E5DC(2, 0xC, 0x1C, 0xC, 0x1C);
    {
        s32 a = (s32)(farg0 * lbl_802955B8);
        s32 d;
        __asm__("clrlwi %0,%0,0x18" : "+r"(a));
        d = (a & 0xFF) << 24;
        __asm__("rlwimi %0,%1,0x10,8,0xf" : "+r"(d) : "r"(a));
        __asm__("rlwimi %0,%1,8,0x10,0x17" : "+r"(d) : "r"(a));
        d |= 0xFF;
        fr.col = d;
    }
    fn_8001E66C(0, &fr.col);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001E6F0(1, 1, 5, 0, 0x7D);
    fn_8001E6F0(2, 1, 6, 0, 0x7D);
    fn_8001E6F0(3, 1, 7, 0, 0x7D);
    fn_8001E2FC(0, 0, 0, 4, 1, 0, 4);
    fn_8001E2FC(2, 2, 0, 4, 3, 0, 4);
    fn_8001E4E8(0, 0xF, 0xE, 8, 0xF, 0, 0, 0, 1, 1);
    fn_8001E4E8(1, 0xF, 0xE, 8, 2, 0, 0, 0, 1, 1);
    fn_8001E4E8(2, 0xF, 0xE, 8, 2, 0, 0, 0, 1, 1);
    if (farg1 != lbl_802955BC) {
        fn_8001E4E8(3, 0xF, 0xE, 8, 2, 0, 0, 2, 1, 0);
    } else {
        fn_8001E4E8(3, 0xF, 0xE, 8, 2, 0, 0, 0, 1, 0);
    }
    fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
    fn_8001E3CC(1, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
    fn_8001E3CC(2, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
    fn_8001E3CC(3, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
    k0 = lbl_802955BC;
    sc = lbl_8029559C / v;
    n = 4;
    k2 = lbl_802955C4;
    k1 = lbl_802955C0;
    d0 = lbl_803773F0;
    d1 = lbl_80377400;
    i = 0;
    do {
        d0[i] = sc * (p0[i] + lbl_80301654);
        d1[i] = sc * (p1[i] + lbl_80301658);
        i += 1;
    } while (i != n);
    fn_8001F0A0(0x80, 0, 4);
    m0 = k0;
    m1 = k0;
    q0 = lbl_803773F0;
    q1 = lbl_80377400;
    fn_8001F0F8(m0, m1, lbl_802955C8);
    fn_8001F1D4(-1);
    m3 = k0 + k1;
    m2 = k0;
    fn_8001F200(lbl_803773F0[0] + m2, lbl_80377400[0] + m2);
    fn_8001F200(q0[1] + m2, q1[1] + m2);
    fn_8001F200(q0[2] + m2, q1[2] + m2);
    fn_8001F200(q0[3] + m2, q1[3] + m2);
    fn_8001F0F8(m3, m0, *(f32 *)((char *)&lbl_802955C4 + 4));
    fn_8001F1D4(-1);
    m1 = lbl_8029559C;
    fn_8001F200(lbl_803773F0[0] + m1, lbl_80377400[0] + m2);
    fn_8001F200(q0[1] + m1, q1[1] + m2);
    fn_8001F200(q0[2] + m1, q1[2] + m2);
    fn_8001F200(q0[3] + m1, q1[3] + m2);
    fn_8001F0F8(m3, k2, *(f32 *)((char *)&lbl_802955C0 + 8));
    fn_8001F1D4(-1);
    fn_8001F200(lbl_803773F0[0] + m1, lbl_80377400[0] + m1);
    fn_8001F200(q0[1] + m1, q1[1] + m1);
    fn_8001F200(q0[2] + m1, q1[2] + m1);
    fn_8001F200(q0[3] + m1, q1[3] + m1);
    fn_8001F0F8(m0, k2, lbl_802955C8);
    fn_8001F1D4(-1);
    fn_8001F200(lbl_803773F0[0] + m2, lbl_80377400[0] + m1);
    fn_8001F200(q0[1] + m2, q1[1] + m1);
    fn_8001F200(q0[2] + m2, q1[2] + m1);
    fn_8001F200(q0[3] + m2, q1[3] + m1);
    fn_8001F0F4();
}
