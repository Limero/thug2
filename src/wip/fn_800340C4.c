// WIP DRAFT (non-matching) — hand-rebuilt from want; 97.20% (4 / 143 words).
// family=m2c range=0x800340C4-0x80034300 size=572B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED: 4-word residual, all one `local_alloc` register choice ===
//
// Both clamp chains want the `w` value re-allocated to the scratch float
// register for the subtract-compare sequence, while this build keeps `w` in
// its division-chain home register and only each chain's intermediate gets
// the scratch register.  Same compare targets either way; only the
// destination register colour differs (4 words across the two chains).
//
// The C variable `w` is ONE web: its home is f12 for the division chain
// (still f12 coming out of the chained multiply-add at 0x80034154) and want
// RE-ALLOCATES it to f0 for both clamp chains, i.e. retail's `w` is split
// across the two multiplies.
// ngccc keeps one home (f12) and only the intermediate of each chain gets
// f0.  Tried and measured, all byte-identical or worse:
//   - `w = v - a; w = w - b;` (two-step, in-place): both steps in f12 (8)
//   - separate named clamp temp `wt` (single + two-step, pinned or not): 11,
//     and it renames the f12/f13 pair instead (see git history of this file)
//   - `"+f"(w)` barriers after the multiplies / before each clamp, doubled:
//     4 (inert);  `volatile f32 w` (+ frame re-pad): 44;  separate division
//     temp `wd`: 13
//   - hard pin `register f32 w __asm__("fr0")`: 4 (pin dropped)
//   - declaration-order and multiply-order permutations (a,b)/(b,a): 4
//   - the clamp value as an inline condition, no named temp
//     (`if ((v - a) - b < lo)` / `if ((v + a) + b > hi)`): 92.3%
//   - 24 `-f`/`-O` flags: all 4 or far worse; `-fno-schedule-insns2` 43,
//     `-fno-expensive-optimizations` 42, `-ffloat-store`/`-fno-builtin` 142
// Object length is exact (572 B == symbols.txt size) and every instruction
// kind/position matches, so this is a register-ALLOCATION choice, not a
// scheduling or structural one.
//
// === LEVERS THAT DID WORK (do not regress them) ===
// 1. Local struct with real `f32` members.  The corpus-merged `Unk_DB0E2BAB`
//    types every field `s32`; with it the loads are integer word loads and
//    the function scores ~4%.  Sub-object at `+0x4` holds `f32` at
//    `+0x1C/+0x20/+0x24` (byte-proven by src/fn_80034030.c and src/fn_80034300.c).
// 2. `char _pad[0x48];` — dead filler that makes the locals region exactly
//    0x5c.  9x `volatile double` and `volatile double[9]` give the same object.
//    Frame: 0xb8 bytes, float-register saves at 0x70..0xb0, GPR save at 0x64,
//    link-register slot at 0xbc, the `(f32)(f64)(s32)` conversion slot at
//    0x58/0x5c.
// 3. `c1/c2/c3` assigned AFTER the first `Tmr_GetTime()` (42 vs 68 diffs).
// 4. `v = b * y + v;` — the final accumulator must reuse v's register;
//    `b = b*y; b = b + v;` gives the wrong destination register.
// 5. `register f32 b __asm__("fr28");` — the pin does bind here and fixes the
//    whole callee-saved FPR map (a=f26 b=f28 c1=f27 c2=f30 c3=f29 v=f25
//    s1=f24 s2=f23).  Without it the (f27..f30) group is rotated.
//    Pins on a/c1/c2/c3 are inert (measured 45-pin sweep).
// 6. A NAMED `prod` for `(f32)(f64)(s32)x * c1 * c2`: 36 -> 20 diffs.  Inline,
//    the product shares x's register and the second sine block's `x`/`prod`
//    f0/f1 colouring flips (12 words).  This is the "two webs trade f0/f1"
//    case — give the product its own name.
// 7. A SEPARATE variable `sub2` for the second clamp's `arg0->unk0x4` load:
//    20 -> 10 diffs, and it also fixed the r9/r10/r11 page-anchor rotation at
//    the top of the function.  Reassigning the same `sub` made ngccc CSE both
//    loads into r10.
// 8. `span = hi + lo; span = span * half;` instead of `span = (hi + lo) * half;`
//    (2-word swap of the constant-load vs multiply order): 10 -> 8.
// 9. `w = (v - a) - b;` / `w = (v + a) + b;` as single expressions: 8 -> 4.
//
// === REJECTED ===
// Manual int->f32 union dance (references the real `lbl_80291C68`): 564 B,
// frame 0xd8, 8 float-register saves, 2 GPR saves, two conversion slots, and
// the wrong convert-sequence variant.  The plain `(f32)(f64)(s32)` cast is
// what retail wrote.  The object's private float pool is relocation-masked
// and link-routed by tools/fix_fp_pool.py at promote time.
//
// Callee arities (all audited from the retail prologues): `Tmr_GetTime` is
// 0-arg `s32`-returning; `sinf` is 1-arg `f32`-returning.  Both prototypes are
// load-bearing (m2c's guesses add a spurious condition-register setup and
// change the argument passing).
#include "types.h"

