// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800966D8-0x800966F8 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800966D8(f32 *arg0, f32 *arg1) {
    f32 temp_f13;
    f32 temp_f0;
    s32 r;

    temp_f13 = arg0[1];
    temp_f0 = arg1[1];
    r = temp_f13 > temp_f0;
    if (!(temp_f13 < temp_f0)) {
        return r;
    }
    return -1;
}
