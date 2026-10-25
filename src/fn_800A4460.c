// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4460-0x800A44C0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A4460(CStruct *arg0, s32 arg1) {
    s32 var_r8;
    CStruct *temp_r11;

    var_r8 = 0;
    while (var_r8 < (s32) arg0->unk0x4) {
        temp_r11 = (void *)((s32)(var_r8 * 0x14) + arg0->unk0x0);
        if (((s32) temp_r11->unk0x8 == arg1) && ((s32) temp_r11->unk0x4 != -QB_UNKNOWN_0x3C883A8E)) {
            temp_r11->unk0x10 = (s32) (temp_r11->unk0x10 | QB_UNKNOWN_0x40000000);
        }
        var_r8 += 1;
    }
}
