// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019A448-0x8019A49C (84B). Byte-identical.
#include "types.h"
s32 fn_8019A448(s32 a0, s32 arg1) {
    register s32 p __asm__("r9");
    register s32 best __asm__("r3");
    s32 v;
    s32 second;
    s32 n;
    s32 t;
    p = a0;
    best = 0;
    second = 0;
    if (arg1 + 1 > 0) {
        t = arg1; __asm__ volatile("" : "+r"(t)); n = t + 1;
        p += 0x14;
        do {
            v = *(s32 *)p;
            p += 4;
            if (v > best) { second = best; best = v; }
            else if (v > second) { second = v; }
        } while (--n != 0);
    }
    return best + second;
}
