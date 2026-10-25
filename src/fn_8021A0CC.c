// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A0CC-0x8021A18C (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 fn_8021F6D4(CStruct * arg0);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetText(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

// FirstNewPlayerInfo @ 0x8021A0CC
s32 FirstNewPlayerInfo(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    s32 var_r29;
    CStruct *temp_r28;
    s32 temp_r30;
    s32 temp_r31;

    var_r29 = 0;
    temp_r28 = fn_801259C8(QB_MODE_INFO, 0);
    for (; var_r29 < temp_r28->unk0x4; var_r29++) {
        temp_r31 = fn_80129528(temp_r28, var_r29);
        temp_r30 = fn_8021F6D4(arg0);
        GetChecksum_2(temp_r31, QB_CHECKSUM, &sp8, 0);
        if (temp_r30 == sp8) {
            GetText(temp_r31, QB_NAME, &spC, 1);
            return spC;
        }
    }
    return 0;
}
