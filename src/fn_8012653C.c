// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012653C-0x80126620 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_8012653C(u8 *arg0, s32 arg1, s32 (*arg2)(s32, char *)) {
    u8 *end;
    u8 *p;
    s32 i;
    s32 n;
    s32 v;
    s32 c;
    u8 c2;
    end = arg0 + arg1;
    p = arg0;
    while (p != end) {
        char buf[0x100];
        p += 2;
        v = 0;
        for (i = 0; i < 8; i++) {
            c = (s8)*p++;
            if ((u32)(c - 0x30) <= 9) {
                c = c - 0x30;
            } else if ((u32)(c - 0x61) <= 5) {
                c = c - 0x57;
            } else if ((u32)(c - 0x41) <= 5) {
                c = c - 0x37;
            }
            v = (v << 4) + c;
        }
        c2 = *++p;
        n = 0;
        if (c2 != '\r') {
            do {
                buf[n++] = c2;
                c2 = *++p;
            } while (c2 != '\r');
        }
        buf[n] = 0;
        p += 2;
        arg2(v, buf);
    }
}
