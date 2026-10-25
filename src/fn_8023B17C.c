// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023B17C-0x8023B1B8 (60B). Byte-identical.
#include "types.h"
s32 fn_8023B17C(s32 arg0, s32 arg1) {
    char *p;
    s32 temp_r0;
    s32 i;

    for (i = 1, p = (char *)arg0 + 0x177A8; i != 9; i++) {
        temp_r0 = *(s32 *)p;
        p += 4;
        if (arg1 == temp_r0) {
            return i;
        }
    }
    return 0;
}
