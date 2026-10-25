// PARKED 2026-10-03 — base 3.8% (2424 B, 549 words).  Random-sample pick.
// m2c decode diverges from the first block; retained as the best guess.
// Not a candidate for the u32-switch recipe (want has no unsigned tree).
//
// family=m2c range=0x800ABD08-0x800AC680 size=2424B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.3% ([0]rev->4.3%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003ABA0(s32, s32);
// FLAG: -Os
extern char lbl_8037BC68[];
extern char lbl_8037BCB8[];
static s32 sp18;
static s32 sp78;
static s32 sp7C;
static s32 sp8;
static s32 M2C_CARRY = 0;

void fn_800723F0(s32, s32);
s32 fn_800ABB34(CStruct *, CStruct *, s32);
s32 fn_80128978(s32, s32);
s32 fn_8003AB44(s32, s32);
void fn_800AD750(s32, s32, s32);
s32 fn_800ABCA8(Unk_9B16FFA5 *, s32 *, s32);
s32 fn_8003EDD0(CStruct *o);
s32 GetFloat(CStruct *arg0, s32 arg1, f32 * arg2, s32 arg3);
void fn_800ABD08(Unk_9B16FFA5 *arg0) {
    s32 sp314;
    s32 sp310;
    s32 sp110;
    Unk_59AB5482 sp88;
    s32 sp84;
    s32 sp80;
    void *sp7C;
    void *sp78;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp20;
    s32 sp1C;
    void *sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 *sp8;
    f32 *var_r9;
    f32 temp_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r17;
    s32 temp_r20;
    s32 temp_r22;
    s32 temp_r23;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_6;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r9_4;
    s32 var_r19;
    s32 var_r26;
    s32 var_r26_2;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r30;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    void *temp_r14;
    void *temp_r16;
    void *temp_r24;
    void *temp_r25;
    CStruct *temp_r29;
    CStruct *temp_r3_4;
    void *temp_r3_5;
    void *temp_r3_7;

    sp314 = temp_r3;
    temp_r3 = fn_80013F8C(arg0->unk0x4);
    var_r19 = 0;
    if (temp_r3 > 0) {
        temp_f31 = *(f32 *)0x80298588;
        temp_r14 = (char *)arg0 + 0x2C5C;
        do {
            temp_r29 = fn_80013FA4(arg0->unk0x4, var_r19);
            temp_r9 = temp_r29->unk0xC;
            temp_r24 = fn_80013F94(arg0->unk0x4, var_r19);
            if (temp_r9 != QB_CIFSTRUCT) {
                if ((u32) temp_r9 <= QB_CIFSTRUCT) {
                    if (temp_r9 != QB_TEX) {
                        if ((u32) temp_r9 <= QB_TEX) {
                            switch (temp_r9) {      
                            case 0x5CA1497:         
                                temp_r3_2 = fn_800ABCA8(arg0, 0x80298578, temp_r29->unk0x8);
                                fn_800AC93C(arg0, temp_r3_2, temp_r24, temp_r29->unk0x4);
                                arg0->unk0xC = (s32) (arg0->unk0xC + 1);
                                if ((s32) arg0->unk0x10 == 0) {
                                    fn_800777F0(0x218);
                                    arg0->unk0x10 = fn_8006FAC8();
                                    fn_8006FB50(1);
                                }
                                if ((f32 *) arg0->unk0x20 == NULL) {
                                    arg0->unk0x20 = fn_8006FB8C(arg0->unk0x10, temp_r3_2);
                                    fn_8002AE94();
                                }
                                if ((f32 *) arg0->unk0x1C == NULL) {
                                    arg0->unk0x1C = (f32 *) arg0->unk0x20;
                                }
                                goto block_82;
                            }
                        } else if (temp_r9 != QB_WGT) {
                            if ((u32) temp_r9 <= QB_WGT) {
                                if (temp_r9 != QB_QB) {
                                    goto block_84;
                                }
                                if ((s32) arg0->unk0x34B8 != 0) {
                                    sprintf(&sp10, 0x8029854C, arg0->unk0x34BC);
                                    fn_8012EBC4(&sp10, temp_r24, 1, 0, 0);
                                }
                                goto block_82;
                            }
                            if (temp_r9 != QB_OBA) {
                                goto block_84;
                            }
                            temp_r3_3 = fn_800ABCA8(arg0, 0x80298570, temp_r29->unk0x8);
                            fn_800AC93C(arg0, temp_r3_3, temp_r24, temp_r29->unk0x4);
                            arg0->unk0x14 = (s32) (arg0->unk0x14 + 1);
                            if ((s32) arg0->unk0x18 == 0) {
                                fn_800777F0(0x218);
                                arg0->unk0x18 = fn_8006FAC8();
                                fn_8006FB50(1);
                            }
                            if ((f32 *) arg0->unk0x24 == NULL) {
                                arg0->unk0x24 = fn_8006FB8C(arg0->unk0x18, temp_r3_3);
                                fn_8002AE94();
                            }
                            goto block_82;
                        }
                    }
                } else if (temp_r9 != -QB_UNKNOWN_0x154AECBA) {
                    if ((u32) temp_r9 <= QB_SKA) {
                        switch (temp_r9) {          
                        case QB_CIF:            
                            CStruct_dtor(arg0->unk0x34D4);
                            fn_800AD750(arg0, arg0->unk0x34D4, temp_r24);
                            goto block_82;
                        }
                    } else if (temp_r9 != -QB_UNKNOWN_0x0279681F) {
                        if ((u32) temp_r9 <= QB_SKIN) {
                            if (temp_r9 != -QB_UNKNOWN_0x122728A1) {
                                goto block_84;
                            }
                            temp_r30 = temp_r29->unk0x8;
                            sp8 = NULL;
                            spC = 0;
                            fn_800F2384(*(s32 *)0x80301B48, temp_r30, 6, 0, temp_r24, temp_r29->unk0x4, 0, 1);
                            *((s32 *)temp_r14 + (arg0->unk0x345C * 4)) = temp_r30;
                            arg0->unk0x345C = (s32) (arg0->unk0x345C + 1);
                            goto block_83;
                        }
                        if (temp_r9 != -0x3AD60C) {
block_84:
                            fn_80014070(arg0->unk0x4, temp_r29->unk0x8, temp_r29->unk0xC);
                        }
                    } else {
                        sprintf(&sp110, 0x80298580, temp_r29->unk0x8 + temp_r29->unk0xC);
                        temp_r20 = *((char *)&temp_r29->unk0x8) + QB_SKIN;
                        fn_800F5758(&sp10);
                        temp_r16 = fn_80014004(arg0->unk0x4, temp_r29->unk0x8, QB_TEX, 1);
                        temp_r3_4 = fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8, QB_TEX, 1);
                        temp_r9_2 = temp_r3_4->unk0xC;
                        temp_r0 = temp_r3_4->unk0x8;
                        temp_r17 = temp_r3_4->unk0x4;
                        sp18 = NULL;
                        temp_r23 = temp_r0 + temp_r9_2;
                        sp1C = 0;
                        sp10 = 0;
                        temp_r0_2 = temp_r29->unk0xC ^ QB_SKIN;
                        sp20 = (0 - temp_r0_2) + temp_r0_2 + M2C_CARRY;
                        if ((s32) temp_r29->unk0xC == -QB_UNKNOWN_0x18CF73E1) {
                            sp14 = 0;
                        } else {
                            sp14 = var_r19 + 0xC8;
                        }
                        sp2C = sp14;
                        sp30 = sp20;
                        sp28 = 0;
                        sp34 = 0;
                        temp_r22 = *(s32 *)0x80301B48;
                        0;
                        var_r30 = ((u32) 0 >> 2U) & 1;
                        temp_r3_5 = fn_80014004(arg0->unk0x4, temp_r29->unk0x8, QB_WGT, 0);
                        if (temp_r3_5 != NULL) {
                            var_r28 = fn_8003ABA0(arg0->unk0x34B0, QB_SKATER_M_HEAD);
                            if (var_r28 == 0) {
                                var_r28 = fn_8003ABA0(arg0->unk0x34B0, QB_SKATER_F_HEAD);
                            }
                            var_r26 = fn_8003AB44(arg0->unk0x34B0, QB_SKATER_M_HEAD);
                            if (var_r26 == 0) {
                                var_r26 = fn_8003AB44(arg0->unk0x34B0, QB_SKATER_F_HEAD);
                            }
                            *((f32 *)&sp88) = temp_f31;
                            sp88.unk0x4 = temp_f31;
                            sp88.unk0x8 = temp_f31;
                            sp88.unk0xC = temp_f31;
                            0;
                            0;
                            if (fn_80128978(var_r28, QB_HEAD_BONE_GROUP) != 0) {
                                var_r4 = var_r28;
                            } else {
                                var_r4 = var_r26;
                            }
                            fn_800ABB34(&sp88, var_r4, QB_HEAD_BONE_GROUP);
                            0;
                            0;
                            if (fn_80128978(var_r28, QB_HEADTOP_BONE_GROUP) != 0) {
                                var_r4_2 = var_r28;
                            } else {
                                var_r4_2 = var_r26;
                            }
                            fn_800ABB34(&sp88, var_r4_2, QB_HEADTOP_BONE_GROUP);
                            0;
                            0;
                            if (fn_80128978(var_r28, QB_NOSE_BONE_GROUP) != 0) {
                                var_r4_3 = var_r28;
                            } else {
                                var_r4_3 = var_r26;
                            }
                            fn_800ABB34(&sp88, var_r4_3, QB_NOSE_BONE_GROUP);
                            0;
                            0;
                            if (fn_80128978(var_r28, QB_JAW_BONE_GROUP) != 0) {
                                var_r4_4 = var_r28;
                            } else {
                                var_r4_4 = var_r26;
                            }
                            fn_800ABB34(&sp88, var_r4_4, QB_JAW_BONE_GROUP);
                            0;
                            0;
                            temp_r25 = temp_r3_5 + 4 + 4;
                            sp80 = (s32)lbl_8037BC68;
                            sp84 = (s32)lbl_8037BCB8;
                            sp7C = temp_r25;
                            var_r26_2 = 0;
                            var_r27 = 0;
                            sp78 = temp_r25 + (((CStruct *)temp_r3_5)->unk0x4 * 0xC);
                            if (fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8 + 1, QB_SKIN, 0) == NULL) {
                                var_r27 = 1;
                            } else if (fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8 + 2, QB_SKIN, 0) == NULL) {
                                var_r27 = 0;
                            } else if (fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8 + 3, QB_SKIN, 0) == NULL) {
                                var_r26_2 = 1;
                                var_r27 = 1;
                            } else if (fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8 + 4, QB_SKIN, 0) == NULL) {
                                var_r26_2 = 1;
                            }
                            var_r28_2 = 0;
                            temp_r3_6 = fn_8003AE20(arg0->unk0x34B0);
                            if ((temp_r3_6 != 0) && (fn_8003EDD0(temp_r3_6) != 0)) {
                                var_r28_2 = 1;
                            }
                            var_r30 = 0;
                            GetInteger(arg0->unk0x34B4, QB_IS_MALE, &sp310, 1);
                            if (var_r27 == var_r28_2) {
                                temp_r30_2 = var_r26_2 ^ sp310;
                                var_r30 = (0 - temp_r30_2) + temp_r30_2 + M2C_CARRY;
                            }
                            if (var_r30 != 0) {
                                fn_800554AC(&sp78);
                                goto block_74;
                            }
                        } else {
block_74:
                            if (var_r30 != 0) {
                                temp_r3_7 = fn_80014004(arg0->unk0x4, temp_r29->unk0x8, QB_CAS, 0);
                                sp18 = temp_r3_7;
                                if (temp_r3_7 != NULL) {
                                    sp1C = *(char *)((s32 *)(fn_80013FB4(arg0->unk0x4, temp_r29->unk0x8, QB_CAS, 1)) + 0x4);
                                }
                                sp8 = &sp28;
                                spC = 0;
                                fn_800F2384(temp_r22, temp_r23, 3, 0, temp_r16, temp_r17, 0, 1);
                                sp8 = &sp10;
                                spC = 0;
                                fn_800F2384(temp_r22, temp_r20, 7, temp_r23, temp_r24, temp_r29->unk0x4, 0, 1);
                                temp_r9_3 = arg0->unk0x345C;
                                *((s32 *)temp_r14 + (temp_r9_3 * 4)) = temp_r20;
                                temp_r9_4 = temp_r9_3 + 1;
                                arg0->unk0x345C = temp_r9_4;
                                *((s32 *)temp_r14 + (temp_r9_4 * 4)) = temp_r23;
                                arg0->unk0x345C = (s32) (temp_r9_4 + 1);
                            }
                        }
                        fn_80014070(arg0->unk0x4, temp_r29->unk0x8, temp_r29->unk0xC);
                        fn_80014070(arg0->unk0x4, temp_r29->unk0x8, QB_TEX);
                        fn_80014070(arg0->unk0x4, temp_r29->unk0x8, -0x3AD60C);
                        fn_80014070(arg0->unk0x4, temp_r29->unk0x8, QB_WGT);
                    }
                } else {
                    fn_800AC9B4(arg0, temp_r29->unk0x8, temp_r24, temp_r29->unk0x4);
                    goto block_82;
                }
            } else {
                CStruct_dtor(arg0->unk0x34D4);
                fn_80129EA0(arg0, arg0->unk0x34D4, temp_r24);
block_82:
block_83:
                fn_80014070(arg0->unk0x4, temp_r29->unk0x8, temp_r29->unk0xC);
            }
            var_r19 += 1;
        } while (var_r19 < sp314);
    }
    if (GetFloat(arg0->unk0x34D4, QB_CAMANIMDURATION, (char *)arg0 + 0x3474, 0) == 0) {
        if ((s32) arg0->unk0x34B8 != 0) {
            var_r9 = arg0->unk0x20;
        } else {
            var_r9 = arg0->unk0x24;
        }
        arg0->unk0x3474 = (f32) *((s32 *)var_r9);
    }
    fn_800723F0(0, 0);
}
