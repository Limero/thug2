// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012FC30-0x8012FCA8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8009CF2C(s32);
extern char lbl_80305F9C[];
s32 fn_8012FC30(Unk_15EF4A35 *arg0, s32 arg2, void *arg3) {
    s32 var_r31;
    Unk_15EF4A35 *var_r11;
    Unk_4ADE3CE7 *temp_r9;

    if (arg3 != NULL) {
        var_r11 = (Unk_15EF4A35 *)arg3;
    } else {
        var_r11 = (Unk_15EF4A35 *)arg0->unk0xBC;
    }
    var_r31 = 0;
    if (var_r11 != NULL) {
        temp_r9 = (Unk_4ADE3CE7 *)((Unk_9994C3F5 *)var_r11)->unk0x8;
        var_r31 = temp_r9->unk0x1C((s32)((char *)var_r11 + temp_r9->unk0x18),
                                   arg2, arg0->unk0x14, (s32)arg0);
    } else {
        fn_8009CF2C(*(s32 *)&lbl_80305F9C);
    }
    return var_r31;
}
