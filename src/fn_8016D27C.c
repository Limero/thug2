// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D27C-0x8016D2E4 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_80305EA4;
extern char lbl_80305EA8[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_8016D348(void);
s32 fn_8016D27C(s32 arg0) {
    if ((lbl_80305EA4 == 0) && (arg0 != 0)) {
        fn_800099AC(0x360, 0, 1);
        lbl_80305EA4 = fn_8016D348();
    }
    *(s32 *)&lbl_80305EA8 += 1;
    return lbl_80305EA4;
}
