// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A430-0x8003A46C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8003A430(CStruct *arg0) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0, QB_DESC_ID, &sp8, 0);
    return sp8;
}
