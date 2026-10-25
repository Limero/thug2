// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130E88-0x80130F20 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8012EFC0(Unk_C7387A53 *);

void fn_80130E88(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    u32 var_r8;
    s32 var_r10;
    s32 var_r11;
    CScript *temp_r9;

    temp_r0 = arg0->unk0xAC;
    if (temp_r0 != 0) {
        if (temp_r0 == arg1) {
            fn_8012EFC0(arg0);
        }
    }
    var_r11 = 0;
    if (var_r11 < (s32) arg0->unk0x38) {
        var_r8 = 0U;
        var_r10 = 0;
        do {
            temp_r9 = var_r10 + arg0->unk0x94;
            temp_r0_2 = temp_r9->unk0x18;
            if (temp_r0_2 != 0) {
                if (temp_r0_2 == arg1) {
                    ((struct { u32 hi : 4; u32 lo : 28; } *)((char *)temp_r9 + (s32)0x28))->hi = var_r8;
                }
            }
            var_r11 += 1;
            var_r10 += 0x2C;
        } while (var_r11 < (s32) arg0->unk0x38);
    }
}
