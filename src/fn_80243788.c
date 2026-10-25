// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243788-0x802437C0 (56B). Byte-identical.
#include "types.h"
s32 fn_80243788(s32 arg0) {
    s32 *p;
    s32 i;
    s32 n;

    p = (s32 *)((char *)arg0 + 4);
    i = 0;
    for (n = 0x20; n != 0; n--) {
        if (*p++ == 0) {
            return i;
        }
        i += 1;
    }
    return -1;
}
