// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219FE0-0x8021A0CC (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_8021D920(Unk_C7387A53 * arg0);
extern s32 fn_80233930(void);
extern s32 GetText(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

s32 fn_80219FE0(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 var_r30;
    s32 temp_r28;
    CStruct *temp_r29;
    s32 temp_r3;
    s32 temp_r31;

    var_r30 = 0;
    temp_r29 = fn_801259C8(QB_LEVEL_SELECT_MENU_LEVEL_INFO, 0);
    for (; var_r30 < temp_r29->unk0x4; var_r30++) {
        temp_r28 = QB_LOAD_SK5ED_GAMEPLAY;
        temp_r31 = fn_80129528(temp_r29, var_r30);
        GetChecksum_2(temp_r31, QB_LEVEL, &sp8, 0);
        temp_r3 = fn_8021D920(arg0);
        if (temp_r3 == sp8) {
            if ((arg1 != 0) && (temp_r3 == temp_r28)) {
                return fn_80233930();
            }
            GetText(temp_r31, QB_TEXT, &spC, 1);
            return spC;
        }
    }
    return 0;
}
