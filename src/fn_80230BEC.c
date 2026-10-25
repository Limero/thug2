// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230BEC-0x80230C54 (104B). Byte-identical.
#include "types.h"
extern char lbl_80305FF8[];
extern s32 lbl_80305FFC;
s32 fn_800099AC(s32, s32, s32);
s32 fn_80230CCC(void);
s32 fn_80230BEC(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305FF8 == 0) && (arg0 != 0)) {
        fn_800099AC(0x80, 0, 1);
        *(s32 *)&lbl_80305FF8 = fn_80230CCC();
    }
    lbl_80305FFC += 1;
    return *(s32 *)&lbl_80305FF8;
}
