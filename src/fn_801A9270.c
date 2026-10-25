// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9270-0x801A92C4 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A92C4(void);
void fn_801A8580(Unk_C8FEE62D *, s32);
bool fn_801A9270(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    s32 var_r4;

    temp_r3 = fn_801A92C4();
    if (temp_r3 == 0) {
        return false;
    }
    var_r4 = -1;
    if (arg2 != -1) {
        var_r4 = arg2 + 1;
    }
    fn_801A8580(temp_r3, var_r4);
    return true;
}
