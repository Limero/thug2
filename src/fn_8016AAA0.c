// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016AAA0-0x8016AB1C (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80125A3C(void *, s32);
s32 fn_8009D888(CScript *, s32);
s32 fn_8009D8B4(s32, s32);
void fn_8016AAA0(CScript *arg0) {
    s32 temp_r10;
    Unk_C7387A53 *temp_r11;
    CScript *temp_r9;

    temp_r11 = arg0->unk0x2C;
    temp_r11->unk0x4C = 0;
    temp_r9 = arg0->unk0x1C;
    temp_r10 = temp_r9->unk0x1C & 0x100;
    if (temp_r10 != 0) {
        temp_r11->unk0x4C = (s32) temp_r9->unk0x20;
        if (fn_80125A3C(QB_SELECT_SHIFT, 1) != 0) {
            fn_8009D888(arg0->unk0x1C, 1);
            fn_8009D8B4(arg0->unk0x1C, 1);
        }
    }
}
