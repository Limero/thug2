// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CF34-0x8005CF80 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005C6E8(s32, s32, s32);
s32 fn_8005CECC(s32, s32, s32);
s32 fn_8005CF34(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r3;

    temp_r3 = fn_8005CECC(arg0, arg1, arg2);
    if (temp_r3 != 0) {
        fn_8005C6E8(temp_r3, arg3, arg4);
    }
    return temp_r3;
}
