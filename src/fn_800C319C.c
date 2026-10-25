// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C319C-0x800C31E0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800C319C(Unk_BAEEFADA *arg0, f32 farg0) {
    s32 var_r3;
    f32 *var_r11;

    var_r3 = 0;
    var_r11 = (f32 *)((char *)arg0 + 0x300);
    for (;;) {
        if (!((farg0 * arg0->unk0x31C * *var_r11) > arg0->unk0x320)) {
            return var_r3;
        }
        if (!(var_r3 < (arg0->unk0x2FC - 1))) {
            return var_r3;
        }
        var_r11 += 1;
        var_r3 += 1;
    }
}
