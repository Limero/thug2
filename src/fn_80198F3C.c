// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198F3C-0x80198F7C (64B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80198F3C(s32 arg0) {
    s32 sp8;

    sp8 = 0;
    fn_80128C80(arg0 + 4, QB_ROUND, &sp8, 0);
    return sp8;
}
