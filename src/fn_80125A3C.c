// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125A3C-0x80125A6C (48B). Byte-identical.
#include "types.h"
void Script_GetInteger(void *, s32);
void fn_80125A3C(void *arg0, s32 arg1) {
    s32 var_r4;

    var_r4 = 0;
    if (arg1 != 0) {
        var_r4 = 1;
    }
    Script_GetInteger(arg0, var_r4);
}
