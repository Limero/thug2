// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D7FF8-0x800D80B8 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0598(s32);
s32 fn_800D67D0(void *, s32);
s32 ContainsFlag(s32, s32);
s32 fn_800D68AC(void *o);
s32 fn_800F0610(void *, s32);
s32 Mth_Rnd(s32);
void fn_800D7FF8(CScript *arg0, CStruct *arg1) {
    s32 temp_r3;
    s32 var_r30;
    if (ContainsFlag(arg1, QB_UNKNOWN_0x422E1FCE) != 0) {
        var_r30 = arg0->unk0x1FC;
    } else {
        var_r30 = arg0->unk0x200;
    }
    temp_r3 = fn_800F0598(var_r30);
    if (temp_r3 != 0) {
        if ((temp_r3 > 1) && (fn_800D68AC(arg0) != 0)) {
            fn_800D67D0(arg0, fn_800F0610(var_r30, Mth_Rnd(temp_r3)));
        } else {
            fn_800D67D0(arg0, fn_800F0610(var_r30, 0));
        }
        arg0->unk0x1C = (s32)((arg0->unk0x1C | 0x10) & QB_UNKNOWN_0xFFFFFFF7);
    }
}
