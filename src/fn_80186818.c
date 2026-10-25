// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186818-0x801868AC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GoalManager_GetGoal(Unk_31DE137E *, s32, s32);
s32 fn_8018D924(s32);
s32 GetStructure_2(s32, s32, s32 *, s32);
s32 GetInteger(s32, s32, s32 *, s32);
s32 fn_80186818(Unk_31DE137E *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = GoalManager_GetGoal(arg0, arg1, 0);
    if (temp_r3 != 0) {
        return fn_8018D924(temp_r3);
    }
    spC = temp_r3;
    if (GetStructure_2(arg0->unk0x1C, arg1, &sp8, 0) != 0) {
        GetInteger(sp8, QB_ISLOCKED, &spC, 1);
    }
    var_r3 = 1;
    if (spC == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
