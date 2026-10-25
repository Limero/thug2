// PARKED 2026-10-03 — base 5.7% (2852 B, 736 words).  Random-sample pick.
// Large function; the m2c decode diverges early and the residual is not a
// local tweak.  Needs a from-scratch rebuild like fn_8000F68C got, not a
// sweep.  No u32-switch tree present, so recipe 7w does not apply.
//
// family=m2c range=0x800ACC2C-0x800AD750 size=2852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 8.0% ([10]rev->8.0%).
#include "types.h"
extern f32 lbl_80298594;
extern f32 lbl_80298598;
extern f32 lbl_802985A8;
#include "qb_constants.h"
#include "structs.h"
s32 fn_800ACBB8(s32, s32, s32);
s32 CStruct_delete(CStruct *, void *);
s32 fn_8006FB8C(CStruct *, void *);
s32 fn_8006FB50(Unk_5E1C040A *, void *);
s32 fn_80128C80(CStruct *, void *, void *, void *);
s32 fn_800ACA28(Unk_6849630D *, void *);
s32 fn_8003AB44(void *, void *);
s32 fn_800B48AC(CScript *);
s32 fn_800626E8(void *, Unk_C7387A53 *);
s32 fn_80060E4C(Unk_C7387A53 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 Script_RunScript(void *, void *, void *, void *, void *);
s32 ContainsFlag(CStruct *, void *);
static s32 M2C_CARRY = 0;
static s32 sp1C;

void *fn_800ACC2C(Unk_DF035CC0 *arg0, CStruct *arg1) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    void *sp1C;
    s32 sp18;
    Unk_59AB5482 sp8;
    s32 var_r27_2;
    s32 var_r29_3;
    s32 var_r30_2;
    s32 var_r31_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    s32 temp_r23;
    s32 temp_r25;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r29_4;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_3;
    s32 temp_r30_4;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r9_2;
    s32 var_cr0_eq;
    s32 var_r19;
    s32 var_r20;
    s32 var_r23;
    s32 var_r24;
    s32 var_r24_2;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30_3;
    s32 var_r31_2;
    s32 var_r3_2;
    u32 var_r21;
    Unk_DB0E2BAB *temp_r25_2;
    Unk_DB0E2BAB *temp_r27;
    Unk_C7387A53 *temp_r29_3;
    void *temp_r3_3;
    CScript *temp_r3_4;
    Unk_C8FEE62D *temp_r3_5;
    Unk_C8FEE62D *temp_r3_6;
    void *temp_r3_7;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_3;
    void *var_r30;
    void *var_r31;
    Unk_F8D48A89 *var_r3;

    sp18 = 0;
    var_r20 = 0;
    GetInteger(arg1, QB_VERSION, &sp18, 1);
    var_r19 = 0;
    sp1C = NULL;
    var_r3 = GetArray(arg1, QB_OBJECTS, &sp1C, 1);
    var_r21 = 0U;
    if ((u32) *((u32 *)&((CStruct *)sp1C)->unk0x4) > 0U) {
        do {
            var_r23 = 0;
            temp_r30 = fn_80129528(sp1C, var_r21);
            CStruct_new(8);
            temp_r25 = CStruct_ctor();
            sp30 = 0;
            sp20 = 0;
            sp24 = 0;
            sp2C = 0;
            sp28 = 0;
            if (sp18 > 1) {
                GetChecksum_2(temp_r30, QB_OBJECTNAME, &sp20, 1);
                GetChecksum_2(temp_r30, QB_TYPE, &sp24, 1);
                GetChecksum_2(temp_r30, QB_SKELETONNAME, &sp28, 0);
                sp30 = sp20;
                var_r24 = sp20 + QB_SKIN;
                sp2C = sp20;
                var_r27 = ContainsFlag(temp_r30, QB_ISHEADMODEL);
                temp_r29 = sp24 ^ QB_PLAYEROBJECT;
                var_r29 = (0 - temp_r29) + temp_r29 + M2C_CARRY;
                if (var_r27 != 0) {
                    temp_r29_2 = sp24 ^ QB_EXTERNALPLAYERHEAD;
                    var_r29 = (0 - temp_r29_2) + temp_r29_2 + M2C_CARRY;
                    var_cr0_eq = var_r29 == 0;
                    if (var_cr0_eq == 0) {
                        sp28 = QB_HEAD_CAS_MALE01;
                        goto block_11;
                    }
                } else {
                    var_r23 = var_r29;
                    var_cr0_eq = var_r23 == 0;
                    if (var_cr0_eq == 0) {
                        var_r19 = 1;
                        sp28 = QB_THPS6_HUMAN;
                        goto block_11;
                    }
                }
            } else {
                GetChecksum_2(temp_r30, QB_OBJECTNAME, &sp20, 1);
                GetChecksum_2(temp_r30, QB_MODELNAME, &sp2C, 1);
                var_r24 = sp2C + QB_SKIN;
                GetChecksum_2(temp_r30, QB_SKELETONNAME, &sp28, 1);
                GetChecksum_2(temp_r30, QB_ANIMNAME, &sp30, 1);
                var_r27 = ContainsFlag(temp_r30, QB_ISHEADMODEL);
                var_r29 = ContainsFlag(temp_r30, QB_ISPLAYERMODEL);
                if ((sp2C == QB_SKATER) || (sp2C == QB_PLAYER)) {
                    var_r23 = 1;
                }
block_11:
                var_cr0_eq = var_r29 == 0;
                if (var_cr0_eq == 0) {
                    var_cr0_eq = var_r27 == 0;
                    if (var_cr0_eq == 0) {
                        var_r20 = 1;
                    }
                }
            }
            0;
            0;
            var_r3 = *(void **)0x80301B48;
            0;
            if (var_cr0_eq != 0) {
                var_r3 = fn_800F2AD8(var_r24, 0);
                if ((var_r3 == NULL) && ((var_r29 == 0) || (var_r27 == 0))) {
                    var_r3 = AddChecksum(temp_r25, 0, QB_CUTSCENEDUMMY);
                }
                0;
                if (0) {
                    goto block_20;
                }
                if (ContainsFlag(temp_r30, QB_ISSKINNEDMODEL) == 0) {
                    sp28 = var_r23;
                    sp30 = var_r23;
                } else {
                    AddChecksum(temp_r25, 0, QB_ISSKINNEDMODEL);
                }
                0;
                if ((var_r27 != 0) && (var_r29 != 0)) {
                    temp_r3 = fn_8003AE20(arg0->unk0x34B0);
                    if ((temp_r3 != 0) && (fn_8003EDD0(temp_r3) != 0)) {
                        var_r24 += 1;
                    }
                    sp34 = 0;
                    GetInteger(arg0->unk0x34B4, QB_IS_MALE, &sp34, 1);
                    if (sp34 == 0) {
                        var_r24 += 2;
                    }
                    AddInteger(temp_r25, QB_MULTICOLOR);
                }
                AddChecksum(temp_r25, QB_ASSETNAME, var_r24);
                goto block_34;
            }
block_20:
            if ((s32) arg0->unk0x34B8 != 0) {
                AddChecksum(temp_r25, QB_REFOBJECTNAME, 0);
                0;
block_34:
                0;
                if (0 && (var_r29 != 0) && ((((var_r3_2 = fn_8003AB44(arg0->unk0x34B0, QB_SKATER_M_HEAD), ((var_r3_2 == 0) == 0)) || (var_r3_2 = fn_8003AB44(arg0->unk0x34B0, QB_SKATER_F_HEAD), ((var_r3_2 == 0) == 0))) && (var_r3 = ContainsFlag(var_r3_2, QB_NOCUTSCENEHEAD), ((var_r3 == NULL) == 0))) || ((temp_r3_2 = fn_8003AB44(arg0->unk0x34B0, QB_HAT), ((temp_r3_2 == 0) == 0)) && (var_r3 = ContainsFlag(temp_r3_2, QB_NOCUTSCENEHEAD), ((var_r3 == NULL) == 0))))) {
                    var_r20 = 0;
                    goto block_42;
                }
                if (sp28 != 0) {
                    AddChecksum(temp_r25, QB_SKELETONNAME);
                    AddInteger(temp_r25, QB_MAX_BONE_SKIP_LOD, 0);
                }
                temp_r3_3 = GetChecksum_3(QB_MODEL);
                temp_r27->unk0x14 = fn_800ACAB0(arg0, temp_r25);
                temp_r27 = (char *)arg0 + ((arg0->unk0x2054 << 5) + 0x54);
                if (temp_r3_3 != NULL) {
                    temp_f31 = lbl_80298594;
                    temp_f30 = lbl_80298598;
                    *((f32 *)&sp8) = temp_f31;
                    sp8.unk0x4 = temp_f31;
                    sp8.unk0x8 = temp_f31;
                    sp8.unk0xC = temp_f30;
                    fn_80062774(((Unk_377910A3 *)temp_r3_3)->unk0x210, &sp8);
                    if ((s32) ((Unk_377910A3 *)temp_r3_3)->unk0x23C != 0) {
                        fn_800B6570(temp_r3_3);
                        fn_8009F498();
                        temp_r3_4 = GetChecksum_3(QB_MODEL);
                        temp_r29_3 = temp_r3_4->unk0x210;
                        if ((s32) arg0->unk0x50 == 0) {
                            fn_800626E8(&sp8, temp_r29_3);
                            0;
                            arg0->unk0x38 = (s32) (((u32) temp_r29_3->unk0x48 >> 0x1DU) & 1);
                            arg0->unk0x3C = (s32) (((u32) temp_r29_3->unk0x48 >> 0x1CU) & 1);
                            0;
                            0;
                            arg0->unk0x50 = 1;
                        }
                        *((f32 *)&sp8) = temp_f31;
                        sp8.unk0x8 = temp_f31;
                        sp8.unk0xC = temp_f30;
                        sp8.unk0x4 = temp_f31;
                        fn_80062774(temp_r29_3, &sp8);
                        fn_80060E4C(temp_r29_3, 0);
                        fn_80062584(temp_r29_3, 0);
                        temp_r30_2 = fn_800602E4(temp_r29_3);
                        fn_80060264(temp_r29_3, fn_800602E4(((Unk_377910A3 *)temp_r3_3)->unk0x210));
                        fn_80060264(((Unk_377910A3 *)temp_r3_3)->unk0x210, temp_r30_2);
                        fn_800B48AC(temp_r3_4);
                    }
                    temp_r9 = ((Unk_377910A3 *)temp_r3_3)->unk0x18;
                    ((s32 (*)(void *, s32))temp_r9->unk0x44)(temp_r3_3 + temp_r9->unk0x40, 1);
                }
                temp_r27->unk0x0 = sp20;
                var_r3 = fn_8009E1F0(arg0, temp_r27->unk0x14, sp20);
                temp_r27->unk0xC = var_r23;
                temp_r27->unk0x4 = sp28;
                temp_r27->unk0x1C = -1;
                temp_r27->unk0x10 = NULL;
                temp_r27->unk0x18 = 0;
                if (sp30 != 0) {
                    var_r3 = fn_800ACA6C(arg0);
                    if (var_r3 != NULL) {
                        temp_r27->unk0x10 = var_r3;
                        fn_800777F0(0x218);
                        var_r3->unk0x4 = fn_8006FAC8();
                        fn_8006FB8C(*(s32 *)(*(s32 *)((char *)((char *)temp_r27) + 0x10) + 0x4), sp30);
                        var_r3 = fn_8006FB50(*(s32 *)(*(s32 *)((char *)((char *)temp_r27) + 0x10) + 0x4), 1);
                    }
                }
                arg0->unk0x2054 = (s32) (arg0->unk0x2054 + 1);
                if (temp_r25 != 0) {
                    var_r3 = CStruct_delete(temp_r25, 3);
                }
            } else {
block_42:
                if (temp_r25 != 0) {
                    var_r3 = CStruct_delete(temp_r25, 3);
                }
            }
            var_r21 += 1;
        } while (var_r21 < (u32) *((u32 *)&((CStruct *)sp1C)->unk0x4));
    }
    if ((var_r19 != 0) && (var_r20 == 0)) {
        var_r3 = Script_RunScript(QB_UNHIDELORESHEADS, 0, 0, 0, 0);
    }
    var_r29_2 = 0;
    if ((s32) arg0->unk0x2054 > 0) {
        var_r31 = (char *)arg0 + 0x54;
        do {
            if ((s32) ((Unk_DB0E2BAB *)var_r31)->unk0xC != 0) {
                GetChecksum_3(((Unk_DB0E2BAB *)var_r31)->unk0x14, QB_MODEL);
                fn_800B6570();
                fn_8009F498();
                GetChecksum_3(QB_SKELETON);
                temp_r30_3 = ((Unk_DB0E2BAB *)var_r31)->unk0x14;
                fn_800ACBB8(arg0, temp_r30_3, fn_800C9780());
            }
            var_r3 = fn_800ACA28(arg0, ((Unk_DB0E2BAB *)var_r31)->unk0x0 - 1);
            if ((var_r3 != NULL) && ((s32) var_r3->unk0xC != 0)) {
                GetChecksum_3(var_r3->unk0x14, QB_MODEL);
                fn_800B6570(arg0);
                fn_8009F498(arg0, arg1);
                GetChecksum_3(QB_SKELETON);
                temp_r30_4 = ((Unk_DB0E2BAB *)var_r31)->unk0x14;
                var_r3 = fn_800ACBB8(arg0, temp_r30_4, fn_800C9780());
            }
            var_r29_2 += 1;
            var_r31 += 0x20;
        } while (var_r29_2 < (s32) arg0->unk0x2054);
    }
    var_r28 = 0;
    if (arg0->unk0x2054 > 0) {
        var_r30 = (char *)arg0 + 0x54;
        do {
            var_r3 = GetChecksum_3(((Unk_DB0E2BAB *)var_r30)->unk0x14, QB_MODEL);
            if (var_r3 != NULL) {
                temp_r29_4 = var_r3->unk0x210;
                var_r31_2 = fn_80060BB0(temp_r29_4);
                temp_r3_5 = fn_800ACA28(arg0, ((Unk_DB0E2BAB *)var_r30)->unk0x0 - 1);
                if ((temp_r3_5 != NULL) && ((s32) temp_r3_5->unk0xC != 0)) {
                    GetChecksum_3(temp_r3_5->unk0x14, QB_MODEL);
                    fn_800B6570();
                    fn_8009F498(arg0, arg1, arg0, arg1);
                    var_r31_2 |= fn_80060BB0(*(s32 *)((s32 *)(GetChecksum_3(QB_MODEL)) + 0x210));
                }
                var_r3 = fn_80060C60(temp_r29_4, var_r31_2);
            }
            var_r28 += 1;
            var_r30 += 0x20;
        } while (var_r28 < (s32) arg0->unk0x2054);
    }
    var_r24_2 = 0;
    if (arg0->unk0x2054 > 0) {
        temp_f30_2 = lbl_802985A8;
        do {
            temp_r9_2 = (var_r24_2 << 5) + 0x54;
            temp_r25_2 = (char *)arg0 + temp_r9_2;
            temp_r3_6 = fn_800ACA28(arg0, *((s32 *)arg0 + (s32)temp_r9_2) - 1);
            if (temp_r3_6 != NULL) {
                temp_r25_2->unk0x18 = (s32) temp_r3_6->unk0x14;
                if (((s32) temp_r3_6->unk0xC != 0) && ((temp_r3_7 = GetChecksum_3(temp_r25_2->unk0x14, QB_MODEL), var_r27_2 = QB_SKATER_M_HEAD, temp_r9_3 = ((CScript *)temp_r3_7)->unk0x18, ((s32 (*)(void *, void *, s32, s32, s32))temp_r9_3->unk0x74)(temp_r3_7 + temp_r9_3->unk0x70, arg0->unk0x34B0, 0, 0, QB_REPLACE_CUTSCENE_SKATER_FROM_APPEARANCE), var_r28_2 = fn_8003ABA0(arg0->unk0x34B0, QB_SKATER_M_HEAD), ((var_r28_2 == 0) == 0)) || (var_r27_2 = QB_SKATER_F_HEAD, var_r28_2 = fn_8003ABA0(arg0->unk0x34B0, QB_SKATER_F_HEAD), ((var_r28_2 == 0) == 0)))) {
                    temp_r23 = ((CScript *)temp_r3_7)->unk0x210;
                    sp38 = 1;
                    GetInteger(var_r28_2, QB_USE_DEFAULT_HSV, &sp38, 0);
                    var_r30_2 = QB_H;
                    var_r29_3 = QB_S;
                    var_r31_3 = QB_V;
                    if (sp38 != 0) {
                        var_r28_2 = fn_8003AB44(arg0->unk0x34B0, var_r27_2);
                        var_r30_2 = QB_DEFAULT_H;
                        var_r29_3 = QB_DEFAULT_S;
                        var_r31_3 = QB_DEFAULT_V;
                    }
                    if ((fn_80128C80(var_r28_2, var_r30_2, &sp3C, 0) != 0) && (fn_80128C80(var_r28_2, var_r29_3, &sp40, 0) != 0) && (fn_80128C80(var_r28_2, var_r31_3, &sp44, 0) != 0)) {
                        CStruct_new(8);
                        temp_r31 = CStruct_ctor();
                        AddChecksum(QB_PART, 0);
                        AddChecksum(temp_r31, QB_MATERIAL, QB_CASHEAD_HEAD);
                        AddInteger(temp_r31, QB_PASS, 0);
                        fn_80061720(temp_r23, temp_r31, (f32) (f64) sp3C, (f32) (f64) sp40 / temp_f30_2, (f32) (f64) sp44 / temp_f30_2);
                        if (temp_r31 != 0) {
                            CStruct_delete(temp_r31, 3);
                        }
                    }
                }
            }
            var_r30_3 = 0;
loop_92:
            var_r3 = arg0->unk0x24;
            if (var_r30_3 < (s32) var_r3->unk0x8) {
                var_r3 = fn_8002AE6C(var_r30_3);
                if ((s32) temp_r25_2->unk0x0 == var_r3) {
                    temp_r25_2->unk0x1C = var_r30_3;
                } else {
                    var_r30_3 += 1;
                    goto loop_92;
                }
            }
            var_r24_2 += 1;
        } while (var_r24_2 < (s32) arg0->unk0x2054);
    }
    return var_r3;
}