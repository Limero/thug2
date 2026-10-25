// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CCC9C-0x800CCD34 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800CCC9C(s32 arg0, CStruct *arg1) {
    s32 *dst;
    s32 spC;
    s32 sp8;
    s32 temp_r0;

    sp8 = -1;
    spC = 0;
    GetInteger(arg1, QB_TYPE, &sp8, 0);
    GetChecksum_2(arg1, 0, &spC, 0);
    if (sp8 != -1 && spC != 0 && sp8 <= 8 && sp8 != -1) {
        temp_r0 = sp8 * 4;
        dst = (s32 *)((char *)arg0 + 0x1C);
        *(s32 *)((char *)dst + temp_r0) = spC;
    }
}
