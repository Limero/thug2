// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0AFC-0x800F0B38 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F0AFC(CStruct *arg0) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0, QB_NAME, &sp8, 0);
    return sp8;
}
