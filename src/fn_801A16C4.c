// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A16C4-0x801A1710 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002DE6C(Unk_C7387A53 *);                            

s32 fn_801A16C4(Unk_31DE137E *arg0) {
    s32 var_r31;

    var_r31 = 0;
    if (((s32) arg0->unk0x1C != 0) && (fn_8002DE6C((char *)arg0 + 0x40) != 0)) {
        var_r31 = 1;
    }
    return var_r31;
}
