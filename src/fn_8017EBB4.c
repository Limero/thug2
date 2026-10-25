// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017EBB4-0x8017EBFC (72B). Byte-identical.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
void fn_8017EBB4(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *d = arg1;
    u8 *s = arg2;
    u8 c = *s;
    while (c != 0) {
        if (c == 0x20) {
            *d = 0x5C;
            *++d = 0x5F;
        } else {
            *d = c;
        }
        d++;
        c = *++s;
    }
    *d = 0;
}
