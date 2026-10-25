// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8520-0x801A8548 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A8520(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r9;
    var_r9 = 0;
    if ((s32) arg0->unk0x44 != 0) {
        var_r9 = (arg1 ^ arg0->unk0x40) == 0;
    }
    return var_r9;
}
