// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019245C-0x80192484 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8019245C(Unk_C7387A53 *arg0) {
    s32 var_r9;

    var_r9 = 0;
    if ((arg0->unk0x70 & 0x200000) || ((s32) arg0->unk0x74 != 0)) {
        var_r9 = 1;
    }
    return var_r9;
}
