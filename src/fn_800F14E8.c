// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F14E8-0x800F1554 (108B). Byte-identical.
#include "types.h"
extern s32 lbl_80301B40;
extern char lbl_80301B44[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_800F15B8(void);
s32 fn_800F14E8(s32 arg0) {
    if ((lbl_80301B40 == 0) && (arg0 != 0)) {
        fn_800099AC(0x10100, 0, 1);
        lbl_80301B40 = fn_800F15B8();
    }
    *(s32 *)&lbl_80301B44 += 1;
    return lbl_80301B40;
}
