// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004A3F8-0x8004A460 (104B). Byte-identical.
#include "types.h"
extern char lbl_80300434[];
extern s32 lbl_80300438;
s32 fn_800099AC(s32, s32, s32);
s32 fn_8004A3F8(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80300434 == 0) && (arg0 != 0)) {
        fn_800099AC(0x780, 0, 1);
        *(s32 *)&lbl_80300434 = fn_8004A4D8();
    }
    lbl_80300438 += 1;
    return *(s32 *)&lbl_80300434;
}
