// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF6D4-0x800DF78C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_800DFD2C(s32, s32, s32, f32);
extern f32 lbl_8029A49C;
bool fn_800DF6D4(s32 arg0, CStruct *arg1) {
    s32 sp10;
    f32 spC;
    s32 sp8;
    s32 has;
    s32 a1;
    f32 a3;
    s32 var_r5;
    sp8 = 0;
    if (GetChecksum_2(arg1, 0, &sp8, 0) != 0) {
        spC = lbl_8029A49C;
        GetFloat(arg1, QB_TIME, &spC, 0);
        sp10 = 0;
        GetInteger(arg1, QB_CLEAR, &sp10, 0);
        has = sp10;
        a1 = sp8;
        a3 = spC;
        var_r5 = 1;
        if (has == 0) {
            var_r5 = 0;
        }
        fn_800DFD2C(arg0, a1, var_r5, a3);
    }
    return true;
}
