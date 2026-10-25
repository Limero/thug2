// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F206C-0x800F20D4 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_80301B48;
extern s32 lbl_80301B4C;
s32 fn_800099AC(s32, s32, s32);
s32 fn_800F214C(void);
s32 fn_800F206C(s32 arg0) {
    if ((lbl_80301B48 == 0) && (arg0 != 0)) {
        fn_800099AC(0x44, 0, 1);
        lbl_80301B48 = fn_800F214C();
    }
    lbl_80301B4C += 1;
    return lbl_80301B48;
}
