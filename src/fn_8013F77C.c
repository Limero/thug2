// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013F77C-0x8013F7F8 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8013F74C(void *);

// WINNER fn_8013F77C (124B) - doc 04. volatile sp8=2 + named temp_r9 flags
// load + prototyped callee + post-call r3-flow value web.
s32 fn_8013F77C(Unk_2DBBFAC5 *arg0) {
    volatile s32 sp8;
    s32 temp_r9;
    s32 var_r11;
    s32 v;
    s32 temp_r0;

    temp_r9 = arg0->unk0x68;
    var_r11 = 1;
    sp8 = 2;
    if (!(temp_r9 & 2)) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        return 0x3E8;
    }
    if (fn_8013F74C((void *)arg0) == 0) {
        v = arg0->unk0x20B4;
    } else {
        v = 0;
    }
    temp_r0 = v * 2;
    v = 0x1F4;
    if (temp_r0 > 0x1F3) {
        v = temp_r0;
    }
    return v;
}
