// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801918C4-0x80191980 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80190ACC(void *, s32 *, s32, s32, void *, s32);
void fn_80191050(CStruct *, s32, s32, s32, s32);
void fn_801918C4(CStruct *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r28;
    s32 temp_r31;

    temp_r31 = arg0->unk0x4;
    if (temp_r31 != 0) {
        return;
    }
    sp8 = 0;
    GetString(arg1, QB_SPEAKER_NAME, &sp8, 0);
    var_r28 = 0;
    if (fn_80190ACC(arg0, &spC, -1, 1, sp8, 1) != 0) {
        var_r28 = 1;
    }
    sp10 = 0;
    GetChecksum_2(arg1, QB_SPEAKER_OBJ_ID, &sp10, 0);
    if (spC == 0) {
        return;
    }
    fn_80191050(arg0, spC, 0, sp10, var_r28);
}
