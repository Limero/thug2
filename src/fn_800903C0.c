// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800903C0-0x800903F0 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800903C0(CStruct *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_ctr;
    u32 var_r0;
    u32 var_r9;

    temp_r0 = arg1 * 4;
    var_r9 = arg0->unk0x10;
    var_ctr = temp_r0;
    if (temp_r0 > 0) {
        do {
            var_r0 = var_r9 >> 1U;
            if (var_r9 & 1) {
                var_r0 ^= 0x3500;
            }
            var_r9 = var_r0;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    arg0->unk0x10 = var_r9;
}
