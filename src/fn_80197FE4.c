// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80197FE4-0x8019804C (104B). Byte-identical.
#include "types.h"
extern char lbl_80305EC0[];
extern s32 lbl_80305EC4;
s32 fn_800099AC(s32, s32, s32);
s32 fn_801982D4(void);
s32 fn_80197FE4(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305EC0 == 0) && (arg0 != 0)) {
        fn_800099AC(0x28, 0, 1);
        *(s32 *)&lbl_80305EC0 = fn_801982D4();
    }
    lbl_80305EC4 += 1;
    return *(s32 *)&lbl_80305EC0;
}
