// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E168-0x8012E228 (192B). Byte-identical.
#include "types.h"
s32 fn_8012B2A0(void *);
s32 fn_8012B7B4(void *);
void fn_8012E168(u8 *arg0) {
    u8 *var_r31 = arg0;
    s32 var_r28 = 0;
    s32 var_r29 = 0;
    s32 var_r30 = 0;
loop_1:
    {
        u8 temp_r0 = *var_r31;
        if ((s32) temp_r0 == 3) {
            var_r28 += 1;
        }
        if ((s32) temp_r0 == 4) {
            var_r28 -= 1;
        }
        if ((s32) temp_r0 == 5) {
            var_r29 += 1;
        }
        if ((s32) temp_r0 == 6) {
            var_r29 -= 1;
        }
        if ((s32) temp_r0 == 0xE) {
            var_r30 += 1;
        }
        if ((s32) temp_r0 == 0xF) {
            var_r30 -= 1;
        }
        if (var_r28 != 0) {
            goto block_17;
        }
        if (var_r29 != 0) {
            goto block_17;
        }
        if (var_r30 != 0) {
            goto block_17;
        }
        if (fn_8012B7B4(var_r31) != 0) {
            goto block_18;
        }
    }
block_17:
    var_r31 = fn_8012B2A0(var_r31);
    goto loop_1;
block_18:
    fn_8012B2A0(var_r31);
    return;
}
