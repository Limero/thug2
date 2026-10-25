// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002FB24-0x8002FBA8 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8002DE6C(s32);
s32 fn_8002FB24(void *arg0) {
    s32 *p = *(s32 **)((char *)arg0 + 0x24);
    s32 cond;
    s32 a;
    s32 b;
    s32 c1;
    s32 c2;
    cond = p[1] + 1 == 0;
    a = (s32)p;
    if (cond) {
        a = 0;
    }
    c1 = (a != 0) ? a - 4 : 0;
    if (c1 == 0) {
        return 0;
    }
    b = (s32)p;
    if (cond) {
        b = 0;
    }
    c2 = (b != 0) ? b - 4 : 0;
    return fn_8002DE6C(c2 + 4);
}
