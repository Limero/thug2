// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011D7C-0x80011DE0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 MemAvailable(Unk_C8FEE62D *);
extern s32 lbl_80290628;

s32 fn_80011D7C(Unk_C7387A53 *arg0) {
    u32 temp_r0;
    s32 total;
    CStruct *var_r11;

    total = MemAvailable(arg0->unk0x34);
    var_r11 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x40) + 0x1C);
    if (var_r11 != NULL) {
        do {
            temp_r0 = (u32) var_r11->unk0x8 >> 8U;
            total += lbl_80290628 + temp_r0;
            var_r11 = var_r11->unk0x0;
        } while (var_r11 != NULL);
    }
    return total;
}
