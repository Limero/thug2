// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0740-0x800F078C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 fn_800F0F84(s32, s32);
extern void fn_800F06A8(s32, s32);

void fn_800F0740(s32 arg0, s32 arg1) {
    s32 t = fn_800F0F84(arg0, 1);

    fn_800F06A8(t, fn_800F0F84(arg1, 1));
}
