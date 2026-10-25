// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B9C8-0x8001BA04 (60B). Byte-identical.
#include "types.h"
extern bool lbl_80300180;
void fn_8001DFF4(void);
void GX_SetZMode(s32, s32, s32);
void fn_8001B9C8(void) {
    GX_SetZMode(1, 3, 1);
    lbl_80300180 = 0;
    fn_8001DFF4();
}
