// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056080-0x800560E0 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80055E74(void);
s32 fn_800560E0(void *, Unk_C8FEE62D *, void *, Unk_C8FEE62D *, s32, s32);
s32 fn_80056080(void *arg0, s32 arg1, void *arg2, Unk_C8FEE62D *arg3, s32 arg4, s32 arg5) {
    s32 var_r3;
    s32 ret;

    ret = fn_80055E74();
    var_r3 = 0;
    if (ret != 0) {
        var_r3 = fn_800560E0(arg0, ret, arg2, arg3, arg4, arg5);
    }
    return var_r3;
}

