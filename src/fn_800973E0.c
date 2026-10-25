// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800973E0-0x8009742C (76B). Byte-identical.
#include "types.h"
extern s32 lbl_803018C0;
void fn_80020514(s32, s32, s32);
void fn_800973E0(s32 arg0) {
    if (lbl_803018C0 != arg0) {
        fn_80020514(9, arg0, 0xC);
        lbl_803018C0 = arg0;
    }
}
