// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5278-0x801A52E4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80127E70(s32, s32, s32, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);
bool fn_801A5278(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r0;
    s32 temp_r30;

    temp_r30 = arg0 + 0x6C;
    fn_80128C80(temp_r30, QB_POINTS_AVAILABLE, &sp8, 1);
    temp_r0 = sp8 + arg1;
    sp8 = temp_r0;
    fn_80127E70(temp_r30, QB_POINTS_AVAILABLE, 1, temp_r0);
    return true;
}
