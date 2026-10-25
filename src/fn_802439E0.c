// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802439E0-0x80243A48 (104B). Byte-identical.
#include "types.h"
bool fn_802439E0(s32 arg0, s32 arg1, s32 *arg2) {
    s32 *p;
    s32 i;
    s32 n;

    p = (s32 *)((char *)arg0 + 0x84);
    i = 0;
    for (n = 0x20; n != 0; n--) {
        s32 slot = *(s32 *)((char *)p - 0x80);
        if (slot != 0) {
            s32 flags = *p;
            s32 sel = (flags == 0);
            s32 *e = (s32 *)(slot + 0x14);
            if (e[sel] == arg1) {
                if (arg2 != 0) {
                    *arg2 = i;
                }
                return true;
            }
        }
        p += 1;
        i += 1;
    }
    return false;
}
