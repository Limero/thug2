// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9430-0x801A9494 (100B). Byte-identical.
#include "types.h"
extern s32 fn_801A92F4(s32 arg0, s32 arg1);
extern s32 fn_801A867C(s32 arg0, s32 arg1);
extern s32 fn_801A9494(s32 arg0, s32 arg1, s32 arg2);
s32 fn_801A9430(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r28;

    temp_r28 = fn_801A867C(fn_801A92F4(arg0, arg2), arg1);
    if ((temp_r28 != 0) && (arg1 != arg2)) {
        fn_801A9494(arg0, arg1, arg2);
    }
    return temp_r28;
}
