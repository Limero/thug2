// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80273384-0x802733B8 (52B). Byte-identical.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
f32 fn_80273384(f32 arg0, f32 arg1) {
    volatile f32 x;
    u32 a, b;
    register f32 r __asm__("fr0");

    x = arg0;
    a = *(volatile u32 *)&x;
    x = arg1;
    b = *(volatile u32 *)&x;
    *(volatile u32 *)&x = (a & 0x7FFFFFFFu) | (b & 0x80000000u);
    r = x;
    return r;
}
