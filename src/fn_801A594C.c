// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A594C-0x801A59B4 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A653C(s32, s32);
void *fn_801A594C(Unk_C7387A53 *arg0) {
    s32 *var_r9;
    s32 var_r0;

    fn_801A653C((char *)arg0 + 4, 0x20);
    arg0->unk0x24 = 0;
    var_r9 = (char *)arg0 + 0x20;
    var_r0 = 1;
    do {
        *((s32 *)var_r9) = 0;
        var_r0 -= 1;
        var_r9 = (s32 *)((char *)var_r9 - 4);
    } while (var_r0 >= 0);
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    return arg0;
}
