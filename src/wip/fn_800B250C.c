// WIP DRAFT (non-matching) — C body rebuilt from the DOL disassembly 2026-09-26
// family=m2c range=0x800B250C-0x800B2748 size=572B
// INERT: not registered in splits.txt/configure.py — never compiled as part of
// the DOL, never counted in objdiff progress. activate via tools/wip.py.
//
// extra_cflags: -mps-float
//
// ---------------------------------------------------------------------------
// VERDICT 2026-09-26: DIFF, 6.1% masked (7/115 aligned words), got 460B vs
// retail 572B. Frame size and every r1 slot offset now MATCH (see below); the
// residual is the paired-single prologue and the case-2 matrix block. See
// "PARK" at the bottom for the full residual analysis. NOT promotable.
// ---------------------------------------------------------------------------
//
// Retail shape (hand-checked; the paired-single field layouts used here were
// re-derived with a controlled compiler probe and match the PS disassembler:
// an earlier field reading made the whole pair prologue look live; it does
// not -- see the PARK note, the prologue ops really do read uninitialised
// registers).
//
//   Takes an object pointer and a 4-float point, returns a small integer.
//   Prologue loads two object pairs and the point's upper pair, reads the
//   integer selector at +0x70, sets up a common zero return, runs a short
//   dead pair-arithmetic prologue (two dead ops reading uninitialised
//   registers), spills three pair temporaries to the frame, derives a scalar
//   threshold, then dispatches on the selector with cases 0, 1, 2 and 4:
//   case 0 returns a float compare of the threshold against +0x78;
//   case 1 is six box compares (three upper-bound, three shared lower-bound)
//   returning 1; case 2 is two bounded-region calls wrapped around a pair
//   computation plus a matrix product (all eight matrix pair ops are dead),
//   two compares, then a backward goto into case 1's tail; case 4 calls a
//   handle getter then an indirect call through a vtable slot with a
//   16-bit offset adjustment. Falls through to zero return.
//
// What this reconstruction gets RIGHT (verified byte-for-byte on those words):
//   * frame 0x50, callee-saved range and link-register slot (requires a 56-byte
//     frame struct -- the extra leading pad must be dropped because the float
//     flag set itself burns one 8-byte slot, so the struct has to start at
//     the first local slot with no pad);
//   * all seven paired stack slots at the expected frame offsets;
//   * the switch dispatch tree and the default zero return plus branch to epilogue;
//   * case 0's threshold compare value-return lowering -- proven against the
//     promoted byte-exact reference;
//   * case 1's six box compares: the upper trio and the lower trio each lower
//     to the expected condition-merge plus branch shape, exactly as in the
//     original (negating the upper trio gives the wrong merge);
//   * the shared-tail shape: the tail lives inside case 1 and case 2 reaches
//     it with a backward goto, which is the only way the original block order
//     can come out;
//   * case 4's load / halfword-load / indirect-call sequence.
#include "types.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSV;

typedef struct {
    s32 i00;
    s32 i04;
    __ps_t p08;
    __ps_t p10;
    __ps_t p18;
    __ps_t p20;
    __ps_t p28;
    __ps_t p30;
    __ps_t p38;
    __ps_t p40;
    __ps_t p48;
    __ps_t p50;
    s32 i58;
    s32 i5C;
    s32 i60;
    s32 i64;
    s32 i68;
    s32 i6C;
    s32 i70;
    s32 i74;
    f32 f78;
    s32 i7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    f32 f98;
    f32 f9C;
} TestObj;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Pt4;

/* 56 bytes: retail's seven paired slots live at r1+0x08 .. r1+0x38 and the
 * saved-register block starts at r1+0x40. Do NOT add a leading pad: under
 * -mps-float cc1 already burns one 8-byte slot below the struct, and a pad
 * would push every slot up by 8 (frame 0x58, everything misaligned). */
typedef struct {
    PSV q08;
    PSV q10;
    PSV q18;
    PSV q20;
    PSV q28;
    PSV q30;
    PSV q38;
} Frame;

extern char lbl_802987BC[];

void fn_800079D8(s32 out, void *bounds);
void *fn_800582B8(s32 h);

