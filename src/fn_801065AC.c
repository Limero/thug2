// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801065AC-0x801065F0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801065AC(Unk_C7387A53 *arg0, s32 arg1) {
    s32 *var_r3;
    s32 temp_r0;
    s32 var_r9;
    s32 var_r11;

    var_r9 = 0;
    temp_r0 = arg0->unk0x24;
    if (var_r9 < temp_r0) {
        var_r3 = *((s32 * *)&arg0->unk0x2C);
        var_r11 = temp_r0;
loop_2:
        temp_r0 = *var_r3;
        var_r3 += 1;
        if (temp_r0 == arg1) {
            return true;
        }
        var_r9 += 1;
        if (var_r9 < var_r11) {
            goto loop_2;
        }
    }
    return false;
}
