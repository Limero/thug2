// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80258840-0x80258880 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80258840(CScript *arg0, s32 b) {
    s32 var_r3;

    var_r3 = fn_80258254();
    if (var_r3 >= 0) {
        var_r3 = *((s32 *)((char *)arg0->unk0x18 + (var_r3 * 4)));
    }
    return var_r3;
}
