// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001AE94-0x8001AED8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern bool lbl_80300174;
extern s32 lbl_80320F48;
extern void (*lbl_80320F4C)(s32);

void fn_8001AE94(s32 arg0) {
    void (*callback)(s32) = lbl_80320F4C;

    lbl_80300174 = 1;
    lbl_80320F48 = arg0;
    callback(arg0);
}
