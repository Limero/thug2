// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4DDC-0x800A4E70 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A4E70(void *, s32);
void fn_800A4DDC(Unk_451C91CE *arg0, s32 arg1, s32 arg2) {
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;

    var_r28 = arg2;
    var_r30 = 0;
    var_r31 = arg0->unk0x7000;
    if ((s32) arg0->unk0x7004 != 0) {
        var_r30 = var_r31;
        var_r31 = 0x400;
    }
    if (arg1 != 0) {
        var_r28 = arg0->unk0xB010;
    }
    if (var_r31 > 0) {
        do {
            if (var_r31 <= var_r28) {
                fn_800A4E70(arg0, var_r30);
            }
            var_r30 += 1;
            if (var_r30 == 0x400) {
                var_r30 = 0;
            }
            var_r31 -= 1;
        } while (var_r31 > 0);
    }
    arg0->unk0xB010 = 0;
}
