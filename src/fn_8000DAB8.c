// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DAB8-0x8000DAF8 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000D984(s32, void *, s32, Unk_C8FEE62D *);
s32 fn_8000DAB8(void *arg0, s32 arg1, Unk_C8FEE62D *arg2, s32 arg3, s32 arg4) {
    s32 var_r3;

    if (arg1 == 3) {
        var_r3 = fn_8000D984(arg3, arg0, arg4, arg2);
    } else {
        var_r3 = arg3;
    }
    return var_r3;
}
