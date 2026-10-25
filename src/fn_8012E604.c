// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E604-0x8012E65C (88B). Byte-identical.
#include "types.h"

s32 fn_8000A778(void);
void fn_80135424(s32, s32, s32, s32, s32);
s32 fn_801255B8(void);
void fn_8012E604(s32 hidden, s32 arg1, s32 arg2) {
    s32 var_r7;
    s32 temp_r6;

    temp_r6 = fn_8000A778();
    var_r7 = 1;
    if (arg2 == 0) {
        var_r7 = 0;
    }
    fn_80135424(arg1, arg1, (s32)fn_801255B8, temp_r6, var_r7);
}
