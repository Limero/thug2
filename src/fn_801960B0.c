// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801960B0-0x8019614C (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_80129528(CStruct * arg0, s32 arg1);
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);

s32 fn_801960B0(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 var_r30;
    s32 temp_r29;
    s32 temp_r31;

    GetArray(arg0->unk0x20, QB_GOAL_OBJECTS, &sp8, 1);
    var_r30 = 0;
    temp_r29 = ((CStruct *)sp8)->unk0x4;
    for (; var_r30 < temp_r29; var_r30++) {
        GetChecksum_2(temp_r31 = fn_80129528(sp8, var_r30), QB_CLUSTER_ID, &spC, 1);
        if (spC == arg1) {
            return temp_r31;
        }
    }
    return 0;
}
