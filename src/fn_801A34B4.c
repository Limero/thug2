// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A34B4-0x801A34EC (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A26E0(s32, s32);
s32 fn_800AB3FC(void *);

s32 fn_801A34B4(s32 arg0) {
    s32 temp_r3;

    temp_r3 = fn_801A26E0(arg0, 0);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_800AB3FC(temp_r3);
}
