// WIP DRAFT — decode-documented park (groupB PS zone, 2026-08-25)
// PARKED (m2c husk retained; hand rebuild not completed).
// 1172B (293 insns), frame 0x158, saves f30/f31 + r28-r31. 3-ARG!
//   (r31=r3 obj, r30=r4, r29=r5 — m2c husk likely has wrong arity).
// Family template: addi r3,r1,8; bl fn_8010794C(desc); pair copies from
// *arg1/+arg2 into desc; fn_80107B20(desc,1,0)==0 -> node-cleanup tail;
// else lhz 0x58(desc) bit-test andi. 2 -> big PS branch: consts at
// lbl_802AF5D0/AFA region (-0xa30/-0xa2c), out-param struct at spA0/spC8,
// ~18 calls, 29 op4 words all standard emittable PS, 73 psq pairs.
// Node cleanup: CObject_RemoveRefLink(*(0xb0),&0xb0); store r30(NULL result).
// Walls: standard zone allocator/scheduler classes.
// family=m2c range=0x80210F58-0x802113EC size=1172B
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.0% ([5]rev->2.0%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF5D0;
extern char lbl_802AF5D4[];
extern f32 lbl_802AF5D8;
extern char lbl_802AF5DC[];
extern char lbl_80303150[];
static s32 sp118;
static s32 sp120;

void fn_80210F58(Unk_F6E1C63B *arg0, void *arg1, s32 arg2) {
    f32 sp110;
    f32 sp108;
    f32 sp100;
    f32 spF8;
    s32 spC8;
    s32 spB0;
    s32 spA0;
    Unk_669274FE sp8;
    s32 *temp_r29_2;
    s32 *temp_r30_2;
    f32 temp_f0;
    f32 temp_f30;
    s32 temp_r29;
    s32 temp_r3;
    s32 var_cr0_eq;
    s32 var_r11;
    Unk_C8FEE62D *temp_r28;
    void *temp_r30;
    CStruct *temp_r30_3;
    CStruct *temp_r9;

    fn_8010794C(&sp8);
    0;
    0;
    0;
    temp_r3 = fn_80107B20(&sp8, 1, 0);
    if (temp_r3 == 0) {
        if (spB0 != 0) {
            CObject_RemoveRefLink(arg0);
            spB0 = temp_r3;
        }
    } else {
        temp_r29 = sp8.unk0x58 & 2;
        if (temp_r29 != 0) {
            sp100 = lbl_802AF5D0;
            sp108 = *(f32 *)&lbl_802AF5D4 - sp8.unk0x80;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
            fn_80005854(arg0, arg1, arg2, &spC8, &spA0);
            0;
            0;
            0;
            0;
            0;
            if (fn_80107B20(&sp8, 1, 0) != 0) {
                sp110 = lbl_802AF5D8;
                0;
                0;
                0;
                0;
            } else {
                0;
            }
            var_cr0_eq = spB0 == 0;
            goto block_27;
        }
        arg0->unk0x48 = (f32) *(f32 *)&lbl_802AF5DC;
        temp_r30 = (char *)arg0 + 0x1880;
        0;
        fn_8020D2E4(arg0, 0);
        fn_800C9350(temp_r30, &sp8);
        arg0->unk0x1940 = 1;
        fn_800DF004(arg0->unk0x1848, 0x802AF814, temp_r30);
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) != 0) {
            if (spB0 != 0) {
                CObject_RemoveRefLink();
                spB0 = temp_r29;
            }
        } else {
            0;
            0;
            fn_800EB67C(arg0->unk0x1850, &sp8);
            temp_r28 = arg0->unk0x1850;
            temp_r30_2 = temp_r28->unk0x1C;
            if (temp_r30_2 == NULL) {
                var_r11 = 0;
            } else {
                temp_r29_2 = *((s32 *)temp_r30_2);
                if (temp_r29_2 != NULL) {
                    var_r11 = 1;
                } else {
                    temp_r28->unk0x70 = temp_r29_2;
                    if ((s32 *) *((s32 *)temp_r30_2) != NULL) {
                        CObject_RemoveRefLink(temp_r30_2);
                        *((s32 *)temp_r30_2) = temp_r29_2;
                    }
                    Mem_Free(temp_r30_2);
                    temp_r28->unk0x1C = temp_r29_2;
                    var_r11 = 0;
                    temp_r28->unk0x74 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
                }
            }
            if (var_r11 != 0) {
                0;
                0;
                arg0->unk0x3C = (f32) *(s32 *)&lbl_802AF5DC;
                0;
                0;
            }
            temp_r30_3 = (char *)arg0 + 0x38;
            0;
            temp_f30 = *(s32 *)&lbl_802AF5DC;
            0;
            if (sp118 > temp_f30) {
                fn_80005A90(temp_r30_3);
                if (arg0->unk0xA0 == temp_f30) {
                    0;
                    0;
                    GetStructure(QB_WALK_PARAMETERS, 0);
                    GetFloat(QB_STICKY_LAND_THRESHOLD_SPEED, &spF8, 1);
                    if (sp120 < spF8) {
                        arg0->unk0x38 = temp_f30;
                        *((f32 *)&temp_r30_3->unk0xC) = (f32) *(s32 *)&lbl_802AF5D4;
                        temp_r30_3->unk0x8 = temp_f30;
                        goto block_25;
                    }
                }
            } else {
                arg0->unk0x38 = temp_f30;
                temp_r30_3->unk0x8 = temp_f30;
                *((f32 *)&temp_r30_3->unk0xC) = (f32) *(s32 *)&lbl_802AF5D4;
block_25:
                temp_r30_3->unk0x4 = temp_f30;
            }
            arg0->unk0x7D8 = temp_f0;
            temp_r9 = (char *)arg0 + 0x7D8;
            temp_f0 = *(s32 *)&lbl_802AF5DC;
            *((f32 *)&temp_r9->unk0xC) = (f32) *(s32 *)&lbl_802AF5D4;
            temp_r9->unk0x8 = temp_f0;
            temp_r9->unk0x4 = temp_f0;
            fn_800AA074(arg0->unk0x183C + 0x1FC);
            var_cr0_eq = spB0 == 0;
            arg0->unk0x80 = QB_LAND;
block_27:
            if (var_cr0_eq == 0) {
                CObject_RemoveRefLink(arg0);
                spB0 = 0;
            }
        }
    }
}
