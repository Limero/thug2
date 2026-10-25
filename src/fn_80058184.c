// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058184-0x800581D8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80058184(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 var_r0;
    s32 v;
    Unk_897A0ACF *temp_r3;

    if (arg1 != 0) {
        var_r0 = arg0->unk0x4 | 1;
    } else {
        var_r0 = arg0->unk0x4 & QB_UNKNOWN_0xFFFFFFFE;
    }
    *((volatile s32 *)&arg0->unk0x4) = var_r0;
    temp_r3 = *((s32 * volatile *)&arg0->unk0x14);
    if (temp_r3 != NULL) {
        if (arg1 != 0) {
            v = (s32)temp_r3->unk0x4;
            v &= QB_UNKNOWN_0xFFFFFFFD;
            temp_r3->unk0x4 = (u16) v;
            return;
        }
        temp_r3->unk0x4 = (u16) (temp_r3->unk0x4 | 2);
    }
}
