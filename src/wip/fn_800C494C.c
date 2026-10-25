// WIP DRAFT (non-matching) — hand-rebuilt from DOL disassembly at 0x800C494C
// family=m2c range=0x800C494C-0x800C4B08 size=444B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py. Not counted in objdiff progress.
//
// PARKED 2026-10-02 (w75/0x800C494C): 48.7% (was 5.4%). THE BIG STRUCTURAL
// DEFECT IS FIXED — see "FIXED" below; what is left is FPR colouring plus two
// emitted-shape residuals that no plain-C spelling tried produces.
//
// FIXED (this round) -- the 8 stack slots are NOT a volatile pair array.
// The original store-plus-reload-plus-copy triple is the compiler lowering of
// a scalar lane extraction from a non-volatile pair local: stage the pair
// expr into a local, reload lane 0 as a scalar, then copy into the value
// register (the compiler will not coalesce this copy). Reading the lane out
// of a volatile object gives only store plus reload with no copy. The copy is
// the tell. Six slots need it (two candidates plus four denominators); the two
// dead slots are plain volatile pair stores. This corrects the previous note's
// claim that a volatile union was required, and the recipe note about the
// coalesced reload -- the fix is to drop the volatile on the container, not
// on the lane. Hundreds of such sites exist in the image; the same swap
// applies there.
//
// RESIDUAL (all measured, none reproduced by any plain-C spelling tried):
//   1. Register copy of the temp into the multiply operand register. A float
//      pin for the copy destination does not pin a copy destination (pins only
//      bind when the variable is fed by a load): the compiler computes the pair
//      difference into the pinned register and copies the wrong way, i.e.
//      exactly inverted. Same pin failure as the previous round's item 1.
//   2. Difference-operand colouring: the original loads the two inputs in one
//      register order and subtracts; this build swaps them. Pinning either
//      variable inserts a copy instead, so the pair cannot be pinned as-is.
//   3. Scheduler-killing flags both score far worse than default; the original
//      constant load / temp store / temp copy positions cannot be reproduced
//      from any statement order tried.
//   4. The compiler cross-jumps cases 1 and 3 (identical bodies, shared
//      copy-plus-divide tail) where the original keeps both tails inline --
//      2 words short overall.
#include "types.h"
#include "structs.h"

extern __ps_t lbl_80298F18; /* {0.0f, 0.0f} */
extern f32 lbl_8029910C;     /* 0.01f */
extern f32 lbl_80299110;     /* 0.1f  */

typedef union {
    __ps_t p;
    struct { f32 hi, lo; } f;
} PV;

typedef struct {
    __ps_t a0; /* 0x00 */
    __ps_t a1; /* 0x08 */
    __ps_t a2; /* 0x10 */
    __ps_t a3; /* 0x18 */
} VA;

typedef struct {
    char _p0[0x30];
    __ps_t n;   /* 0x30 */
    __ps_t g38; /* 0x38 */
    char _p1[0x20];
    __ps_t w0;  /* 0x60 */
    __ps_t v0;  /* 0x68 */
    __ps_t w1;  /* 0x70 */
    __ps_t v1;  /* 0x78 */
    f32 f80;    /* 0x80 */
    f32 f84;    /* 0x84 */
} PA;

/* r3 is an unused leading arg: both callers (fn_800C4B08@0x800C4CD0 and
   fn_800C4E78@0x800C5034) set r3/r4/r5 = (ctx, arg0, arg1) before the bl.
   Shape: 4-candidate "barycentric coord on a 2-triangle quad" selector.
     t  = arg0[0x08] - arg1[0x38]              (PS pair, sub)
     d  = arg0[0x00] - arg1[0x30]              (PS pair, sub)
     K  = lbl_80298F18 = {0.0f, 0.0f}
     d0 = sum0( madd(d, w0, merge00(t*v0, K)) )
     d1 = sum0( madd(d, w1, merge00(t*v1, K)) )
     candidates in order d0, f80-d0, d1, f84-d1 -> min + index 0..3
     denominator: idx0/1 use (w0,v0); idx2/3 use (w1,v1):
       den = sum0( madd(wN, arg0[0x10], merge00(vN * arg0[0x18], K)) )
     result = (idx odd ? -best : best) / den
     guard: if (best < lbl_8029910C) return lbl_80299110
   Frame: 0x48 = 8 eight-byte slots. 0x08/0x10 are the volatile `d`/`t`
   stores; the other six are the lane-extraction homes of c0,c1,dn0..dn3. */
