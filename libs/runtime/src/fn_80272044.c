// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80272044-0x80272094 (80B). Byte-identical.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
f64 fn_80272044(f64 arg0, f64 arg1) {
    volatile union { f64 d; u32 w[2]; } t;
    register f64 y __asm__("fr0");
    register f64 r __asm__("fr0");
    register u32 h __asm__("r7");
    register u32 l __asm__("r8");
    register u32 h2 __asm__("r9");
    register u32 l2 __asm__("r10");
    register u32 h3 __asm__("r11");
    register u32 l3 __asm__("r12");
    register u32 m __asm__("r11");

    y = arg0;
    __asm__("" : "+f"(y));
    t.d = y;
    h = t.w[0];
    l = t.w[1];
    t.d = arg1;
    h2 = t.w[0];
    l2 = t.w[1];
    t.d = arg0;
    h3 = t.w[0];
    l3 = t.w[1];
    h &= 0x7FFFFFFFu;
    m = h | (h2 & 0x80000000u);
    t.w[0] = m;
    t.w[1] = l3;
    r = t.d;
    return r;
}
