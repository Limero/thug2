// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80270254-0x80270290 (60B). Byte-identical.
#include "types.h"
f64 fn_80270254(f64 arg0) {
    volatile union { f64 d; u32 w[2]; } t;
    register f64 y __asm__("fr0");
    register f64 r __asm__("fr0");
    register u32 h __asm__("r11");
    register u32 l __asm__("r12");
    register u32 l2 __asm__("r10");
    register u32 h2 __asm__("r9");
    register u32 m __asm__("r9");

    y = arg0;
    __asm__("" : "+f"(y));
    t.d = y;
    h = t.w[0];
    l = t.w[1];
    t.d = arg0;
    h2 = t.w[0];
    l2 = t.w[1];
    m = h & 0x7FFFFFFFu;
    t.w[0] = m;
    t.w[1] = l2;
    r = t.d;
    return r;
}
