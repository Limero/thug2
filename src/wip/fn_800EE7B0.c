// PARKED 2026-09-18 — FPR-ALLOCATION WALL in the clamp block (30/90 words).
// 8.0% -> 66.7%. Everything outside one 12-word block now matches word-for-word
// (prologue, both conversions, all five call sites, both QB_STRONG sites).
//
// WHAT FIXED IT (five real defects in the m2c draft):
//  1. `*(s32 *)(*(s32 *)((char *)arg0 + 0xB8) + 0x1340)` is a **f32** field, not
//     s32: want is `lfs f0, 0x1340(r9)` with no conversion. As s32 the draft got
//     the int->double 2^52 bit trick (xoris + an extra live f30), which cost the
//     whole frame (0x30 vs want's 0x38 with `stfd f31` only) and every offset
//     after it.
//  2. The first conversion is the **unsigned** variant. want is
//     `stw r0,0x1c(r1); lis r10,0x4330; stw r10,0x18(r1); lfd f31,0x18(r1);
//     fsub f31,f31,f0` with f0 = lbl_802AAEC0 (2^52) — no `xoris`, which is the
//     u32->double path. Writing `(f32)(f64)(u32)((lbl_80303150 + Tmr_GetTime()) -
//     temp_r30)` with `extern u32 lbl_80303150` reproduces it.
//  3. `CStruct_new` / `CStruct_ctor` are the family call pair:
//     `temp_r30_2 = CStruct_ctor(CStruct_new(8));` (no argument setup for the
//     second call — r3 carries over). See fn_800AB990 / fn_801F4BB8.
//  4. Raw address literals -> registered symbols: `*(s32 *)0x80303150` is
//     `lbl_80303150` (u32), `*(f32 *)0x8029AEC8/AECC/AED0` are `lbl_8029AEC8`,
//     `lbl_8029AECC`, `lbl_8029AED0` (all `f32` in symbols.txt). Also
//     `PARKED`-style note: the draft's `0x8029AECC`/`0x8029AED0` split is real —
//     want loads AED0 (upper clamp, `fcmpu cr0,f31,f13`) first, then AECC.
//  5. `temp_f13` = lbl_8029AED0 and `temp_f12` = lbl_8029AECC are genuine locals
//     (each is loaded once and used twice).
//
// WHY IT IS PARKED: want keeps the four clamp values in f31/f13/f12/f0/f1
// (`lfs f13` / `lfs f12` / `fmr f0,f31` / `fmr f1,f0`), ngccc allocates f0/f13
// for the two loads and f1 for the running value, and drops the `var_f1 = var_f0`
// copy by coalescing. Probed and rejected: both clamp forms (default-then-
// override and if/else), assignment order (temps before/after `var_f0`, swapped
// temp order), local declaration order (3 permutations), and relying on the
// labels directly instead of temps — all 64.4-66.7%. The prologue and the tail
// are byte-exact, so only the FPR assignment inside this block is open.
// family=m2c range=0x800EE7B0-0x800EE918 size=360B
#include "qb_constants.h"
#include "structs.h"
f32 fn_800EEB10(s32, s32);
f32 fn_800EEAE0(Unk_31DE137E *, s32);
void fn_8012772C(CStruct *, s32, f32);
void fn_800CCD34(CScript *, CStruct *);
s32 Tmr_GetTime(void);
void fn_8009F010(s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 CStruct_delete(s32, s32);
extern u32 lbl_80303150;
extern f32 lbl_8029AEC8;
extern f32 lbl_8029AECC;
extern f32 lbl_8029AED0;
void fn_800EE7B0(Unk_FFAD6788 *arg0) {
    volatile double _dummy;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f0;
    f32 var_f1;
    s32 temp_r30;
    s32 temp_r30_2;

    temp_r30 = arg0->unk0xB4;
    temp_f31 = (f32)(f64)(u32)((lbl_80303150 + Tmr_GetTime()) - temp_r30);
    if (!(temp_f31 < fn_800EEB10((s32)arg0, QB_COLLISION_MUTE_DELAY))) {
        temp_f31_2 = *(f32 *)(arg0->unk0xB8 + 0x1340) / fn_800EEAE0((Unk_31DE137E *)arg0, QB_FULLCOLLISION);
        if (temp_f31_2 > fn_800EEB10((s32)arg0, QB_COLLISION_CUTOFF_FACTOR)) {
            fn_8012772C((CStruct *)arg0->unk0x2C, QB_PERCENT, temp_f31_2 * lbl_8029AEC8);
            fn_800CCD34((CScript *)arg0->unk0xBC, (CStruct *)arg0->unk0x2C);
            arg0->unk0xB4 = lbl_80303150 + Tmr_GetTime();
            temp_r30_2 = CStruct_ctor(CStruct_new(8));
            temp_f13 = lbl_8029AED0;
            temp_f12 = lbl_8029AECC;
            if (temp_f31_2 > temp_f13) {
                var_f0 = temp_f13;
            } else {
                var_f0 = temp_f31_2;
            }
            var_f1 = var_f0;
            if (var_f0 < temp_f12) {
                var_f1 = temp_f12;
            }
            fn_8012772C((CStruct *)temp_r30_2, QB_STRENGTH, var_f1);
            fn_8009F010(*(s32 *)(arg0->unk0xB8 + 0x1358), QB_UNKNOWN_0xC4A60423, temp_r30_2);
            if (temp_r30_2 != 0) {
                CStruct_delete(temp_r30_2, 3);
            }
        }
    }
}
