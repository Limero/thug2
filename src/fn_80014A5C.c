// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014A5C-0x80014ABC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80314330[];
extern s32 fn_8001B5B8(char *arg0);
void fn_80014A5C(s32 arg0, s32 arg1) {
    char *p;
    u32 n;

    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            p = lbl_80314330;
            n = 2;
            do {
                fn_8001B5B8(p + 0x84);
                p += 0xFC;
            } while (n-- != 0);
        }
    }
}
