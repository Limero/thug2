// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D56BC-0x800D5714 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0598(s32);
s32 Mth_Rnd(s32);
void AddInteger(CStruct *, s32, s32);
bool fn_800D56BC(CScript *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r30;
    s32 temp_r3;
    temp_r3 = fn_800F0598(arg0->unk0x200);
    if (temp_r3 != 0) {
        temp_r30 = arg2->unk0x18;
        AddInteger(temp_r30, QB_LINK, Mth_Rnd(temp_r3) + 1);
    }
    return true;
}
