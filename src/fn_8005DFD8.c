// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DFD8-0x8005E040 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_803C9E18[];
s32 fn_8002428C(void *arg0, s32 arg1);
bool fn_8005DFD8(s32 arg0) {
    void **var_r31;
    void **var_r29;
    void *temp_r3;

    var_r31 = lbl_803C9E18;
    var_r29 = var_r31 + 9;
    do {
        temp_r3 = *var_r31;
        var_r31++;
        if ((temp_r3 != 0) && (fn_8002428C(temp_r3, arg0) != 0)) {
            return true;
        }
    } while (var_r31 <= var_r29);
    return false;
}
