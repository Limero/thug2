// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EDE0-0x8001EE4C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void (*lbl_80300280)(u32);

void fn_8001EDE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 a = arg0 * 2;
    u32 hi = ((a + 0x30) << 24) | 0xC0000;

    lbl_80300280((arg2 - 1) | hi);
    lbl_80300280((arg3 - 1) | ((a + 0x31) << 24));
}
