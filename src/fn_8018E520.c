// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E520-0x8018E584 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 strcasecmp(s32, s32);
s32 fn_8018E520(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r3;
    s32 var_r3;

    if (GetString(arg0->unk0x20, QB_PROSET_PREFIX, &sp8, 0) != 0) {
        temp_r3 = strcasecmp(sp8, arg1);
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto block_4;
        }
    } else {
block_4:
        var_r3 = 0;
    }
    return var_r3;
}
