// WIP DRAFT (non-matching) — C-only matrix-multiply reconstruction
// family=m2c range=0x8019F090-0x8019F830 size=1952B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// ============================ PARKED (2026-10-04) =============
// BEST MEASURED: 1952B object == want size exactly, masked 39.75%
// (`tools/test_wip_drafts.py --addr 0x8019F090` -> DIFF 39.75%, 294/488 words;
// baseline at the start was DIFF 13.52%, 422/488). Opcode-level
// diff is 89 instructions (see tools/want_got.py + a PS-aware got dump);
// 20 of the 32 dot products are now byte-identical and 6 more differ by a
// single load position. Relocations verified by hand: both `bl`s ->
// fn_80003F54/fn_80003E0C, both `lis`+displacement pairs ->
// lbl_802AAFC8 / lbl_802AAFCC, both `bdnz` self-targeting.
//
// THREE THINGS CHANGED (each verified by measurement):
//
//  1. THE `fr9` PIN IS NOT NEEDED — the previous note's claim that a plain
//     local loses the shared `left[0]` load is WRONG. `f32 l0;` (no
//     `__asm__`) still emits ONE `lfs` for row 0's `M[0]`, shared by all four
//     column products, and the object is still exactly 1952B. What the pin
//     actually bought was a chosen FPR NUMBER, not the hoisted load.
//  2. EVERY TERM MUST BE SPELLED `(M) * (N)`. The parked body had the first
//     term of the non-hoisted rows as `(N)[C] * (M)[R]`; want emits the fma
//     multiplicands in (M,N) order for ALL four terms (`fmadds f11,f11,f10,f12`
//     = M1 * f10 + acc). Flipping it fixed the N1/M1 load order and the
//     acc1/fmadds operand pairing in 24 products: 422 -> 400 diffs.
//  3. **`-fno-schedule-insns` MUST BE DROPPED.** The want's 32 dot products
//     are SCHEDULER output: `lfs N3` sits between the `fmuls` and the first
//     `fmadds`, and `lfs N4`/`lfs M4` sit before the second `fmadds`. No
//     un-scheduled RTL order produces that. With the flag off, ngccc's
//     allocator picks exactly want's FPR assignment on its own — f0 to the
//     N operand of the `fmuls` seed, f12 to its M, f11 to M[0]/acc1, f10 to
//     N[0], f9 to N[8], f13 to M[2]/acc2, re-using f12/f0 for the last term
//     (and, in row 0 product 3, putting acc1 in f9 because the hoisted l0
//     register dies there). Cost: the prologue rotates (below). Net
//     400 -> 295 diffs. `-fschedule-insns2` must stay ON
//     (`-fno-schedule-insns2` = 442); ~20 other -f flags measured as exact
//     no-ops on this body (see AGENTS-recipes §4r).
//
// STILL EXACT: frame 0xa0, `stfd f31`/`stmw r30`/`stw r0`, epilogue, the 16
// identity stores in want's order off r31, the r30/r31 pointer roles, both
// empty loops (`li r0,4`/`mtctr r0`/`bdnz <self>`, self-relative in both),
// rot[16] @0x08 and out[16] @0x48, both `bl` sites, all 16 psq_l/psq_st
// copy-backs, the shared `M[0]` load, and the 1-fmuls+3-fmadds contraction
// with want's term order (terms 1,0,2,3).
//
// REMAINING BLOCKER #1 — the missing second pointer advance. Want computes two
// address derivations from the same base plus offset 0x78: the first (at
// 0x8019F0C0) feeds the left matrix between the identity stores, and the
// second (at 0x8019F110) re-derives the base right before the first call.
// C cannot express this: ngccc's CSE normalises `base + 0x1E` to the value
// already sitting in a register. Measured (all `-mps-float`, no pins):
//   `base = base + 0x1E;` in place -> 1592B: BOTH addis appear, but CSE then
//       unifies the two address pseudos, so all four M-loads of every row
//       hoist out of its 4 products (-90 words) and the store base / matrix
//       pointer swap to r30/r31.
//   `arg0 = arg0 + 0x1E;` (parameter) -> 1592B, same collapse.
//   a third pointer variable -> 1588B / 1772B, r31 spills to r9.
//   `base = left;` (what is in this file) -> 1952B, NO hoisting, correct
//       pointer roles, but emits `mr r31,r30` in the second half instead of
//       the second addi, so the whole first half is one word short and the
//       masked word-diff counts every word from 0x8019F110..0x8019F4A0 as
//       different. That single missing word is worth ~229 of the 294.
// One-sided trade: keep the load structure, lose one word. With the addi
// present the same body scores ~81%, so this is where the next session
// should start (a way to keep two live equal-valued address pseudos).
//
// REMAINING BLOCKER #2 — 89 instructions of ngccc allocator/scheduler:
//   * prologue: want interleaves two page materializations with the base-pointer
//     copy, two float loads, the counter setup and its move to the count
//     register, three identity-column stores (offsets 0x78 through 0xb4), the
//     second pointer derivation and the float-argument copy, in that order;
//     got hoists `stfs 0xa0`+`stfs 0xac` to the top, materialises the second
//     page in r11 (want reuses r9 — its 2nd `lis` sits after the 1st `lfs`,
//     so r9 is dead), and keeps `li r0,4`/`mtctr r0` in the prologue where
//     want's scheduler sinks them into the first product. 13 instructions.
//   * row 3 (M offset 0x30) products 1-3, both halves (~34 words): want
//     rotates to N2=f13/M2=f0/M1=f12/N4=f11, ours keeps the f0/f12/f11 set
//     it used for product 0 (and reaches for f8 in product 3) — the
//     allocator's free-list state is one product out of step.
//   * the psq copy-back, both halves (10 words): want alternates
//     `psq_l f12`/`psq_l f0`, ours uses f0 for all four loads, and want's
//     first psq_l sits between the last two fmadds.
//   * 3 one-position load swaps per half (6 words): `lfs f12,8(rM)` in
//     out[5][3], `lfs f13,0x18(rM)` in out[8][2], `lfs f13,0x28(rM)` in
//     out[11][3] (M[2]/M[3] of the row).
// AGENTS-recipes §6bu2 records the same wall on fn_800A7B40 (same code
// shape): "the remaining 33 words were a pure sched2 look-ahead wall and
// resisted everything" — 30+ flags, load staging, right-association,
// accumulator temps, volatile aliases, 2D vs pointer access, decl order.
// Also measured here: `((M)+(R))[k]` pointer-base spelling produces a
// BYTE-IDENTICAL object (front end folds it back).
//
// NEGATIVE RESULTS (do not re-try blind):
//  * `register f32 l0 __asm__("fr9")` — only picks an FPR number, and costs
//    a word while the flag is on; not allowed here anyway.
//  * volatile on either matrix pointer: kills the hoisting (recovers the 90
//    words) but pins the loads to un-scheduled RTL order -> 1772B, or 1952B
//    at 424 diffs with both pointers volatile. Far worse than 294.
//  * a dead `base = (f32 *)0;` to kill the CSE entry: 1952B but the store
//    base moves to r30 / matrix to r31 and r31 gets saved -> 343 diffs.
//  * `-fcse-skip-blocks` / `-fcse-follow-jumps` / `-fgcse` / `-fno-gcse`:
//    no effect on either behaviour. `-fno-cse` does not exist in ProDG cc1
//    (only `cc1 v2.0.1.76` accepts `-fcse-*`); no flag disables the load
//    CSE, which is what the want's per-row reloads prove was absent.
//  * unique temp names per site (`l0a`/`l0b`, recipes §7b-152) is worth 1
//    word (295 -> 294) and is kept: it also fixes row 0 product 3's acc1.
// =============================================================================


