// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F340C-0x801F348C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_801F340C(u8 *arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    u8 *base;
    u8 *q;

    for (i = 0; i < arg0[0x336]; i++) {
        base = arg0 + 0x32C;
        if (base[i] == arg1) {
            j = i;
            if (j < arg0[0x336] - 1) {
                q = base;
                __asm__("" : "+r"(q));
                k = j + 1;
                do {
                    m = k;
                    q[j] = *(u8 *)(m + (s32)q);
                    k = k + 1;
                    j = m;
                } while (j < arg0[0x336] - 1);
            }
            arg0[0x336] = arg0[0x336] - 1;
            return;
        }
    }
}
