// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056500-0x8005656C (108B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80056660(s32, s32, s32);
s32 fn_800127E4(Unk_C8FEE62D *, s32, void *, s32, s32);
void fn_8005761C(s32);
s32 fn_80056500(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r30;
    s32 var_r3;
    s32 ret;

    temp_r30 = arg0 + 0xD8;
    fn_8005761C(temp_r30);
    ret = fn_800127E4(temp_r30, 0, 0, 0, 0);
    var_r3 = 0;
    if (ret != 0) {
        fn_80056660(arg0, ret, arg2);
        var_r3 = 1;
    }
    return var_r3;
}

