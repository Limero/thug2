// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F59CC-0x801F5A0C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F59CC(s32 arg0) {
    s32 var_ctr;
    s32 var_r11;
    s32 var_r9;
    void *var_r3;

    var_r3 = arg0 + 0x20;
    var_ctr = 0x32;
    var_r11 = 0;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r3)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if (var_r9 != 0) {
            var_r11 += 1;
        }
        var_r3 += 0x370;
        var_ctr -= 1;
    } while (var_ctr != 0);
    return var_r11;
}
