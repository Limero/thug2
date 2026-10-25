// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024090-0x800240F4 (100B). Byte-identical.
#include "types.h"
extern char lbl_80300368[];
extern s32 lbl_8030036C;
extern s32 lbl_80300370;
extern bool lbl_80300374;
s32 fn_80024090(s32 arg0) {
    s32 temp_r3;
    s32 temp_r7;

    temp_r7 = *(s32 *)&lbl_80300368;
    if (temp_r7 == 0) {
        return 0;
    }
    if ((s32) (lbl_80300370 - lbl_8030036C) < arg0) {
        lbl_8030036C = 0;
    }
    temp_r3 = lbl_8030036C;
    lbl_8030036C = temp_r3 + arg0;
    lbl_80300374 += arg0;
    return temp_r7 + temp_r3;
}
