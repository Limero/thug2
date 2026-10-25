// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D14C-0x8002D1C4 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8002CB4C(Unk_F1C0E2AD *, s32);
void fn_8002D14C(Unk_FFAD6788 *arg0, s32 arg1) {
    s32 *var_r31;
    s32 var_r30;
    s32 zero;

    zero = 0;
    var_r31 = (char *)arg0 + 4;
    var_r30 = 0x32;
    do {
        if ((s32) *((s32 *)var_r31) != 0) {
            fn_8002CB4C(*((s32 *)var_r31), 3);
            *((s32 *)var_r31) = zero;
        }
        var_r31 += 1;
        var_r30 -= 1;
    } while (var_r30 != 0);
    arg0->unk0xD0 = var_r30;
    arg0->unk0xD4 = var_r30;
    arg0->unk0xD8 = var_r30;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
