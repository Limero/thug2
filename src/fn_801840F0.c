// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801840F0-0x80184168 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-rerun-cse-after-loop
#include "types.h"
#include "structs.h"
s32 fn_801840F0(Unk_C7387A53 *arg0, s32 arg1) {
    CStruct *var_r9;
    s32 var_r11;
    s32 var_r4;

    var_r4 = arg1;
    var_r9 = arg0->unk0x2C;
    var_r11 = 0;
    goto check1;
    do {
        var_r9 = var_r9->unk0xC;
        var_r11 += 1;
    check1:
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
    } while (var_r9 != NULL);
    if (var_r11 == 0) {
        return 0;
    }
    var_r9 = arg0->unk0x2C;
    goto check2;
    do {
        if (--var_r4 == -1) {
            goto found;
        }
        var_r9 = var_r9->unk0xC;
    check2:
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
    } while (var_r9 != NULL);
    var_r9 = NULL;
found:
    return var_r9->unk0x4;
}
