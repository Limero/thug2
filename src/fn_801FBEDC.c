// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FBEDC-0x801FBF18 (60B). Byte-identical.
#include "types.h"
#include "types.h"
#include "structs.h"
s32 fn_801FBE60(void);
s32 fn_801F9F2C(Unk_C7387A53 *, s32);
s32 fn_801FBEDC(void *arg0, void *arg1, s32 arg2) {
    s32 var_r3;

    var_r3 = fn_801FBE60();
    if (var_r3 != 0) {
        var_r3 = fn_801F9F2C(var_r3, arg2);
    }
    return var_r3;
}