#include "types.h"

extern f32 lbl_802AAFC8;
extern f32 lbl_802AAFCC;
extern void *fn_80003F54(void *, f32);
extern void *fn_80003E0C(void *, f32);

typedef struct {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 f8;
    f32 f9;
    f32 f10;
    f32 f11;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
} Out;

/* row `R`, column `C` of out = row R of M dotted with column C of N.
   Term order and BOTH operand orders are load-bearing — see the park note. */
#define DOT4(D, I, M, N, R, C) \
    (D).I = (M)[(R)] * (N)[(C)] + (M)[(R) + 1] * (N)[(C) + 4] + \
        (M)[(R) + 2] * (N)[(C) + 8] + (M)[(R) + 3] * (N)[(C) + 12]

/* row 0 only: its first operand is hoisted into a local scalar so all four
   column products share one load (ngccc keeps it in a register). */
#define DOT4L(D, I, L0, M, N, R, C) \
    (D).I = (L0) * (N)[(C)] + (M)[(R) + 1] * (N)[(C) + 4] + \
        (M)[(R) + 2] * (N)[(C) + 8] + (M)[(R) + 3] * (N)[(C) + 12]

#define COPY_MATRIX(D, S) \
    do { \
        ((__ps_t *)(D))[0] = ((volatile __ps_t *)(S))[0]; \
        ((__ps_t *)(D))[1] = ((volatile __ps_t *)(S))[1]; \
        ((__ps_t *)(D))[2] = ((volatile __ps_t *)(S))[2]; \
        ((__ps_t *)(D))[3] = ((volatile __ps_t *)(S))[3]; \
        ((__ps_t *)(D))[4] = ((volatile __ps_t *)(S))[4]; \
        ((__ps_t *)(D))[5] = ((volatile __ps_t *)(S))[5]; \
        ((__ps_t *)(D))[6] = ((volatile __ps_t *)(S))[6]; \
        ((__ps_t *)(D))[7] = ((volatile __ps_t *)(S))[7]; \
    } while (0)

