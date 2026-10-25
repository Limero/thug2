// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006EBE0-0x8006EC14 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80087284(s32 *);
extern s32 lbl_80366DD8;
void fn_8006EBE0(s32 *arg0) {
    s32 sp8;
    s32 temp_r0;

    temp_r0 = *arg0;
    lbl_80366DD8 = temp_r0;
    sp8 = temp_r0;
    fn_80087284(&sp8);
}
