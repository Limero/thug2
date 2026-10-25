// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B7FF0-0x801B8018 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801B7FF0(CScript *arg0) {
    s32 var_r9;

    var_r9 = 0;
    if ((s32) arg0->unk0x1C == 2) {
        var_r9 = (arg0->unk0x24 & 0x89C) == 0;
    }
    return var_r9;
}
