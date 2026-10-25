// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5880-0x801A58E8 (104B). Byte-identical.
#include "types.h"
extern char lbl_80305EFC[];
extern char lbl_80305F00[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_801A594C(void);
s32 fn_801A5880(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305EFC == 0) && (arg0 != 0)) {
        fn_800099AC(0x48, 0, 1);
        *(s32 *)&lbl_80305EFC = fn_801A594C();
    }
    *(s32 *)&lbl_80305F00 += 1;
    return *(s32 *)&lbl_80305EFC;
}