typedef struct { char pad0x0[0x1C]; f32 unk0x1C; f32 unk0x20; f32 unk0x24; } S340C4_sub;
typedef struct {
    char pad0x0[4];
    S340C4_sub *unk0x4;
    char pad0x8[0x10];
    f32 unk0x18;
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
} S340C4;

extern f32 lbl_80291C60; /* 0.5      */
extern f32 lbl_80291C64; /* 1.0      */
extern f64 lbl_80291C68; /* 2^52+2^31 */
extern f32 lbl_80291C70; /* 0.0625   */
extern f32 lbl_80291C74; /* 16.0     */
extern f32 lbl_80291C78; /* pi       */
extern s32 lbl_80303150;

s32 Tmr_GetTime(void);
f32 sinf(f32);

f32 fn_800340C4(S340C4 *arg0) {
    char _pad[0x48];
    S340C4_sub *sub, *sub2;
    f32 half, one, c1, c2, c3;
    f32 lo, hi, v, t, a, s1, s2, span, num, den, w;
    register f32 b __asm__("fr28");
    f32 x, y, prod;
    sub = arg0->unk0x4;
    half = lbl_80291C60;
    lo = sub->unk0x1C;
    hi = sub->unk0x24;
    v = arg0->unk0x2C;
    one = lbl_80291C64;
    t = arg0->unk0x28;
    a = arg0->unk0x18;
    b = arg0->unk0x1C;
    s1 = arg0->unk0x20;
    s2 = arg0->unk0x24;

    span = hi + lo;
    span = span * half;
    num = v - span;
    num = fabs(num);
    den = (hi - lo) * half;
    w = (t - one) * num;
    w = w / den;
    w = w + one;
    a = a * w;
    b = b * w;

    w = (v - a) - b;
    if (w < lo) {
        v = lo + a + b;
    }
    w = (v + a) + b;
    if (w > hi) {
        v = (hi - a) - b;
    }

    x = (f32)(f64)(s32)(lbl_80303150 + Tmr_GetTime()) * s1;
    c1 = lbl_80291C70;
    c2 = lbl_80291C74;
    c3 = lbl_80291C78;
    prod = (f32)(f64)(s32)x * c1 * c2;
    y = sinf(2.0f * (x - prod) * c3);
    b = b * y + a;

    x = (f32)(f64)(s32)(lbl_80303150 + Tmr_GetTime()) * s2;
    prod = (f32)(f64)(s32)x * c1 * c2;
    y = sinf(2.0f * (x - prod) * c3);
    v = b * y + v;

    sub2 = arg0->unk0x4;
    if (v < sub2->unk0x1C) {
        v = sub2->unk0x1C;
    }
    if (v > sub2->unk0x24) {
        v = sub2->unk0x24;
    }
    return v;
}
