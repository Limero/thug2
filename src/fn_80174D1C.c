// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174D1C-0x80174DB8 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A6C4C(s32, s32);
extern char lbl_80305F1C[];
extern char lbl_80305F9C[];
s32 fn_8009CF2C(s32);
s32 fn_801A98F0(s32);
void fn_80174D1C(Unk_C7387A53 *arg0) {
    s32 var_r10;
    s32 var_r3;
    register CStruct *var_r9 __asm__("r9");

    arg0->unk0x54 = 0;
    var_r9 = arg0->unk0x38;
    var_r10 = 0;
    var_r3 = *(s32 *)&lbl_80305F9C;
    for (;;) {
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
        if (var_r9 == NULL) {
            break;
        }
        var_r9 = var_r9->unk0xC;
        var_r10 += 1;
    }
    if ((var_r10 != 0) || (fn_8009CF2C(var_r3) != 0)) {
        if ((s32) arg0->unk0x50 != 0) {
            fn_801A6C4C(arg0->unk0x24, -1);
            var_r3 = fn_801A98F0(*(s32 *)&lbl_80305F1C);
        }
    }
}
