// PARKED 2026-10-03 — base 1.8% (2644 B, 548 words).  Random-sample pick.
// Tested s32->u32 on every s32 parameter (arg3/arg4/arg6) plus the `u32 swvN`
// staging spelling: FLAT at 10/548.  Confirms recipe 7w is exhausted here; the
// m2c decode is simply wrong.  Needs a full rebuild.
//
// family=m2c range=0x8002A3E0-0x8002AE34 size=2644B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// VOID-ARITY FIX 2026-09-11 (tools/fix_void_calls.py): callee is `(void)` in src/ -- phantom argument removed; 2.0% -> 2.1%.
#include "types.h"
#include "structs.h"
s32 fn_80026AD4(void *);
// FLAG: -fno-rerun-cse-after-loop
extern char lbl_80291650[];
extern f32 lbl_80291654;
extern f32 lbl_80291660;
extern char lbl_80291664[];
extern f32 lbl_80291668;
static s32 sp80;

void fn_80026140(s32, CStruct *, CStruct *, s32);
s32 sqrtf(s32);
void fn_8002D2A0(void);
s32 fn_8002A3E0(Unk_DB0E2BAB *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, CScript *arg5, f32 farg0, s32 arg6) {
    s32 spD4;
    s32 sp84;
    void *sp80;
    f32 sp78;
    s32 sp68;
    s32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    Unk_59AB5482 sp18;
    f32 spC;
    Unk_59AB5482 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f13_4;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f25;
    f32 var_f26;
    s16 var_r0_2;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r15;
    s32 temp_r20;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r31;
    s32 var_r8;
    s32 var_r8_2;
    u16 var_r0;
    void *temp_r10;
    void *temp_r10_2;
    void *var_r22;
    void *var_r23;
    Unk_5AA7B5D7 *var_r25;
    Unk_5D1D68CC *var_r26;
    Unk_5AA7B5D7 *var_r27;
    void *var_r28;
    Unk_5D1D68CC *var_r29;
    void *var_r30;

    spD4 = 0;
    var_r30 = arg1;
    temp_r0 = arg0->unk0x4;
    var_r28 = arg2;
    if (temp_r0 & 0x800000) {
        temp_r9 = temp_r0 & 0x1000;
        if ((temp_r9 == 0) && ((s32) arg0->unk0x24 == 0)) {
            fn_8002D2A0();
            fn_8002AFB0(arg0, fn_8002D718());
        }
        0;
        return fn_80027720(arg0, var_r30, var_r28, arg3, arg4, arg5, farg0);
    }
    var_r29 = arg0->unk0x10;
    var_r31 = 0;
    var_r27 = arg0->unk0x14;
    var_f26 = *(f32 *)&lbl_80291650;
    var_r26 = var_r29;
    var_r25 = var_r27;
    var_f25 = var_f26;
    temp_f30 = farg0 * lbl_80291654;
    var_r22 = var_r29;
    var_r23 = var_r27;
    temp_r15 = arg0->unk0x18;
    if ((s32) arg0->unk0x8 > 0) {
        temp_f28 = lbl_80291660;
        temp_f27 = *(f32 *)&lbl_80291664;
        temp_f29 = lbl_80291668;
        do {
            sp84 = var_r31 + 1;
            temp_r20 = fn_80026A84(arg0, temp_r15, var_r31);
            temp_r3 = fn_80026AA8(arg0, temp_r15, var_r31);
            var_r8 = 0;
            sp80 = var_r30 + 0x10;
            if (temp_r20 > 0) {
                temp_r0_2 = temp_r20 - 1;
                if (temp_r0_2 == 0) {
                    var_r26 = var_r22;
                    var_r29 = var_r22;
                    var_f25 = *(s32 *)&lbl_80291650;
                } else {
loop_11:
                    temp_r9_2 = var_r8 * 8;
                    temp_r10 = temp_r9_2 + var_r22;
                    temp_f12 = (f32) (f64) ((s32) (*((s32 *)temp_r9_2 + (s32)var_r22) << 0x11) >> 0x11);
                    0;
                    if ((0 == 0) || (0, (0 == 0))) {
                        var_r8 += 1;
                        if (var_r8 < temp_r20) {
                            if (var_r8 == temp_r0_2) {
                                var_f25 = *(s32 *)&lbl_80291650;
                                var_r29 = var_r22 + (var_r8 * 8);
                                var_r26 = var_r29;
                            } else {
                                goto loop_11;
                            }
                        }
                    } else {
                        var_r26 = temp_r10;
                        var_r29 = temp_r10 + 8;
                        var_f25 = (temp_f30 - temp_f12) / ((f32) (f64) ((s32) (((Unk_9994C3F5 *)temp_r10)->unk0x8 << 0x11) >> 0x11) - temp_f12);
                    }
                }
            }
            temp_r3_2 = fn_80026AD4(arg0);
            temp_f0 = *(s32 *)&lbl_80291650;
            if (var_f25 == temp_f0) {
                if (temp_r3_2 != 0) {
                    *((f32 *)&((CStruct *)var_r30)->unk0x0) = (f32) *((f32 *)&var_r26->unk0x4);
                    *((f32 *)&((CStruct *)var_r30)->unk0x4) = (f32) *((f32 *)&var_r26->unk0x8);
                    var_f0 = var_r26->unk0xC;
                } else {
                    *((f32 *)&((CStruct *)var_r30)->unk0x0) = (f32) ((f32) (f64) *(f32 *)((char *)var_r26 + (s32)0x2) * temp_f28);
                    *((f32 *)&((CStruct *)var_r30)->unk0x4) = (f32) ((f32) (f64) (s16) *((f32 *)&var_r26->unk0x4) * temp_f28);
                    var_f0 = (f32) (f64) *(f32 *)((char *)var_r26 + (s32)0x6) * temp_f28;
                }
                ((CStruct *)var_r30)->unk0x8 = var_f0;
                temp_f0_2 = *((f32 *)&((CStruct *)var_r30)->unk0x0);
                temp_f13 = *((f32 *)&((CStruct *)var_r30)->unk0x4);
                temp_f12_2 = ((CStruct *)var_r30)->unk0x8;
                var_f1 = ((temp_f27 - (temp_f0_2 * temp_f0_2)) - (temp_f13 * temp_f13)) - (temp_f12_2 * temp_f12_2);
                0;
                if (0 == 0) {
                    var_f1 = *(s32 *)&lbl_80291650;
                }
                var_f1_2 = sqrtf(var_f1);
                ((CStruct *)var_r30)->unk0xC = var_f1_2;
                var_r0 = var_r26->unk0x0;
                goto block_30;
            }
            temp_f13_2 = *(s32 *)&lbl_80291664;
            temp_cr0_eq = var_f25 == temp_f13_2;
            if (temp_cr0_eq != 0) {
                if (temp_r3_2 != 0) {
                    *((f32 *)&((CStruct *)var_r30)->unk0x0) = (f32) *((f32 *)&var_r29->unk0x4);
                    *((f32 *)&((CStruct *)var_r30)->unk0x4) = (f32) *((f32 *)&var_r29->unk0x8);
                    var_f0_2 = var_r29->unk0xC;
                } else {
                    *((f32 *)&((CStruct *)var_r30)->unk0x0) = (f32) ((f32) (f64) *(f32 *)((char *)var_r29 + (s32)0x2) * temp_f28);
                    *((f32 *)&((CStruct *)var_r30)->unk0x4) = (f32) ((f32) (f64) (s16) *((f32 *)&var_r29->unk0x4) * temp_f28);
                    var_f0_2 = (f32) (f64) *(f32 *)((char *)var_r29 + (s32)0x6) * temp_f28;
                }
                ((CStruct *)var_r30)->unk0x8 = var_f0_2;
                temp_f0_3 = *((f32 *)&((CStruct *)var_r30)->unk0x0);
                temp_f13_3 = *((f32 *)&((CStruct *)var_r30)->unk0x4);
                temp_f12_3 = ((CStruct *)var_r30)->unk0x8;
                var_f1_3 = ((temp_f27 - (temp_f0_3 * temp_f0_3)) - (temp_f13_3 * temp_f13_3)) - (temp_f12_3 * temp_f12_3);
                0;
                if (0 == 0) {
                    var_f1_3 = *(s32 *)&lbl_80291650;
                }
                var_f1_2 = sqrtf(var_f1_3);
                ((CStruct *)var_r30)->unk0xC = var_f1_2;
                var_r0 = var_r29->unk0x0;
block_30:
                if (var_r0 & 0x8000) {
                    ((CStruct *)var_r30)->unk0xC = (f32) -var_f1_2;
                }
            } else {
                *((f32 *)&sp8) = temp_f0;
                sp8.unk0x4 = temp_f0;
                0;
                sp8.unk0x8 = temp_f0;
                sp8.unk0xC = temp_f13_2;
                *((f32 *)&sp18) = temp_f0;
                sp18.unk0x8 = temp_f0;
                sp18.unk0xC = temp_f13_2;
                sp18.unk0x4 = temp_f0;
                if (temp_cr0_eq == 0) {
                    *((f32 *)&sp8) = *((f32 *)&var_r26->unk0x4);
                    spC = *((f32 *)&var_r26->unk0x8);
                    var_f0_3 = var_r26->unk0xC;
                } else {
                    *((f32 *)&sp8) = (f32) (f64) *(f32 *)((char *)var_r26 + (s32)0x2) * temp_f28;
                    spC = (f32) (f64) (s16) *((f32 *)&var_r26->unk0x4) * temp_f28;
                    var_f0_3 = (f32) (f64) *(f32 *)((char *)var_r26 + (s32)0x6) * temp_f28;
                }
                sp8.unk0x8 = var_f0_3;
                temp_f0_4 = sp8.unk0x0;
                temp_f13_4 = sp8.unk0x4;
                temp_f12_4 = sp8.unk0x8;
                var_f1_4 = ((temp_f27 - (temp_f0_4 * temp_f0_4)) - (temp_f13_4 * temp_f13_4)) - (temp_f12_4 * temp_f12_4);
                0;
                if (0 == 0) {
                    var_f1_4 = *(s32 *)&lbl_80291650;
                }
                temp_f1 = sqrtf(var_f1_4);
                sp8.unk0xC = temp_f1;
                temp_cr0_eq_2 = (var_r26->unk0x0 & 0x8000) == 0;
                if (temp_cr0_eq_2 == 0) {
                    sp8.unk0xC = (f32) -temp_f1;
                }
                if (temp_cr0_eq_2 == 0) {
                    *((f32 *)&sp18) = *((f32 *)&var_r29->unk0x4);
                    sp1C = *((f32 *)&var_r29->unk0x8);
                    var_f0_4 = var_r29->unk0xC;
                } else {
                    *((f32 *)&sp18) = (f32) (f64) *(f32 *)((char *)var_r29 + (s32)0x2) * temp_f28;
                    sp1C = (f32) (f64) (s16) *((f32 *)&var_r29->unk0x4) * temp_f28;
                    var_f0_4 = (f32) (f64) *(f32 *)((char *)var_r29 + (s32)0x6) * temp_f28;
                }
                sp20 = var_f0_4;
                var_f1_5 = ((temp_f27 - (*((f32 *)&sp18) * *((f32 *)&sp18))) - (sp1C * sp1C)) - (sp20 * sp20);
                0;
                if (0 == 0) {
                    var_f1_5 = *(s32 *)&lbl_80291650;
                }
                temp_f1_2 = sqrtf(var_f1_5);
                sp24 = temp_f1_2;
                if (var_r29->unk0x0 & 0x8000) {
                    sp24 = -temp_f1_2;
                }
                fn_80026140(&sp28, &sp8, &sp18, var_f25);
                0;
                0;
            }
            var_r8_2 = 0;
            if (temp_r3 > 0) {
                temp_r0_3 = temp_r3 - 1;
                if (temp_r0_3 == 0) {
                    var_r25 = var_r23;
                    var_r27 = var_r23;
                    var_f26 = *(s32 *)&lbl_80291650;
                } else {
loop_51:
                    temp_r0_4 = var_r8_2 * 8;
                    temp_r10_2 = temp_r0_4 + var_r23;
                    temp_f12_5 = (f32) (f64) *((s32 *)var_r23 + (s32)temp_r0_4);
                    0;
                    if ((0 == 0) || (0, (0 == 0))) {
                        var_r8_2 += 1;
                        if (var_r8_2 < temp_r3) {
                            if (var_r8_2 == temp_r0_3) {
                                var_f26 = *(s32 *)&lbl_80291650;
                                var_r27 = var_r23 + (var_r8_2 * 8);
                                var_r25 = var_r27;
                            } else {
                                goto loop_51;
                            }
                        }
                    } else {
                        var_r25 = temp_r10_2;
                        var_r27 = temp_r10_2 + 8;
                        var_f26 = (temp_f30 - temp_f12_5) / ((f32) (f64) *((f32 *)&((Unk_9994C3F5 *)temp_r10_2)->unk0x8) - temp_f12_5);
                    }
                }
            }
            temp_r3_3 = fn_80026AD4(arg0);
            if (var_f26 == *(s32 *)&lbl_80291650) {
                if (temp_r3_3 != 0) {
                    *((f32 *)&((CStruct *)var_r28)->unk0x0) = (f32) *((f32 *)&var_r25->unk0x4);
                    *((f32 *)&((CStruct *)var_r28)->unk0x4) = (f32) *((f32 *)&var_r25->unk0x8);
                    ((CStruct *)var_r28)->unk0xC = temp_f27;
                    *((f32 *)&((CStruct *)var_r28)->unk0x8) = (f32) *((f32 *)&var_r25->unk0xC);
                } else {
                    *((f32 *)&((CStruct *)var_r28)->unk0x0) = (f32) ((f32) (f64) *(f32 *)((char *)var_r25 + (s32)0x2) / temp_f29);
                    *((f32 *)&((CStruct *)var_r28)->unk0x4) = (f32) ((f32) (f64) (s16) *((f32 *)&var_r25->unk0x4) / temp_f29);
                    var_r0_2 = *(s32 *)((char *)var_r25 + (s32)0x6);
                    ((CStruct *)var_r28)->unk0xC = temp_f27;
                    goto block_64;
                }
            } else {
                temp_f12_6 = *(s32 *)&lbl_80291664;
                if (var_f26 == temp_f12_6) {
                    if (temp_r3_3 != 0) {
                        *((f32 *)&((CStruct *)var_r28)->unk0x0) = (f32) *((f32 *)&var_r27->unk0x4);
                        *((f32 *)&((CStruct *)var_r28)->unk0x4) = (f32) *((f32 *)&var_r27->unk0x8);
                        ((CStruct *)var_r28)->unk0xC = temp_f12_6;
                        *((f32 *)&((CStruct *)var_r28)->unk0x8) = (f32) *((f32 *)&var_r27->unk0xC);
                    } else {
                        *((f32 *)&((CStruct *)var_r28)->unk0x0) = (f32) ((f32) (f64) *(f32 *)((char *)var_r27 + (s32)0x2) / temp_f29);
                        *((f32 *)&((CStruct *)var_r28)->unk0x4) = (f32) ((f32) (f64) (s16) *((f32 *)&var_r27->unk0x4) / temp_f29);
                        var_r0_2 = *(s32 *)((char *)var_r27 + (s32)0x6);
                        ((CStruct *)var_r28)->unk0xC = temp_f12_6;
block_64:
                        *((f32 *)&((CStruct *)var_r28)->unk0x8) = (f32) ((f32) (f64) var_r0_2 / temp_f29);
                    }
                } else {
                    temp_cr0_eq_3 = temp_r3_3 == 0;
                    if (temp_cr0_eq_3 == 0) {
                        sp38 = *((f32 *)&var_r25->unk0x4);
                        sp3C = *((f32 *)&var_r25->unk0x8);
                        var_f0_5 = *((f32 *)&var_r25->unk0xC);
                        sp44 = temp_f12_6;
                    } else {
                        sp38 = (f32) (f64) *(f32 *)((char *)var_r25 + (s32)0x2) / temp_f29;
                        sp3C = (f32) (f64) (s16) *((f32 *)&var_r25->unk0x4) / temp_f29;
                        sp44 = temp_f12_6;
                        var_f0_5 = (f32) (f64) *(s32 *)((char *)var_r25 + (s32)0x6) / temp_f29;
                    }
                    sp40 = var_f0_5;
                    if (temp_cr0_eq_3 == 0) {
                        sp48 = *((f32 *)&var_r27->unk0x4);
                        sp4C = *((f32 *)&var_r27->unk0x8);
                        var_f0_6 = *((f32 *)&var_r27->unk0xC);
                        sp54 = temp_f27;
                    } else {
                        sp48 = (f32) (f64) *(f32 *)((char *)var_r27 + (s32)0x2) / temp_f29;
                        sp4C = (f32) (f64) (s16) *((f32 *)&var_r27->unk0x4) / temp_f29;
                        sp54 = temp_f27;
                        var_f0_6 = (f32) (f64) *(s32 *)((char *)var_r27 + (s32)0x6) / temp_f29;
                    }
                    sp50 = var_f0_6;
                    sp78 = var_f26;
                    fn_8002B8E4(&sp68);
                    0;
                    0;
                    0;
                    fn_8002B8E8(&sp58, &sp68);
                    0;
                    0;
                }
            }
            var_r23 += temp_r3 * 8;
            var_r31 = sp84;
            var_r22 += temp_r20 * 8;
            var_r30 = sp80;
            var_r28 += 0x10;
        } while (var_r31 < (s32) arg0->unk0x8);
    }
    0;
    return 1;
}
