// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014904-0x80014980 (124B). Byte-identical.
#include "types.h"
s32 fn_8000DE40();                                  
s32 fn_8000DE5C();                                  
s32 fn_8000E014(void *, s32, s32, s32);                
s32 fn_8001B6DC(s32, s32, s32);                     

s32 fn_80014904(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r31;

    if (fn_8000DE40() != 0) {
        temp_r31 = fn_8000E014(arg0, arg1, arg2, arg3);
        if (fn_8000DE5C() != 0) {
            return temp_r31;
        }
    }
    return fn_8001B6DC(arg3 + 0x84, arg0, arg1 * arg2);
}
