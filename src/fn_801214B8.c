// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801214B8-0x80121518 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80015434(s32);
void Mem_Free_3(s32);
extern s32 lbl_80302F10;
bool fn_801214B8(s32 arg0) {
    s32 temp_r3;
    s32 a0 = arg0;

    if (lbl_80302F10 != 0) {
        Mem_Free_3(lbl_80302F10);
        lbl_80302F10 = 0;
    }
    temp_r3 = fn_80015434(a0);
    lbl_80302F10 = temp_r3;
    if (temp_r3 == 0) {
        return false;
    } else {
        return true;
    }
}
