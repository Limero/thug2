// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010A00-0x80010A38 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
// MemAvailable @ 0x80010A00
s32 MemAvailable(Unk_C8FEE62D *arg0) {
    s32 var_r0;
    s32 var_r3;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_2;

    temp_r9 = arg0->unk0x10;
    if (temp_r9 != NULL) {
        var_r0 = temp_r9->unk0x3C;
    } else {
        var_r0 = arg0->unk0x4;
    }
    temp_r9_2 = arg0->unk0x14;
    if (temp_r9_2 != NULL) {
        var_r3 = temp_r9_2->unk0x3C;
    } else {
        var_r3 = arg0->unk0xC;
    }
    return var_r3 - var_r0;
}
