// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80064618-0x80064640 (40B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
void fn_80064618(void *arg0, s32 arg1) {
    s32 var_r0;
    volatile s32 *p = (volatile s32 *)(char *)arg0;

    if (arg1 != 0) {
        var_r0 = p[0x128 / 4] | 0x10000;
    } else {
        var_r0 = p[0x128 / 4] & QB_UNKNOWN_0xFFFEFFFF;
    }
    p[0x128 / 4] = var_r0;
    p[0x144 / 4] = arg1;
}
