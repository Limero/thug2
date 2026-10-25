// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D924-0x8018D97C (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(s32 arg0);
extern s32 fn_80187B0C(s32 arg0, s32 arg1, s32 arg2);

s32 fn_8018D924(Unk_C7387A53 *arg0) {
    s32 var_r30;
    s32 temp_r3;

    var_r30 = 0;
    temp_r3 = Game_GetGoalManager((s32)arg0);
    if (((arg0->unk0x70 & QB_UNKNOWN_0x04000000) != 0) || (fn_80187B0C(temp_r3, arg0->unk0x3C, arg0->unk0x38) != 0)) {
        var_r30 = 1;
    }
    return var_r30;
}
