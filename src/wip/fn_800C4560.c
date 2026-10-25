// WIP DRAFT (non-matching) — decompiled from the retail DOL.
// family=m2c range=0x800C4560-0x800C4734 size=468B
//
// PARKED at 96.58% (4 of 117 words; object size 468B == retail). Two
// independent 2-word residuals remain, both characterised and neither
// reachable from C under SN ProDG 3.9.3:
//
//  A. Path-A float clamp: retail pre-copies the THEN value of the max, tests
//     the two operands in (value, limit) order and takes the POSITIVE branch
//     over the else assignment. ProDG's float COND_EXPR expansion always
//     pre-copies the ELSE value, swaps the compare operands and emits the
//     inverted branch; the MAX_EXPR path that would produce retail's shape is
//     never built by this front end (no fmax/fmin builtin). 40+ probe bodies
//     were measured (both ternary arm orders, both if/else orders, empty then,
//     pre-assign + if, dest==tested, >=/<= variants, five max idioms, four
//     goto shapes, "+f" and empty asm barriers, five compiler versions, the
//     C++ frontend, -O1/-O3/-Os/-ffloat-store and six schedule flags). Every
//     one either pre-copies the else and inverts, or if-converts to
//     subtract+fsel. -O1 emits the positive-branch form but coalesces the load
//     into the argument register, losing the separate copy. The arms-swapped
//     ternary in the body (`limit > value ? limit : value`, same maximum) is
//     the best reachable state: both loads and both copies already sit in
//     retail's registers and only the mirrored compare/branch pair differs.
//
//  B. Loop-preheader page-anchor slot (a 1-instruction swap): the hoisted
//     page anchor for the 2^52 double is emitted one slot after the offset
//     computation instead of one slot before it. The anchor is a reload
//     pseudo, so sched2 cannot move it; the slot is decided by loop.c's
//     hoist append plus basic-block reorder. Fourteen schedule/optimisation
//     flags and six spellings of the offset computation were measured as
//     exact no-ops or regressions. The zone's siblings (src/fn_800C4734.c,
//     fn_800C47EC.c, fn_800C48A0.c) show the retail preheader shape, so it is
//     reproducible in principle but not from this body. A hand-written
//     int->double dance (real double extern plus a stack word pair) was
//     measured three ways (22.2% / 4.3% / 55.8%): it needs a seventh
//     callee-saved register, so the frame changes and the whole body slides.
//
// MEASURED LEVERS (on the 96.58% base): clamp arm order 96.6% (taken, was
// 94.9%); pre-assigned then-value with a <= test 93.2%; if/else both orders
// 94.9%; pre-assign + "+f" barrier 42.7% (fsel); empty asm barriers in either
// arm 93.2%/1.7%; goto forms 42.7-93.2%; max idioms 55.8-57.3%; volatile
// double dummy counts 0..4 = 85.5/85.5/96.6/85.5/85.5 (two is exact); six
// offset spellings 94.9-96.6%; fourteen compile flags no move.
//
// STRUCTURE THAT IS ALREADY EXACT (all verified; do not re-derive):
//  1. `clamped = (sq > K) ? K : sq` and the path-A clamp must be TERNARIES,
//     not if/else: every if/else or empty-then spelling ce2-if-converts to
//     subtract+select pair (2 insns, wrong shape).
//  2. Path B's clamp is NOT a ternary: `f1 = v; if (f1 < K) f1 = -f1; else
//     f1 = K;` reproduces retail's shape exactly (both arms non-empty, so no
//     if-conversion; the negate arm emits the extra forward jump to the merge).
//     Only the non-copy then-arm keeps it.
//  3. `fn_800C319C` is called INSIDE both arms (two separate calls). One
//     shared call hands `self` the wrong callee-saved home and desynchronises
//     ~40 words.
//  4. The LUT must be a struct-member array (`self->u.tbl[idx]`): that is the
//     only spelling that bases the indexed load on `self + 0x300`.
//  5. Latch must be `} while (--n != -1);` (compare on the PRE-decrement
//     value; the natural `n-- != 0` needs an extra copy).
//  6. Count guard `n = f1AC; n -= 1; if (n + 1 == 0) return;`.
//  7. Exactly TWO `volatile double` dummies produce the 0x48 frame (six GPR
//     saves at 0x20, both doubles at 0x38/0x40, LR at 0x4c).
//  8. `val = X / (f32)(f64)(u32)den;` then `val = val * clamped;` as two
//     statements, and the `(u32)` cast is required: it selects the unsigned
//     int->double expansion (bias store, 2^52 load, subtract, round) with the
//     magic hoisted into a callee-saved FPR; a signed cast would bias first.
//  9. File-local typedefs — the shared `Unk_999439AE` / `Unk_9994C3F5`
//     classes mistype +0x318 as s32 and have no LUT member.
// 10. `fn_800C319C` is `s32 (S4560 *, f32)` and reads both the pointer (its
//     +0x31C field) and the float argument, so no return-type flip is
//     available.
//
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
typedef struct { char pad0x0[0x84]; f32 f84; char pad0x88[0xD0]; f32 f158; char pad0x15C[0x50]; s32 i1AC; s32 i1B0; char pad0x1B4[0x13C]; void *p2F0; f32 f2F4; char pad0x2F8[0x8]; union { f32 tbl[0x1C]; struct { char q0[0x18]; f32 f318; f32 f31C; char q1[0x8]; s32 f328; s32 f32C; s32 f330; s32 f334; } fl; } u; } S4560;
typedef struct { char pad0x0[0x8]; f32 f8; char pad0xC[0x98]; f32 fA4; char pad0xA8[0x10]; s32 iB8; s32 iBC; char pad0xC0[0xC]; f32 fCC; } N4560;
extern f32 lbl_802990EC;
extern f32 lbl_802990F0;
extern f32 lbl_802990F4;
extern s32 fn_800C319C(S4560 * arg0, f32 arg1);
void fn_800C4560(S4560 *self) {
    volatile double _dummy0;
    volatile double _dummy1;
    f32 v;
    f32 pv;
    f32 sq;
    f32 clamped;
    f32 f1;
    f32 val;
    f32 t;
    s32 idx;
    s32 den;
    s32 n;
    s32 off;

    v = self->f84;
    sq = (v * v) / lbl_802990EC;
    clamped = (sq > lbl_802990F0) ? lbl_802990F0 : sq;
    if (((self->u.fl.f328 != 0) || (self->u.fl.f334 != 0)) && (self->u.fl.f32C == 0)) {
        n = self->i1AC;
        n -= 1;
        if (n + 1 == 0) {
            return;
        }
        off = (n * 16 - n) << 5;
        do {
            N4560 *node = (N4560 *)((char *)self->p2F0 + off);
            if (node->iBC != 0) {
                if ((self->u.fl.f330 == 0) || (node->iB8 == 0)) {
                    if (self->u.fl.f334 == 0) {
                        pv = node->f8;
                        f1 = (lbl_802990F4 > pv) ? lbl_802990F4 : pv;
                        idx = fn_800C319C(self, f1);
                    } else {
                        f1 = node->f8;
                        if (f1 < lbl_802990F4) {
                            f1 = -f1;
                        } else {
                            f1 = lbl_802990F4;
                        }
                        idx = fn_800C319C(self, f1);
                    }
                    den = self->i1B0;
                    val = ((self->f2F4 * self->u.fl.f31C) * self->u.tbl[idx]) / (f32)(f64)(u32)den;
                    val = val * clamped;
                    if (self->u.fl.f334 != 0) {
                        val *= -self->u.fl.f318;
                    }
                    if ((self->u.fl.f330 != 0) && (den == 4)) {
                        val += val;
                    }
                    t = node->fCC * val;
                    node->f8 = (t * self->f158) + node->f8;
                    node->fA4 = node->fA4 + t;
                }
            }
            off -= 0x1E0;
        } while (--n != -1);
    }
}