void fn_8019F090(f32 *arg0, f32 farg1, f32 farg2) {
    struct {
        f32 rot[16];
        Out out;
    } fr;
    f32 *base;
    f32 *left;
    f32 *nmat;
    f32 l0a;
    f32 l0b;
    s32 i;

    base = arg0;

    base[0x1E] = lbl_802AAFC8;
    left = base + 0x1E;
    base[0x2D] = lbl_802AAFC8;
    base[0x2C] = lbl_802AAFCC;
    base[0x1F] = lbl_802AAFCC;
    base[0x20] = lbl_802AAFCC;
    base[0x21] = lbl_802AAFCC;
    base[0x22] = lbl_802AAFCC;
    base[0x23] = lbl_802AAFC8;
    base[0x24] = lbl_802AAFCC;
    base[0x25] = lbl_802AAFCC;
    base[0x26] = lbl_802AAFCC;
    base[0x27] = lbl_802AAFCC;
    base[0x28] = lbl_802AAFC8;
    base[0x29] = lbl_802AAFCC;
    base[0x2A] = lbl_802AAFCC;
    base[0x2B] = lbl_802AAFCC;

    for (i = 0; i < 4; i++) {
    }

    nmat = fn_80003F54(fr.rot, farg1);

    l0a = left[0];
    DOT4L(fr.out, f0, l0a, left, nmat, 0, 0);
    DOT4L(fr.out, f1, l0a, left, nmat, 0, 1);
    DOT4L(fr.out, f2, l0a, left, nmat, 0, 2);
    DOT4L(fr.out, f3, l0a, left, nmat, 0, 3);
    DOT4(fr.out, f4, left, nmat, 4, 0);
    DOT4(fr.out, f5, left, nmat, 4, 1);
    DOT4(fr.out, f6, left, nmat, 4, 2);
    DOT4(fr.out, f7, left, nmat, 4, 3);
    DOT4(fr.out, f8, left, nmat, 8, 0);
    DOT4(fr.out, f9, left, nmat, 8, 1);
    DOT4(fr.out, f10, left, nmat, 8, 2);
    DOT4(fr.out, f11, left, nmat, 8, 3);
    DOT4(fr.out, f12, left, nmat, 12, 0);
    DOT4(fr.out, f13, left, nmat, 12, 1);
    DOT4(fr.out, f14, left, nmat, 12, 2);
    DOT4(fr.out, f15, left, nmat, 12, 3);
    COPY_MATRIX(left, &fr.out);

    for (i = 0; i < 4; i++) {
    }

    base = left;
    nmat = fn_80003E0C(fr.rot, farg2);

    l0b = base[0];
    DOT4L(fr.out, f0, l0b, base, nmat, 0, 0);
    DOT4L(fr.out, f1, l0b, base, nmat, 0, 1);
    DOT4L(fr.out, f2, l0b, base, nmat, 0, 2);
    DOT4L(fr.out, f3, l0b, base, nmat, 0, 3);
    DOT4(fr.out, f4, base, nmat, 4, 0);
    DOT4(fr.out, f5, base, nmat, 4, 1);
    DOT4(fr.out, f6, base, nmat, 4, 2);
    DOT4(fr.out, f7, base, nmat, 4, 3);
    DOT4(fr.out, f8, base, nmat, 8, 0);
    DOT4(fr.out, f9, base, nmat, 8, 1);
    DOT4(fr.out, f10, base, nmat, 8, 2);
    DOT4(fr.out, f11, base, nmat, 8, 3);
    DOT4(fr.out, f12, base, nmat, 12, 0);
    DOT4(fr.out, f13, base, nmat, 12, 1);
    DOT4(fr.out, f14, base, nmat, 12, 2);
    DOT4(fr.out, f15, base, nmat, 12, 3);
    COPY_MATRIX(base, &fr.out);
}