f32 fn_800C494C(s32 unused, VA *arg0, PA *arg1) {
    volatile __ps_t vd;
    volatile __ps_t vt;
    PV c0;
    PV c1;
    PV dn0;
    PV dn1;
    PV dn2;
    PV dn3;
    register __ps_t sp __asm__("fr6");
    register __ps_t k __asm__("fr7");
    register f32 best __asm__("fr10");
    register f32 cur __asm__("fr1");
    register f32 f80v __asm__("fr11");
    register __ps_t t __asm__("fr0");
    __ps_t d;
    __ps_t s;
    __ps_t q;
    __ps_t nn;
    register __ps_t w0 __asm__("fr4");
    register __ps_t v0 __asm__("fr5");
    register __ps_t w1 __asm__("fr8");
    register __ps_t v1 __asm__("fr9");
    s32 idx;

    idx = 0;
    k = lbl_80298F18;
    q = arg1->g38;
    t = arg0->a1;
    t = __builtin_ps_sub(t, q);
    vt = t;
    sp = t;
    nn = arg1->n;
    d = arg0->a0;
    d = __builtin_ps_sub(d, nn);
    vd = d;
    w0 = arg1->w0;
    v0 = arg1->v0;
    f80v = arg1->f80;
    s = __builtin_ps_mul(sp, v0);
    s = __builtin_ps_merge00(s, k);
    s = __builtin_ps_madd(d, w0, s);
    c0.p = __builtin_ps_sum0(s, s, s);
    best = c0.f.hi;
    cur = f80v - best;
    if (cur < best) {
        best = cur;
        idx = 1;
    }
    w1 = arg1->w1;
    v1 = arg1->v1;
    s = __builtin_ps_mul(sp, v1);
    s = __builtin_ps_merge00(s, k);
    s = __builtin_ps_madd(d, w1, s);
    c1.p = __builtin_ps_sum0(s, s, s);
    cur = c1.f.hi;
    if (cur < best) {
        best = cur;
        idx = 2;
    }
    cur = arg1->f84 - cur;
    if (cur < best) {
        best = cur;
        idx = 3;
    }
    if (best < lbl_8029910C) {
        return lbl_80299110;
    }
    switch (idx) {
    case 0:
        s = __builtin_ps_mul(v0, arg0->a3);
        s = __builtin_ps_merge00(s, k);
        s = __builtin_ps_madd(w0, arg0->a2, s);
        dn0.p = __builtin_ps_sum0(s, s, s);
        { register f32 den __asm__("fr0"); den = dn0.f.hi; return best / den; }
    case 1:
        s = __builtin_ps_mul(v0, arg0->a3);
        s = __builtin_ps_merge00(s, k);
        s = __builtin_ps_madd(w0, arg0->a2, s);
        dn1.p = __builtin_ps_sum0(s, s, s);
        { register f32 nb __asm__("fr12"); register f32 den __asm__("fr13");
          nb = -best; den = dn1.f.hi; return nb / den; }
    case 2:
        s = __builtin_ps_mul(v1, arg0->a3);
        s = __builtin_ps_merge00(s, k);
        s = __builtin_ps_madd(w1, arg0->a2, s);
        dn2.p = __builtin_ps_sum0(s, s, s);
        { register f32 den __asm__("fr0"); den = dn2.f.hi; return best / den; }
    case 3:
        s = __builtin_ps_mul(v1, arg0->a3);
        s = __builtin_ps_merge00(s, k);
        s = __builtin_ps_madd(w1, arg0->a2, s);
        dn3.p = __builtin_ps_sum0(s, s, s);
        { register f32 nb __asm__("fr12"); register f32 den __asm__("fr13");
          nb = -best; den = dn3.f.hi; return nb / den; }
    }
    return cur;
}