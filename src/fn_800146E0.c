// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800146E0-0x8001473C (92B). Byte-identical.
#include "types.h"
s32 fn_8000DE40();                                  
s32 fn_8000DE5C();                                  
s32 fn_8000E104(s32);                               
s32 fn_8001B6A8(s32);                               

s32 fn_800146E0(s32 arg0) {
    s32 temp_r31;

    if (fn_8000DE40() != 0) {
        temp_r31 = fn_8000E104(arg0);
        if (fn_8000DE5C() != 0) {
            return temp_r31;
        }
    }
    return fn_8001B6A8(arg0 + 0x84);
}
