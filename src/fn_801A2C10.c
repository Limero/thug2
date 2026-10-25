// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2C10-0x801A2CF8 (232B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_801A26E0(Unk_31DE137E * arg0, s32 arg1);
extern void fn_801A2B1C(Unk_31DE137E * arg0, Unk_C8FEE62D * arg1);
extern s32 fn_801A269C(Unk_31DE137E * arg0);
bool fn_801A2C10(Unk_31DE137E *arg0, s32 arg1) {
    Unk_C7387A53 *var_r3;
    Unk_89391A04 *temp_r9;
    Unk_C8FEE62D *var_r11;
    s32 var_r30;

    var_r30 = 0;
    if (arg1 == 0) {
        var_r3 = fn_801A26E0(arg0, 0);
        if (var_r3 != NULL) {
            var_r30 = 1;
            fn_801A2B1C(arg0, var_r3);
        }
    } else {
        var_r3 = fn_801A26E0(arg0, 0);
        if ((var_r3 != NULL) && (var_r3->unk0x20 != 0)) {
            var_r30 = 1;
            do {
                fn_801A2B1C(arg0, var_r3);
                var_r3 = fn_801A26E0(arg0, 0);
                if (var_r3 == NULL) {
                    break;
                }
            } while (var_r3->unk0x20 != 0);
        }
    }
    var_r11 = fn_801A26E0(arg0, 0);
    if (var_r11 != NULL) {
        temp_r9 = var_r11->unk0x14;
        temp_r9->unk0x24((char *)var_r11 + temp_r9->unk0x20);
    }
    if (var_r30 == 0) {
        fn_801A269C(arg0);
    }
    return true;
}
