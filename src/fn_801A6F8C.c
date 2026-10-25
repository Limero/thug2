// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6F8C-0x801A6FB4 (40B). Byte-identical.
#include "types.h"
void fn_801A6F8C(s32 arg0, s32 arg1) {
    s32 *base;
    s32 idx;
    s32 *p;

    base = (s32 *)(arg0 + 0x5F0);
    idx = arg1 >> 5;
    p = base + idx;
    *p = *p | (1 << (arg1 & 0x1F));
}
