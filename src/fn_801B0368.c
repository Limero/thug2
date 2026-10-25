// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0368-0x801B03E0 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801B0330();
void fn_801B0228(Unk_9994C3F5 *, s32);
void fn_801B0230(Unk_C7387A53 *, s32);
void fn_801B0238(CStruct *, s32);
s32 fn_801B0368(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 var_r3;

    if (fn_801B0330() == 0) {
        fn_801B0238(arg0, 0);
        var_r3 = 0;
    } else {
        fn_801B0228(arg0, arg1);
        fn_801B0230(arg0, arg2);
        fn_801B0238(arg0, 1);
        var_r3 = 1;
    }
    return var_r3;
}
