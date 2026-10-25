// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A46C-0x8003A5B8 (332B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003D868(s32, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void AddChecksum(CStruct *, s32, s32);
s32 fn_8003A430(CStruct *);
void CStruct_dtor(CStruct *);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8003D664(s32, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80127358(CStruct *, Unk_C7387A53 *);
void fn_8003A46C(s32 arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r29_3;
    s32 temp_r30;
    s32 temp_r30_2;
    void *temp_r31;
    CStruct *var_r30;

    sp8 = 0;
    var_r30 = fn_80127358(arg0 + 0x58, NULL);
    if (var_r30 != NULL) {
        do {
            temp_r31 = fn_80127358(arg0 + 0x58, var_r30);
            if ((s32) (var_r30->unk0x0 & 0x7F0000) == 0xA0000) {
                temp_r29 = var_r30->unk0x4;
                if (ContainsFlag(var_r30->unk0x8, QB_RANDOMIZED_DESC_ID) != 0) {
                    temp_r29_2 = fn_8003D664(temp_r29, sp8);
                    GetChecksum_2(temp_r29_2, QB_RANDOM_SET, &sp8, 0);
                    CStruct_dtor(var_r30->unk0x8);
                    temp_r30 = var_r30->unk0x8;
                    AddChecksum(temp_r30, QB_DESC_ID, fn_8003A430(temp_r29_2));
                } else if (GetInteger(var_r30->unk0x8, QB_RANDOM_INDEX, &spC, 0) != 0) {
                    temp_r29_3 = fn_8003D868(temp_r29, spC, sp8);
                    GetChecksum_2(temp_r29_3, QB_RANDOM_SET, &sp8, 0);
                    CStruct_dtor(var_r30->unk0x8);
                    temp_r30_2 = var_r30->unk0x8;
                    AddChecksum(temp_r30_2, QB_DESC_ID, fn_8003A430(temp_r29_3));
                }
            }
            var_r30 = temp_r31;
        } while (var_r30 != NULL);
    }
}
