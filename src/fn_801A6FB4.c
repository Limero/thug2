// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6FB4-0x801A6FDC (40B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801A6FB4(s32 arg0, s32 arg1) {
    char *p = (char *)(arg0 + 0x5F0);
    *(u32 *)(p + ((arg1 >> 5) << 2)) &= ~(1u << (arg1 & 0x1F));
}
