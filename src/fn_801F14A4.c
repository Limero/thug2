// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F14A4-0x801F14C8 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F14A4(Unk_E06AC104 *arg0) {
    s32 var_r3;

    if (arg0->unk0x188 != 0) {
        goto L0;
    }
    var_r3 = 1;
    __asm__("" : "+r"(var_r3));
    if (arg0->unk0x20 != 1) {
    L0:
        var_r3 = 0;
    }
    return var_r3;
}
