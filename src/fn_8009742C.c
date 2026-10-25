// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009742C-0x80097478 (76B). Byte-identical.
#include "types.h"
extern s32 lbl_803018C4;
void fn_80020514(s32, s32, s32);
void fn_8009742C(s32 arg0) {
    if (lbl_803018C4 != arg0) {
        fn_80020514(0xB, arg0, 4);
        lbl_803018C4 = arg0;
    }
}
