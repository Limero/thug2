// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BB84-0x8006BBE4 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
u32 fn_8006BB84(void *arg0, u32 arg1) {
    s32 temp_r0;
    s32 temp_r11;
    s32 var_r9;
    u32 var_r10;
    u32 var_r8;
    void *var_r3;

    var_r3 = arg0;
    var_r8 = 0U;
    var_r10 = 0U;
    var_r9 = ((Unk_D0F3FE29 *)var_r3)->unk0x600 - ((Unk_D0F3FE29 *)var_r3)->unk0x0;
    if (var_r8 < arg1) {
        do {
            temp_r11 = ((Unk_D0F3FE29 *)var_r3)->unk0x0;
            if (temp_r11 == 0) {
                return var_r10;
            }
            temp_r0 = ((Unk_D0F3FE29 *)var_r3)->unk0x600 - temp_r11;
            if (temp_r0 > var_r9) {
                var_r9 = temp_r0;
                var_r8 = var_r10;
            }
            var_r10 += 1;
            var_r3 += 4;
        } while (var_r10 < arg1);
    }
    return var_r8;
}
