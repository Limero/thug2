// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FBCC-0x8001FC74 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern void (*lbl_80300280)(u32);
// SetTevSwapModeTable @ 0x8001FBCC
void SetTevSwapModeTable(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 hi = arg0;
    lbl_80300280(QB_UNKNOWN_0xFE00000F);
    hi = hi * 2;
    lbl_80300280((arg1 | (arg2 << 2)) | ((hi + 0xF6) << 0x18));
    lbl_80300280(QB_UNKNOWN_0xFE00000F);
    lbl_80300280((arg3 | (arg4 << 2)) | ((hi + 0xF7) << 0x18));
}
