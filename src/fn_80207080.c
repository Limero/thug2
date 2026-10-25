// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207080-0x802070E8 (104B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_80207080(Unk_90685748 *arg0, s32 arg1) {
    s32 var_r10;
    s32 var_r11;
    char *var_r9;
    s32 off;

    var_r10 = 0;
    var_r11 = arg0->unk0x99E;
    if (var_r10 < arg0->unk0x99C) {
        off = var_r11 * 0x18 + 0x50;
        var_r9 = (char *)(off + (s32)arg0);
        do {
            if (*(s32 *)(var_r9 - 4) != 0) {
                *(s32 *)(var_r9 - 4) = 0;
                *(s32 *)var_r9 |= arg1;
            }
            var_r9 -= 0x18;
            var_r11 -= 1;
            if (var_r11 < 0) {
                var_r9 += 0x960;
                var_r11 += 0x64;
            }
            var_r10 += 1;
        } while (var_r10 < arg0->unk0x99C);
    }
}