s32 fn_800B250C(TestObj *self, Pt4 *pt) {
    Frame fr;
    __ps_t pa;
    __ps_t pb;
    __ps_t pz;
    __ps_t pd;
    f32 t0;
    f32 t1;
    f32 t2;
    s32 v;

    pa = self->p10;
    pz = *(__ps_t *)lbl_802987BC;
    pb = *(__ps_t *)((char *)pt + 8);
    v = self->i70;
    pd = __builtin_ps_sub(pa, pb);
    pd = *(__ps_t *)pt;
    fr.q10.ps = pb;
    pb = __builtin_ps_mul(pd, pb);
    pa = self->p08;
    pz = __builtin_ps_merge00(pz, pb);
    pd = __builtin_ps_sub(pa, pd);
    fr.q08.ps = pd;
    pd = __builtin_ps_madd(pb, pd, pd);
    pd = __builtin_ps_sum0(pd, pd, pd);
    fr.q38.ps = pd;
    t0 = fr.q38.flt.hi;
    switch (v) {
    case 0:
        return t0 <= self->f78;
    case 1:
        t0 = pt->x;
        if (!(t0 >= self->f80)) {
            return 0;
        }
        t1 = pt->y;
        if (!(t1 >= self->f84)) {
            return 0;
        }
        t2 = pt->z;
        if (!(t2 >= self->f88)) {
            return 0;
        }
    tail:
        if (!(t0 <= self->f90)) {
            return 0;
        }
        if (!(t1 <= self->f94)) {
            return 0;
        }
        if (!(t2 <= self->f98)) {
            return 0;
        }
        return 1;
    case 2:
        fn_800079D8((s32)&fr.q28, (char *)self + 0x80);
        fr.q20.ps = __builtin_ps_sub(fr.q30.ps, *(__ps_t *)((char *)pt + 8));
        fr.q30.ps = fr.q20.ps;
        fr.q18.ps = self->p48;
        fr.q28.ps = self->p48;
        fn_800079D8((s32)&fr.q28, (char *)self + 0x80);
        fr.q18.ps = __builtin_ps_add(fr.q28.ps, fr.q18.ps);
        t0 = fr.q18.flt.hi;
        if (!(t0 >= self->f80)) {
            return 0;
        }
        t1 = fr.q18.flt.lo;
        if (!(t1 >= self->f84)) {
            return 0;
        }
        t2 = fr.q20.flt.hi;
        goto tail;
    case 4: {
        void *h = fn_800582B8(self->i7C);
        void *vt = *(void **)((char *)h + 0xC);
        return ((s32 (*)(void *, Pt4 *, f32 *)) * (s32 *)((char *)vt + 0x9C))(
            (char *)h + *(s16 *)((char *)vt + 0x98), pt, (f32 *)&fr.q18);
    }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// RE-TRIAGED 2026-10-19: sweep still DIFF — PS prologue + case-2 matrix
// wall stands. Parked as-is.
// PARK 2026-09-26 — DIFF 6.1% (7/115), got 460B vs retail 572B. Not promotable.
//
// Two independent, structural blockers:
//
// (1) THE PAIR PROLOGUE IS 8 WORDS SHORT AND IS NOT REACHABLE FROM C.
//     The original prologue is 27 words; this build emits 19, so every later
//     word is index-shifted and only the first 7 words can ever match. The
//     eight missing words are the constant page setup, the zero-pair load,
//     the zero return (emitted, just elsewhere), and two dead pair-arithmetic
//     ops.
//     The last two are dead in the original AND they read uninitialised
//     registers -- under the verified field layout one takes its subtractend
//     from a register nothing has written yet, and the other takes one of
//     its sources likewise. A C expression that reads uninitialised storage
//     is undefined, so no C source -- with or without volatile / barriers /
//     register pins -- can be written that both computes them and lets them
//     die: the compiler deletes both (verified: a barrier between the two
//     assignments changes neither the score nor a single byte, and a volatile
//     sink would add a store the original does not have). The original stream
//     is the signature of a source whose dead-code elimination this compiler
//     cannot reproduce; the version theory is excluded because this IS the
//     game compiler for pair ops.
//     => Re-open only if a source construct is found that makes the compiler
//        emit an operation whose operands are never defined.
//
// (2) CASE 2'S MATRIX BLOCK IS EIGHT DEAD PAIR OPS: several multiply-accumulate
//     ops each with a destination the next op overwrites, plus the pair op
//     they chain from. Adding them to the C (measured) costs 8 bytes of frame
//     -- the values then live across the two bounded-region calls and the
//     compiler gives them slots, frame 0x58 instead of 0x50, which misaligns
//     every stack offset in the function. Frame correctness was chosen over
//     the 8 dead words. Note also that all eight accumulate into registers
//     whose results are never stored, so the whole block is semantically empty;
//     only the pair difference stored to the frame pair slots and the pair add
//     after the second call are real, and both are reproduced.
//
// Two smaller, non-blocking differences (documented so they are not re-tried):
//   * the two prologue parameter-home copies: the original emits them in
//     descending register order; this compiler always emits them ascending
//     and no source statement order changes it (measured with all three
//     orderings of the first three statements). The register homes are right;
//     only the emission order differs.
//   * case 1 re-materialises the zero return; this build shares it with the
//     pre-switch zero. Also blocked by (1): case 1 cannot be aligned
//     until the prologue length matches, so neither difference is worth
//     chasing on its own.
// ---------------------------------------------------------------------------
