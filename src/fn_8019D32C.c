// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D32C-0x8019D388 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000C394(s32);
bool fn_8019D32C(s32 arg0) {
    s32 var_r30;
    void **var_r31;
    Unk_C7387A53 *temp_r9;

    var_r31 = (void **)(arg0 + 0x28);
    for (var_r30 = 0; var_r30 <= 3; var_r30++) {
        temp_r9 = *var_r31;
        var_r31 += 1;
        if (fn_8000C394(temp_r9->unk0x20) != 0) {
            return true;
        }
    }
    return false;
}
