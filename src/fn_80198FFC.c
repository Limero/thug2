// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198FFC-0x8019903C (64B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80198FFC(s32 arg0) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0 + 4, QB_TEAM_GRAFFITI_MODE, &sp8, 0);
    return sp8;
}
