// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801927F0-0x80192854 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_80198F7C(s32);
s32 fn_8018C374(Unk_007756DA *, s32, s32);
s32 fn_801927F0(Unk_007756DA *arg0, s32 arg1, s32 arg2) {
    s32 var_r3;
    if ((arg1 == 0) && (fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK)) {
        var_r3 = 0;
    } else {
        var_r3 = fn_8018C374(arg0, arg1, arg2);
    }
    return var_r3;
}
