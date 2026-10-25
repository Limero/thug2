// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801931EC-0x80193678 (1164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802A9CF8;
extern f32 lbl_802A9CFC;
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_8019519C(Unk_C7387A53 * arg0);
extern s32 fn_80195214(Unk_C7387A53 * arg0);
extern s32 fn_80195068(void *arg0);
extern s32 Game_GetGoalManager(void);
extern s32 fn_8018E24C(Unk_C7387A53 * arg0);
extern s32 fn_80183D68(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_80194DD4(Unk_C7387A53 * arg0);
extern f32 fn_800144C8(void);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern void fn_801937EC(Unk_C19E9EA6 * arg0, s32 arg1);
extern s32 fn_80195124(Unk_C7387A53 * arg0);
extern s32 fn_8018CD64(Unk_C8FEE62D * arg0);

s32 fn_801931EC(Unk_9AA32608 *arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r3;
    void *temp_p;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r30;
    s32 var_r4;
    s32 var_ctr;
    char *var_r9;
    Unk_89391A04 *temp_r9;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_WAIT_TO_ADD_TRICKS, &sp8, 0);
    if (sp8 == 0) {
        spC = 1;
        if ((fn_8019519C(arg0) == 0) && (GetInteger(arg0->unk0x20, QB_TIME_TO_STOP_ADDING_TRICKS, &spC, 0) != 0)) {
            spC *= 0x3E8;
        }
        if (fn_80195214(arg0) != 0) {
            temp_r9 = arg0->unk0x14;
            if (temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20) != 0) {
                temp_r9 = arg0->unk0x14;
                temp_r0 = (s32)temp_r9->unk0x9C;
                temp_p = (void *)(((s32 (*)(void *))(void *)temp_r0)((char *)arg0 + temp_r9->unk0x98));
                if (temp_p == NULL) {
                    sp10 = (s32)temp_p;
                    GetInteger(arg0->unk0x20, QB_TRICKS_COMPLETED, &sp10, 0);
                    GetInteger(arg0->unk0x20, QB_TRICKTRIS_TOTAL_TO_WIN, &sp14, 1);
                    if (sp10 < sp14) {
                        goto block_14;
                    }
                    goto block_13;
                }
            }
            goto block_14;
        }
        temp_r9 = arg0->unk0x14;
        if ((temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20) != 0) && (arg0->unk0x54 < spC)) {
            temp_r9 = arg0->unk0x14;
            if ((temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98) == 0) && (fn_80195068(arg0) != 0)) {
block_13:
                temp_r3 = Game_GetGoalManager();
                fn_80183D68(temp_r3, fn_8018E24C(arg0));
                return 1;
            }
        }
block_14:
        temp_r9 = arg0->unk0x14;
        if (temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20) != 0) {
            temp_r9 = arg0->unk0x14;
            if (temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98) == 0) {
                fn_80194DD4(arg0);
            }
        }
        if (fn_80195214(arg0) != 0) {
            if (!(arg0->unk0x70 & 0x80000)) {
                if (!((f32)(f64)(arg0->unk0x54) > lbl_802A9CF8)) {
                    goto tail;
                }
            }
                temp_r9 = arg0->unk0x14;
                temp_r3_2 = temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98);
                if (temp_r3_2 == 0) {
                    sp18 = temp_r3_2;
                    GetInteger(arg0->unk0x20, QB_TRICKS_COMPLETED, &sp18, 0);
                    var_r30 = 0;
                    GetInteger(arg0->unk0x20, QB_TRICKTRIS_TOTAL_TO_WIN, &sp1C, 1);
                    var_ctr = 0x1E;
                    var_r9 = (char *)arg0 + 0x84;
                    do {
                        temp_r0 = *(s32 *)var_r9;
                        var_r9 += 0x24;
                        if (temp_r0 == 0) {
                            var_r30 += 1;
                        }
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                    GetInteger(arg0->unk0x20, QB_TRICKTRIS_BLOCK_SIZE, &sp20, 1);
                    if ((var_r30 < sp20) && (var_r30 + sp18 < sp1C)) {
                        var_r4 = sp20 - var_r30;
                        temp_r0 = (sp1C - sp18) - var_r30;
                        if (temp_r0 < var_r4) {
                            var_r4 = temp_r0;
                        }
                        goto block_40;
                    }
                }
        } else {
            temp_r9 = arg0->unk0x14;
            if ((temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20) != 0) && ((arg0->unk0x70 & 0x80000) || (arg0->unk0x54 >= spC))) {
                temp_r9 = arg0->unk0x14;
                if (temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98) == 0) {
                    temp_f1 = fn_800144C8() * lbl_802A9CFC;
                    arg0->unk0x4B0 += (s32)temp_f1;
                    temp_r3_3 = fn_8019519C(arg0);
                    if (temp_r3_3 != 0) {
                        if ((ContainsFlag(arg0->unk0x20, QB_SINGLE_COMBO_ADDED) == 0) && (arg0->unk0x4B0 > 0x32)) {
                            GetInteger(arg0->unk0x20, QB_COMBO_SIZE, &sp24, 1);
                            fn_801937EC(arg0, sp24);
                            AddChecksum(arg0->unk0x20, 0, QB_SINGLE_COMBO_ADDED);
                        }
                    } else {
                        GetInteger(arg0->unk0x20, QB_ADJUSTED_TRICK_TIME, &sp28, 1);
                        if (arg0->unk0x4B0 > sp28) {
                            arg0->unk0x4B0 = temp_r3_3;
                            if (fn_80195124(arg0) != 0) {
                                GetInteger(arg0->unk0x20, QB_COMBO_SIZE, &sp2C, 1);
                                var_r4 = sp2C;
block_40:
                                fn_801937EC(arg0, var_r4);
                            } else {
                                fn_801937EC(arg0, 1);
                            }
                        }
                    }
                }
            }
        }
    }
tail:
    return fn_8018CD64(arg0);
}
