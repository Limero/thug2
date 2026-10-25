// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F0A0-0x8001F0F4 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void (*lbl_80300260)(u8);
extern void (*lbl_80300268)(s32);
void fn_8001F0A0(s32 arg0, s32 arg1, s32 arg2) {
    lbl_80300260((u8)(arg1 | arg0));
    lbl_80300268(arg2);
}
