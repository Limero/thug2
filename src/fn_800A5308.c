// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5308-0x800A5360 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800A68BC(s32, s32, s32);
s32 fn_800A5308(CStruct *arg0, s32 arg1) {
    s32 sp8;
    s32 var_r3;

    sp8 = arg1;
    var_r3 = fn_800A68BC(arg0->unk0x8, &sp8, 1);
    if (var_r3 == 0) {
        var_r3 = fn_800A68BC(arg0->unk0xC, &sp8, 1);
    }
    return var_r3;
}
