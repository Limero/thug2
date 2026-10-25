// PARKED 2026-10-05: DIFF 7.97% (198/590 words, size-exact 2360B).
// family=m2c range=0x80099B2C-0x8009A464 size=2360B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// (the older SEARCHED/UPDATED notes below are kept for history)
//
// WHAT IT IS: a render-state + display-list submit. `fn(arg0, arg1, arg2)`
// guards on three pointers, then walks a long sequence of GX/PSMTX state
// setters and finally `GX_CallDisplayList`. Ground truth harvested from want
// (all verified, do not re-derive):
//  * 32 `bl` to 25 distinct callees:
//      fn_8001F91C x3, fn_800145AC x2, fn_800231C4 x2, PSMTXTrans x2,
//      PSMTXConcat x2, sinf x2, and once each: fn_8001F03C, fn_8001E2FC,
//      fn_8001E248, fn_8001E3CC, fn_8001E4E8, fn_8001E5DC, fn_8001E66C,
//      SetBlendMode, fn_8001EEE0, fn_8001EF84, fn_8001EFBC, fn_8001F298
//      (=GX_SetZMode), fn_8001FA54, fn_8001FEC0, fn_800205EC
//      (=GX_CallDisplayList), fn_80020494 (=GX_GetProjectionv), fn_800204D4
//      (=GX_GetViewportv), PSMTXInvXpose, PSMTXScale.
//    Only 5 of those 25 have a prototype in this draft; the other 20 are
//    implicit-int, which is almost certainly wrong for the float-taking ones
//    (a missing prototype adds a spurious condition-register setup before the
//    call and forces double promotion of the float args — check want for the
//    setup pattern per call site before adding a prototype: AGENTS-recipes
//    items 16/27).
//  * THREE top-level guards, each branching to the epilogue at 0x8009A424:
//      a null test on arg1's field, a chained load through arg0's pointer
//      field, and a global-flag test.
//    The second one was still a SCALED-POINTER bug in the m2c body
//    (`(s32 *)(P + 0x4)` adds 16 bytes); fixed here to
//    `*(s32 *)((char *)arg0->unk0x14 + 0x4)` so it emits a plain displaced
//    word load.
//  * TWO counted loops: a 4-word one at 0x80099DE8..0x80099DF8 and a
//    ~268-word one at 0x80099FF0..0x8009A420 (45% of the function is that one
//    loop body).  m2c's body has no faithful loop for either.
//  * REGISTER/FRAME FACTS (the real blocker): want saves ELEVEN float regs
//    (f21..f31 at 0x1c0..0x210) and FIFTEEN GPRs (save set from r17 at 0x184,
//    i.e. r17..r31) in a 0x218 frame; this draft produces 11 float regs but
//    saves from r14 (9 GPRs) in a 0xd0 frame. So the original keeps ~15 values
//    live across the state-setting calls and has a local pool of ~0x170
//    bytes, while m2c's body carries ~60 *undefined* temps
//    (temp_f10, temp_f1_2, var_ctr, var_r11 ...) that model none of that.
//    Until the live ranges are rebuilt the object cannot come close: every
//    GPR number in the body differs (want r21/r24/r26/r28..r31, got
//    r14/r19/r22/r25/r30), which alone costs most of the 543 differing words.
//
// The body's argument lists to the state setters are m2c's guesses and were NOT
// re-derived here; treat the first state-setting call (argument setup differs:
// want forwards the float args with a constant in a saved register) as the
// first thing to re-check if someone picks this up.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8037B614[];
extern char lbl_8037B9B8[];
extern char lbl_8037B9D8[];
extern char lbl_80297534[];
extern f32 lbl_80297540;
extern f32 lbl_80297544;
extern f32 lbl_80297548;
extern f32 lbl_8029754C;
extern f32 lbl_80297550;
extern f32 lbl_80297560;
extern char lbl_80297564[];
extern bool lbl_803018D0;
extern bool lbl_803018D4;
extern char lbl_803018E0[];
extern u8 lbl_8037B9BD;
void fn_8001EFBC(s32, s32 *);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_80099B2C(Unk_C8FEE62D *arg0, Unk_DB0E2BAB *arg1, Unk_C7387A53 *arg2) {
    s32 sp100;
    s32 spE0;
    s32 spB0;
    f32 sp9C;
    f32 sp8C;
    f32 sp80;
    s32 sp50;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r28;
    f32 temp_f10;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f21;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f30_5;
    f32 temp_f30_6;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 var_f1;
    f32 var_f2;
    s32 *var_r30;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r11_5;
    s32 temp_r3;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r9;
    s32 temp_r9_3;
    s32 temp_r9_5;
    s32 var_cr0_eq;
    s32 var_cr0_eq_2;
    s32 var_ctr;
    s32 var_r10;
    s32 var_r27;
    s32 var_r9;
    u16 temp_r0_3;
    u8 var_r30_2;
    Unk_6A78CE27 *temp_r11_4;
    CStruct *temp_r21;
    Unk_C8FEE62D *temp_r30;
    Unk_C7387A53 *temp_r3_2;
    void *temp_r9_2;
    CStruct *temp_r9_4;
    void *var_r11;
    void *var_r29;
    void *var_r31;

    if (((s32) arg1->unk0x8 != 0) && (temp_r21 = *(s32 *)((char *)arg0->unk0x14 + 0x4), ((temp_r21 == NULL) == 0))) {
        if (lbl_803018D4 != 0) {
            temp_f1 = *(f32 *)&lbl_80297534;
            sp18 = 0;
            fn_8001F03C(0, &sp18, 0x80290000, temp_f1, temp_f1, temp_f1, temp_f1);
            fn_8001E2FC(0, 0xFF, 0xFF, 4, 0xFF, 0xFF, 4);
            sp8 = 1;
            spC = 0;
            fn_8001E4E8(0, 0xF, 0xF, 0xF, 0xE, 0, 0, 0);
            sp8 = 1;
            sp14 = 0;
            spC = 0;
            sp10 = 0;
            fn_8001E3CC(0, 7, 7, 7, 6, 0, 0, 0);
            SetBlendMode(1, 4, 1, 0, 1, 0, 1);
            fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
            sp18 = QB_COLOR_GRAY8;
            fn_8001E66C(0, &sp18);
            fn_8001E248(2, 0, 0, 0, 0, 0, 2);
            sp18 = -1;
            fn_8001EFBC(4, &sp18);
            sp18 = -1;
            fn_8001EF84(4, &sp18);
            GX_SetZMode(0, 7, 0);
            fn_8001EEE0(0, 1, 1, 0, 0);
            return;
        }
        0;
        var_r31 = arg1->unk0x38 + (temp_r21->unk0xC << 5);
        var_cr0_eq = (((Unk_3513F638 *)var_r31)->unk0x4 & 0x100) == 0;
        if (var_cr0_eq == 0) {
            var_r30 = arg1->unk0x2C;
            temp_r11 = *(s32 *)((char *)var_r31 + (s32)0xA) - 1;
            temp_r9 = arg0->unk0x10;
            var_r29 = var_r30 + 0x10;
            var_ctr = temp_r11;
            if (temp_r11 > 0) {
                do {
                    var_r30 = var_r29 + (*((s32 *)var_r30) * 8);
                    var_r29 = var_r30 + 0x10;
                    var_ctr -= 1;
                } while (var_ctr != 0);
            }
            var_cr0_eq = temp_r9 == 0;
            var_r9 = 0;
            if (temp_r9 < 0) {
                temp_r7 = ((CStruct *)var_r30)->unk0xC;
                temp_r11_2 = ((CStruct *)var_r30)->unk0x4;
                temp_r3 = fn_800145AC() - (arg0->unk0x10 & QB_UNKNOWN_0x7FFFFFFF);
                temp_r8 = ((CStruct *)var_r30)->unk0x8;
                var_r10 = (temp_r3 + temp_r7) % temp_r11_2;
                if ((temp_r8 > 0) && ((s32) (temp_r3 / temp_r11_2) >= temp_r8)) {
                    var_r10 = ((temp_r11_2 * temp_r8) + temp_r7) % temp_r11_2;
                }
                var_r9 = ((CStruct *)var_r30)->unk0x0 - 1;
                var_cr0_eq = var_r9 == 0;
                if (var_r9 >= 0) {
                    temp_r11_3 = var_r9 * 8;
                    temp_r0 = *((s32 *)temp_r11_3 + (s32)var_r29);
                    var_cr0_eq = var_r10 == temp_r0;
                    if (var_r10 < temp_r0) {
                        var_r11 = temp_r11_3 + var_r29;
loop_14:
                        var_r9 -= 1;
                        var_cr0_eq = var_r9 == 0;
                        if (var_r9 >= 0) {
                            temp_r0_2 = *(s32 *)((char *)var_r11 - 0x8);
                            var_r11 -= 8;
                            var_cr0_eq = var_r10 == temp_r0_2;
                            if (var_r10 < temp_r0_2) {
                                goto loop_14;
                            }
                        }
                    }
                }
            }
            ((Unk_3513F638 *)var_r31)->unk0x0 = (s32) *(s32 *)((char *)((var_r9 * 8) + var_r29) + 0x4);
            temp_r11_4->unk0x6 = (u8) (temp_r11_4->unk0x6 | 8);
            temp_r11_4 = *(s32 *)((char *)arg0->unk0x14 + 0x4);
        }
        0;
        if (var_cr0_eq != 0) {
            var_cr0_eq_2 = lbl_803018D0 == 0;
            if ((var_cr0_eq_2 == 0) && (temp_r9_2 = *(s32 *)((char *)arg0->unk0x14 + 0x4), var_cr0_eq_2 = (s32) (*(s32 *)((char *)temp_r9_2 + (s32)0x6) & 0x18) == 0, (var_cr0_eq_2 != 0))) {
                temp_r11_5 = arg1->unk0x24;
                temp_r9_3 = *(s32 *)((char *)temp_r9_2 + (s32)0xE) * 0x18;
                GX_CallDisplayList(*(s32 *)((char *)(temp_r9_3 + temp_r11_5) + 0x4), *((s32 *)temp_r9_3 + (s32)temp_r11_5));
            } else {
                0;
                if (var_cr0_eq_2 == 0) {
                    goto block_22;
                }
                temp_r9_4 = arg0->unk0x14;
                temp_r3_2 = temp_r9_4->unk0x4;
                fn_800231C4(temp_r3_2, arg1->unk0x38 + (temp_r3_2->unk0xC << 5), 1, 1, 0, 0, temp_r9_4);
            }
        } else {
block_22:
            *(s32 *)(lbl_8037B9B8 + (s32)0x0) = QB_UNKNOWN_0x59A32C24;
            *(s32 *)(lbl_8037B9B8 + (s32)0x4) = 1;
            *(s32 *)(lbl_8037B9B8 + (s32)0x6) = 2;
            *(s32 *)(lbl_8037B9B8 + (s32)0x5) = 0x80;
            *(s32 *)(lbl_8037B9D8 + (s32)0x4) = 0x61;
            *(s32 *)(lbl_8037B9D8 + (s32)0x0) = (s32) arg2->unk0xC;
            *(s32 *)(lbl_8037B9D8 + (s32)0x10) = 0;
            *(s32 *)(lbl_8037B9D8 + (s32)0x7) = 0;
            *(s32 *)(lbl_8037B9D8 + (s32)0xE) = 0x80;
            *(s32 *)(lbl_8037B9D8 + (s32)0xF) = 0xFF;
            *(s32 *)(lbl_8037B9D8 + (s32)0x16) = 0;
            *(s32 *)(lbl_8037B9D8 + (s32)0x6) = 0;
            *(s32 *)(lbl_8037B9D8 + (s32)0xC) = 0x80;
            *(s32 *)(lbl_8037B9D8 + (s32)0xD) = 0x80;
            fn_800231C4((void *)lbl_8037B9B8, 0x8037B9D8, 1, 1, 0, 0, (void *)lbl_8037B9D8, 0);
        }
        0;
        var_r30_2 = *(s32 *)(*(s32 *)((char *)*(s32 *)((char *)((char *)arg0) + 0x14) + 0x4) + 0x5);
        if (0) {
            var_r30_2 = lbl_8037B9BD;
        }
        if ((s32) *(u8 *)&lbl_803018E0 != 0) {
            *(s32 *)&lbl_803018E0 = 0U;
            fn_8001FEC0(0);
        }
        var_r27 = 0;
        fn_8001FA54(6, var_r30_2, 0, 6, var_r30_2);
        if ((s32) temp_r21->unk0x4 > 0) {
            temp_f27 = lbl_80297540;
            temp_f25 = lbl_80297548;
            temp_f23 = lbl_80297544;
            temp_f21 = lbl_8029754C;
            temp_f26 = lbl_80297550;
            temp_f24 = *(s32 *)&lbl_80297534;
            do {
                temp_r0_3 = ((Unk_3513F638 *)var_r31)->unk0x4;
                if ((s32) (temp_r0_3 & 6) != 0) {
                    switch (var_r27) {              
                    case 0:
                        var_r28 = 0x1E;
                        break;
                    case 1:
                        var_r28 = 0x21;
                        break;
                    case 2:
                        var_r28 = 0x24;
                        break;
                    case 3:
                        var_r28 = 0x27;
                        break;
                    default:
                        var_r28 = 0x3C;
                        break;
                    }
                    if (temp_r0_3 & 2) {
                        ((s32 (*)(s32, s32 *)) 0x8025E198)(0x8037B614, &spB0);
                        GX_GetProjectionv(&spE0);
                        GX_GetViewportv(&sp100);
                        temp_f1_2 = (f32) (f64) *(f32 *)((char *)var_r31 + (s32)0x12) * temp_f27;
                        temp_f30 = -*(s32 *)(lbl_8037B614 + (s32)0xC) * (temp_f1_2 * temp_f23);
                        temp_f2 = (f32) (f64) ((Unk_3513F638 *)var_r31)->unk0x14 * temp_f27;
                        temp_f31 = -*(s32 *)(lbl_8037B614 + (s32)0x1C) * (temp_f2 * temp_f23);
                        temp_f30_2 = temp_f30 - (f32) (f64) (s32) temp_f30;
                        temp_f31_2 = temp_f31 - (f32) (f64) (s32) temp_f31;
                        ((s32 (*)(f32 *, f32, f32, f32)) 0x8025E3B4)(&sp20, temp_f1_2 * temp_f25, temp_f2 * temp_f21, *(s32 *)&lbl_80297534);
                        ((s32 (*)(s32 *, f32, f32, f32)) 0x8025E380)(&sp50, temp_f25, temp_f25, lbl_80297550);
                        ((s32 (*)(s32 *, f32 *, f32 *)) 0x8025DFD4)(&sp50, &sp20, &sp80);
                        ((s32 (*)(f32 *, s32 *, f32 *)) 0x8025DFD4)(&sp80, &spB0, &sp80);
                        sp8C += temp_f30_2;
                        sp9C += temp_f31_2;
                        fn_8001F91C(&sp80, var_r28, 1);
                    } else if ((s32) *(s32 *)((char *)var_r31 + (s32)0x17) != 0) {
                        sp20 = (f32) (f64) ((Unk_3513F638 *)var_r31)->unk0x18 * temp_f27;
                        sp28 = temp_f26;
                        sp24 = -(f32) (f64) *(f32 *)((char *)var_r31 + (s32)0x1A) * temp_f27;
                        sp2C = ((f32) (f64) *((f32 *)&((Unk_3513F638 *)var_r31)->unk0x1C) * temp_f27) - temp_f26;
                        sp30 = (f32) (f64) *(f32 *)((char *)var_r31 + (s32)0x1A) * temp_f27;
                        sp38 = temp_f26;
                        sp34 = (f32) (f64) ((Unk_3513F638 *)var_r31)->unk0x18 * temp_f27;
                        sp3C = ((f32) (f64) *(f32 *)((char *)var_r31 + (s32)0x1E) * temp_f27) - temp_f26;
                        fn_8001F91C(&sp20, var_r28, 1, temp_r0_3, temp_r0_3, temp_r0_3, temp_r0_3);
                    } else {
                        temp_r8_2 = arg1->unk0x34;
                        temp_r9_5 = ((Unk_3513F638 *)var_r31)->unk0x8 << 5;
                        temp_r30 = temp_r8_2 + temp_r9_5;
                        temp_f31_3 = (f32) (f64) fn_800145AC(arg0) * lbl_80297560;
                        temp_f30_3 = temp_f31_3 * *((s32 *)temp_r8_2 + (s32)temp_r9_5);
                        temp_f30_4 = (temp_r30->unk0x10 * sinf((temp_r30->unk0x8 * temp_f31_3) + temp_r30->unk0x18)) + temp_f30_3;
                        temp_f29 = temp_f31_3 * temp_r30->unk0x4;
                        temp_f10 = *(f32 *)&lbl_80297564;
                        temp_f30_5 = temp_f30_4 + temp_f10;
                        temp_f2_2 = (temp_r30->unk0x14 * sinf((temp_r30->unk0xC * temp_f31_3) + temp_r30->unk0x1C)) + temp_f29 + temp_f10;
                        temp_f30_6 = temp_f30_5 - (f32) (f64) ((s32) temp_f30_5 & QB_UNKNOWN_0xFFFFFFF0);
                        temp_f2_3 = temp_f2_2 - (f32) (f64) ((s32) temp_f2_2 & QB_UNKNOWN_0xFFFFFFF0);
                        if (temp_f30_6 < temp_f24) {
                            var_f1 = temp_f30_6 + temp_f10;
                        } else {
                            var_f1 = temp_f30_6 - temp_f10;
                        }
                        if (temp_f2_3 < temp_f24) {
                            var_f2 = temp_f2_3 + *(s32 *)&lbl_80297564;
                        } else {
                            var_f2 = temp_f2_3 - *(s32 *)&lbl_80297564;
                        }
                        ((s32 (*)(f32 *, f32, f32, f32)) 0x8025E380)(&sp20, var_f1, var_f2, *(s32 *)&lbl_80297534);
                        fn_8001F91C(&sp20, var_r28, 1);
                    }
                }
                var_r27 += 1;
                var_r31 += 0x20;
            } while (var_r27 < (s32) temp_r21->unk0x4);
        }
    }
}
