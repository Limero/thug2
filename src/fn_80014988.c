// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014988-0x80014A5C (212B). Byte-identical.
#include "types.h"
s32 fn_8001B7C0(s32);
void fn_8001B718(s32, s32, s32);
s32 fn_8000E08C(s32, s32, s32);
s32 fn_80014988(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;

    if (fn_8000DE40() != 0) {
        temp_r30 = fn_8000E08C(arg0, arg1, arg2);
        if (fn_8000DE5C() != 0) {
            return temp_r30;
        }
    }
    switch (arg2) {
    case 0:
        fn_8001B718(arg0 + 0x84, 0, arg1);
        break;
    case 2:
        fn_8001B718(arg0 + 0x84, 1, arg1);
        break;
    default:
    case 1:
        fn_8001B718(arg0 + 0x84, 2, arg1);
        break;
    }
    return fn_8001B7C0(arg0 + 0x84);
}
