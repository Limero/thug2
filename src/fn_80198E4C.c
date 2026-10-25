// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198E4C-0x80198E8C (64B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80198E4C(s32 arg0) {
    s32 sp8;

    sp8 = 3;
    GetInteger(arg0 + 4, QB_FIREBALL_LEVEL, &sp8, 0);
    return sp8;
}
