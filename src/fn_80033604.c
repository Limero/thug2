// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033604-0x80033644 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_800335E0(s32);
s32 GetChecksum_3(s32, s32);
s32 fn_800C9780(s32);
s32 fn_80033604(s32 arg0) {
    s32 temp_r3;

    temp_r3 = GetChecksum_3(fn_800335E0(arg0), QB_SKELETON);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_800C9780(temp_r3);
}
