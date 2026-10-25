// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802070E8-0x80207184 (156B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_800145AC(void);

void fn_802070E8(Unk_90685748 *arg0, s32 arg1, u32 arg2) {
    s32 var_r28;
    s32 var_r29;
    char *var_r31;
    s32 temp_r30;
    s32 off;

    var_r28 = 0;
    var_r29 = arg0->unk0x99E;
    if (var_r28 < arg0->unk0x99C) {
        off = var_r29 * 0x18 + 0x50;
        var_r31 = (char *)(off + (s32)arg0);
        do {
            if (*(s32 *)(var_r31 - 0xC) == arg1) {
                temp_r30 = *(s32 *)(var_r31 - 0x14);
                if ((u32)(fn_800145AC() - temp_r30) >= arg2) {
                    *(s32 *)var_r31 = -1;
                }
            }
            var_r31 -= 0x18;
            var_r29 -= 1;
            if (var_r29 < 0) {
                var_r31 += 0x960;
                var_r29 += 0x64;
            }
            var_r28 += 1;
        } while (var_r28 < arg0->unk0x99C);
    }
}
