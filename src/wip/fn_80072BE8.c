// WIP DRAFT (non-matching) — hand-rebuilt from the want bytes (m2c was only a skeleton)
// family=m2c range=0x80072BE8-0x80072E4C size=612B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-04. Best measured body: 600B object vs 612B want (3 words
// SHORT), frame already 0xc8, GPR save set already r26..r31, masked want_got
// 143/153 differing words. Semantic decode of every pool value and of every
// want instruction is DONE and reproduced below; the residual is register /
// CR-field / slot allocation, not semantics.
//
// WHAT THE WANT ACTUALLY IS (fully decoded — this part is trustworthy)
//   f31 = (f32)((f64){0x43300000, fn_80016EC4(arg1)^0x80000000} - 2^52+2^31)
//        i.e. the compiler's int-to-float idiom: sign-flip the value, store
//        the bias words to the frame, load the pair as a double, subtract
//        the magic bias, round to single.
//        `lbl_80295568` IS that magic constant (2^52+2^31 = 4503601774854144.0);
//        the pool-double load in want is the retargeted load (see fix_fp_pool).
//   f31 *= 0.5f (lbl_80295570) only when arg1 == 0.
//   f30 = (lbl_80301638 == 1) ? lbl_80295574(1.0f) : lbl_8030163C(1.0f).
//   arr[7] = {0.015625, 0.09375, 0.234375, 0.3125, 0.234375, 0.09375, 0.015625}
//   f28 = f30 / f31   (emitted between the 6th and 7th arr store)
//   then the six UI calls, then d = (f64)(s32)farg1  (fctiwz + stfd, no magic)
//   loop i=0..6:  a = d.low; d.low = (i-3)^0x80000000; d.high = 0x43300000;
//                 f1 = f28*(f32)(d - 2^52); f2 = f1;
//                 if (arg2!=5) f1*=0.0f(lbl_80295588); if (arg2!=6) f2*=0.0f;
//                 fn_8007297C(0x280, 0x1C0, 2, a, f1, f2, arr[i]*farg0);
//   IMPORTANT non-obvious trick reproduced here: want's loop subtracts the
//   double pair (high = 2^52 bias, low = negative zero), i.e. the LOW word of
//   the (f64)4503601774854144.0 constant is -0.0 and the compiler folds it
//   with the 0.0 multiplier literal, while the HIGH word is copied from the
//   still-live magic pair.  That is why the multiplier must be a
//   literal `0.0f` (not the global) and why the loop constant must be the
//   2^52 pool entry, not lbl_80295568.
//
// REMAINING BLOCKERS (all register/slot allocation, measured, not guessed)
//   B1  4 callee-saved float regs (f28..f31) vs want's 6 (f26..f31).  Want
//       keeps both quotient inputs in callee-saved registers even though both
//       die at the divide *before* the calls; every C shape tried puts them
//       in scratch regs, which drops the count to 4 and shifts every stack
//       offset.
//   B2  The loop's two loop-invariant tests land in cr3/cr4 here; want puts
//       them in cr0/cr4, which forces the compiler's condition-register
//       cache save/restore pair (want's 2 extra words).  With both fields
//       non-default the build emits no such save at all.  Condition-field
//       choice not steerable from C.
//   B3  The two product registers' roles are swapped: want computes the
//       product into the first float arg, copies it aside, then to the second
//       arg (1 extra word); here the product goes to the second arg first,
//       then the first.
//   B4  The compiler splits the punned-double temporary into a separate 8-byte
//       slot (here 0x80) instead of reusing the loop's slot (want 0x70) — one
//       extra store/load pair in the loop preheader.
//
// NEGATIVE RESULTS (all measured, all reverted)
//  - GCC 2.95 bogus CSE: writing `f31v = (f32)(d - <literal>)` and
//    `f1 = f28v*(f32)(d - <literal>)` over the same punned `d` makes the
//    compiler CSE the two `X - magic` expressions and seed `d` in the loop
//    preheader from the *int-conversion* value -> +20B garbage.  Fixed by making the pre-loop
//    value a SEPARATE local (`e`) or by not using a literal at all there
//    (the `(f32)(f64)(s32)x` cast).  Reproduced with pd-pointer, named-struct
//    union, s32[2]+pun, direct `*(s32*)&d`, and `volatile f64` variants.
//  - Loop-constant `4503599627370496.0` (2^52) vs `lbl_80295568` (2^52+2^31):
//    only the 2^52 literal reproduces want's high-word copy + shared-0.0-
//    low-word pair.
//  - Store order of the 7 arr writes, `v[4]` writes, the int-conversion store,
//    the divide position, and the `arr[22]` over-declaration (needed to grow the
//    local area to the 128 bytes want uses between 0x00-0x7f) all already
//    match; reordering them does not change the score.
//  - `-mps-float` irrelevant (no PS), no flags/pins tried beyond the default
//    set; the residual is a compile-time CSE bug + allocator pressure, not a
//    scheduling knob.
// ---------------------------------------------------------------------------
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_80295570;
extern f32 lbl_80295574;
extern f32 lbl_80295578;
extern f32 lbl_8029557C;
extern f32 lbl_80295580;
extern f32 lbl_80295584;
extern s32 lbl_80301638;
extern f32 lbl_8030163C;
s32 fn_80016EAC(s32);
s32 fn_80016EC4(s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8007272C(s32);
void SetBlendMode(s32, s32, s32, s32, s32, s32, s32);
void set_blend_mode(s32, s32, s32);
void fn_8007297C(s32, s32, s32, s32, f32, f32, f32);

void fn_80072BE8(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    s32 v[4];
    f32 arr[22];
    f64 d;
    s32 *pd = (s32 *)&d;
    s32 i;
    s32 a;
    f32 f31v;
    f32 f30v;
    f32 f28v;
    f32 f1;
    f32 f2;

    fn_80016EC4(arg0);
    fn_80016EAC(arg1);
    f31v = (f32)(f64)(s32)fn_80016EC4(arg1);
    if (arg1 == 0) {
        f31v = f31v * lbl_80295570;
    }
    f30v = (lbl_80301638 == 1) ? lbl_80295574 : lbl_8030163C;
    arr[0] = lbl_80295578;
    arr[1] = lbl_8029557C;
    arr[2] = lbl_80295580;
    arr[3] = lbl_80295584;
    arr[4] = lbl_80295580;
    arr[5] = lbl_8029557C;
    arr[6] = lbl_80295578;
    f28v = f30v / f31v;
    set_blend_mode(0, 0, 0);
    v[0] = 1;
    v[1] = 0;
    v[2] = 0;
    v[3] = 0;
    fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0);
    v[0] = 1;
    v[1] = 0;
    fn_8001E4E8(0, 15, 15, 15, 15, 0, 0, 0);
    fn_8007272C(0);
    SetBlendMode(1, 1, 1, 0, 1, 0, 0);
    pd[1] = (s32)farg1;
    pd[0] = QB_INT_TO_DOUBLE_BIAS;
    for (i = 0; i <= 6; i++) {
        a = pd[1];
        pd[1] = (i - 3) ^ 0x80000000;
        pd[0] = QB_INT_TO_DOUBLE_BIAS;
        f1 = f28v * (f32)(d - 4503599627370496.0);
        f2 = f1;
        if (arg2 != 5) {
            f1 = f1 * 0.0f;
        }
        if (arg2 != 6) {
            f2 = f2 * 0.0f;
        }
        fn_8007297C(0x280, 0x1C0, 2, a, f1, f2, arr[i] * farg0);
    }
}