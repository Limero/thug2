// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7FD0-0x801A8038 (104B). Byte-identical.
#include "types.h"
extern char lbl_80305F1C[];
extern s32 lbl_80305F20;
s32 fn_800099AC(s32, s32, s32);
s32 fn_801A871C(void);
s32 fn_801A7FD0(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305F1C == 0) && (arg0 != 0)) {
        fn_800099AC(0x40, 0, 1);
        *(s32 *)&lbl_80305F1C = fn_801A871C();
    }
    lbl_80305F20 += 1;
    return *(s32 *)&lbl_80305F1C;
}
