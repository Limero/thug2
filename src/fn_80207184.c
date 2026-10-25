// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207184-0x80207244 (192B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_800145AC(void);

bool fn_80207184(Unk_90685748 *arg0, s32 arg1, u32 arg2, s32 arg3) {
    s32 var_r28;
    s32 var_r29;
    char *var_r31;
    s32 temp_r30;
    s32 off;

    var_r28 = 0;
    var_r29 = arg0->unk0x99E;
    if (var_r28 < arg0->unk0x99C) {
        off = var_r29 * 0x18 + 0x4C;
        var_r31 = (char *)(off + (s32)arg0);
        do {
            temp_r30 = *(s32 *)(var_r31 - 0x10);
            if ((u32)(fn_800145AC() - temp_r30) >= arg2) {
                break;
            }
            if ((((Unk_4C649A8C *)var_r31)->unk0x4 & arg3) == 0) {
                if (*(s32 *)(var_r31 - 0xC) == 1 && *(s32 *)(var_r31 - 8) == arg1) {
                    *(s32 *)var_r31 = *(s32 *)(var_r31 - 0xC);
                    return true;
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
    return false;
}
