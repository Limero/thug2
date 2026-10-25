// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056174-0x800561B4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80055E74(void);
s32 fn_800561B4(Unk_CFB386B2 *, CScript *);
s32 fn_80056174(Unk_CFB386B2 *arg0) {
    s32 var_r3;
    s32 ret;

    ret = fn_80055E74();
    var_r3 = 0;
    if (ret != 0) {
        var_r3 = fn_800561B4(arg0, ret);
    }
    return var_r3;
}

