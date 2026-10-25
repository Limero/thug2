// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019EA50-0x8019EAD0 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80301B48;
extern s32 fn_800F2A48(s32 mgr, s32 val, s32 flag);
extern s32 fn_800F2628(Unk_C7387A53 * a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j);
bool fn_8019EA50(s32 arg0, s32 arg1) {
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = lbl_80301B48;
    temp_r3 = fn_800F2A48(temp_r31, arg1, 0);
    if (temp_r3 != 0) {
        return false;
    }
    fn_800F2628(temp_r31, arg0, 6, arg1, 0, 0, 0, 0, temp_r3, temp_r3);
    return true;
}
