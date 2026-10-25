// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2E28-0x801A2E88 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A269C(void *arg0);
s32 fn_801A275C(void *arg0, s32 arg1);

s32 fn_801A2E28(Unk_31DE137E *arg0, s32 arg1) {
    s32 temp_r3;
    s32 var_r3;

    if (fn_801A269C(arg0) == 0) {
        var_r3 = 1;
    } else if (arg1 == 0) {
        var_r3 = 0;
    } else {
        temp_r3 = fn_801A275C(arg0, arg1);
        var_r3 = (temp_r3 == 0);
    }
    return var_r3;
}

// Parked after random matching: compiler register allocation and branch
// scheduling differ in the short conditional path; current body is retained.

