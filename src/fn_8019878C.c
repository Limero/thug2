// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019878C-0x8019880C (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;

extern s32 fn_801754AC(s32 arg0);
extern s32 fn_8019868C(CStruct * arg0);
extern s32 fn_80128C80(CStruct * arg0, void * arg1, void * arg2, s32 arg3);

s32 fn_8019878C(CStruct *arg0) {
    s32 sp8;
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = fn_801754AC(lbl_80305EAC);
    var_r3 = 0;
    if (temp_r3 != 0) {
        if (fn_8019868C(arg0) == 0) {
            return 1;
        }
        fn_80128C80((char *)arg0 + 4, QB_STOP_AT_ZERO, &sp8, 1);
        var_r3 = sp8;
        var_r3 = (var_r3 == 1);
    }
    return var_r3;
}
