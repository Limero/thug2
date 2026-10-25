// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E5DC-0x8001E66C (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern void (*lbl_80300280)(u32);
void fn_8001E5DC(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    lbl_80300280(0xFEFFFFF0);
    lbl_80300280((arg1 * 0x10) | (arg2 << 9) | (arg3 << 0xE) | (arg4 << 0x13) | (((((s32)arg0 + (s32)(arg0 >> 0x1FU)) >> 1) + 0xF6) << 0x18));
}
