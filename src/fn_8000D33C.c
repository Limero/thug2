// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D33C-0x8000D3DC (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8000EB38(s32, s32);
void fn_8000EB24(void *);
s32 fn_8000CCBC(void *, void *);
bool fn_8000D33C(void *arg0, u8 *arg1) {
    u8 buf[0x80];
    s8 c;
    u8 b;
    u8 *p;
    s32 t;
    p = buf;
    b = *arg1;
    c = *arg1;
    *p = b;
    if (c != 0) {
        do {
            if (*p == 0x2f) {
                *p = 0x5c;
            }
            b = *++arg1;
            c = *arg1;
            *++p = b;
        } while (c != 0);
    }
    fn_8000EB24((void *)*(s32 *)((char *)arg0 + 0x14));
    t = fn_8000EB38(*(s32 *)((char *)arg0 + 0x14), 0);
    if (t != 0) {
        do {
            if (fn_8000CCBC((void *)t, buf) != 0) {
                return true;
            }
            t = fn_8000EB38(*(s32 *)((char *)arg0 + 0x14), 0);
        } while (t != 0);
    }
    return false;
}
