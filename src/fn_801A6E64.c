// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6E64-0x801A6ECC (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_803A2E50[];
s32 fn_801A6E0C(void *, u32);
s32 fn_801A6E64(void *arg0) {
    s32 *var_r30;
    s32 temp_r0;
    s32 var_r29;
    u32 var_r31;

    var_r30 = (s32 *)lbl_803A2E50;
    var_r29 = 0;
    var_r31 = 0;
    do {
        temp_r0 = *var_r30;
        var_r30 += 1;
        if (temp_r0 == 0) {
            var_r29 += fn_801A6E0C(arg0, var_r31);
        }
        var_r31 += 1;
    } while (var_r31 <= 0x14);
    return var_r29;
}
