// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800994C8-0x8009950C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: u16 derefs + char-stride r5 - EXACT, M5.46
void fn_800994C8(Unk_1C4D340C *arg0, s32 arg1, s32 *arg2) {
    s32 *var_r5;
    s32 var_ctr;
    u16 temp_r10;

    var_r5 = (s32 *)((char *)arg2);
    var_ctr = arg1;
    if (arg1 > 0) {
        do {
            temp_r10 = arg0->unk0x5E;
            if (temp_r10 < (u16) arg0->unk0x5C) {
                *((s32 *)((char *)arg0->unk0x58 + (temp_r10 * 4))) = *((s32 *)var_r5);
                arg0->unk0x5E = (u16) (arg0->unk0x5E + 1);
            }
            var_r5 = (s32 *)((char *)var_r5 + 4);
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}
