// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077A9C-0x80077AEC (80B). Byte-identical.
#include "types.h"
extern bool lbl_80377640;
extern char lbl_80377620[];
void fn_800071D4(s32);
s32 fn_80077A9C(void) {
    if (lbl_80377640 == 0) {
        fn_800071D4((s32)lbl_80377620);
        lbl_80377640 = 1;
    }
    return (s32)lbl_80377620;
}
