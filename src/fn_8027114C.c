// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8027114C-0x80271170 (36B). Byte-identical.
#include "types.h"
f32 fn_8027114C(f32 arg0) {
    volatile f32 x;
    register f32 r __asm__("fr0");

    x = arg0;
    *(volatile u32 *)&x &= 0x7FFFFFFFu;
    r = x;
    return r;
}
