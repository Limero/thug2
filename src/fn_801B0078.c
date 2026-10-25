// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0078-0x801B00E0 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_80305F24;
extern char lbl_80305F28[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_801B0E1C(void);
s32 fn_801B0078(s32 arg0) {
    if ((lbl_80305F24 == 0) && (arg0 != 0)) {
        fn_800099AC(0x10, 0, 1);
        lbl_80305F24 = fn_801B0E1C();
    }
    *(s32 *)&lbl_80305F28 += 1;
    return lbl_80305F24;
}
