// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013F708-0x8013F734 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8013F708(Unk_FFAD6788 *arg0) {
    s32 temp_r9;
    volatile s32 sp8;
    s32 var_r3;

    temp_r9 = arg0->unk0x68;
    sp8 = 4;
    var_r3 = 1;
    if (!(temp_r9 & 4)) {
        var_r3 = 0;
    }
    return var_r3 ^ 1;
}
