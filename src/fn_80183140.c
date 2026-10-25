// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183140-0x80183194 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80183140(Unk_C8FEE62D *arg0, s32 *arg1) {
    CStruct *var_r11;

    var_r11 = arg0->unk0x8;
    arg0->unk0x10 = NULL;
    arg0->unk0x14 = 0;
    while (var_r11 != NULL) {
        if ((s32) var_r11->unk0x0 == (s32) *arg1) {
            arg0->unk0x10 = var_r11;
            return var_r11->unk0x4;
        }
        arg0->unk0x14 = (s32) (arg0->unk0x14 + 1);
        var_r11 = var_r11->unk0x8;
    }
    return 0;
}
