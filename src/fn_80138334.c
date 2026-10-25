// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138334-0x80138400 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80138334(u8 *src, s32 len, u8 *dst, s32 *cap) {
    u8 cmd;
    u8 n;
    u32 run;
    s32 out;
    out = 0;
    if (len != 0) {
        do {
            cmd = *src++;
            len--;
            if ((cmd & 0x80) == 0) {
                n = 0;
                if (n <= cmd) {
                    do {
                        if (out >= *cap) return -1;
                        out++;
                        *dst++ = *src++;
                        n++;
                        len--;
                    } while (n <= cmd);
                }
            } else {
                run = (cmd & 0x7F) + 2;
                n = 0;
                if (n < run) {
                    do {
                        if (out >= *cap) return -1;
                        *dst++ = *src;
                        out++;
                        n++;
                    } while (n < run);
                }
                src++;
                len--;
            }
        } while (len != 0);
    }
    *cap = out;
    return 0;
}
