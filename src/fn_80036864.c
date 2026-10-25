// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036864-0x800368FC (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_8003A31C(void *);
s32 fn_8003A334(void *, s32);
s32 fn_8003A344(void *, s32);

void fn_80036864(void *arg0, void *arg1) {
    s32 i;
    s32 z;
    s32 off;
    s32 *p;
    s32 v;
    s32 t;

    i = 0;
    z = 0;
    off = 0;
    while (i < fn_8003A31C(arg1)) {
        s32 c;
        c = fn_8003A334(arg1, i);
        v = 0;
        if (c != 0) {
            v = fn_8003A344(arg1, i);
        }
        p = (s32 *)((char *)*(s32 *)((char *)arg0 + 0x18) + off);
        t = *(s32 *)((char *)arg0 + 4);
        p[1] = t + (v << 6);
        p[2] = z;
        off += 0x20;
        i++;
    }
}
