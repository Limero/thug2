// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AC4E4-0x801AC550 (108B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_800E9D30(Unk_C7387A53 * arg0, s32 arg1);

s32 fn_801AC4E4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r11;
    s32 var_r8;
    Unk_C7387A53 *var_r3;

    var_r11 = 0;
    while (var_r11 < arg0->unk0x50) {
        var_r3 = (void *)((char *)arg0->unk0x48 + (var_r11 * 0x60));
        if (var_r3->unk0x54 == arg1) {
            return fn_800E9D30(var_r3, 2);
        }
        var_r11 += 1;
    }
    return 0;
}
