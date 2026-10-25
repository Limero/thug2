// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EAC4-0x8009EB68 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801318C8(CStruct *, s32, s32);
void fn_80131960(CStruct *, s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_8009EAC4(CStruct *arg0, CStruct *arg1, s32 arg2) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    sp8 = 0;
    temp_r3 = GetChecksum_2(arg1, QB_NAME, &sp8, 0);
    if (temp_r3 != 0) {
        fn_80131960(arg0, sp8, arg2);
    } else {
        spC = temp_r3;
        if (GetChecksum_2(arg1, QB_ID, &spC, 0) != 0) {
            fn_801318C8(arg0, spC, arg2);
        }
    }
    return true;
}
