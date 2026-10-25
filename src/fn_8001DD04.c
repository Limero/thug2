// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DD04-0x8001DD28 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_CC008000[];
void fn_8001DD04(s32 arg0, s32 arg1, s16 arg2) {
    *(volatile u8 *)&lbl_CC008000 = 0x38;
    *(volatile u16 *)&lbl_CC008000 = arg2;
    *(volatile u16 *)&lbl_CC008000 = (u16) (arg0 | ((arg1 - 1) << 0xc));
}
