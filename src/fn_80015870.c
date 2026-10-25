// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015870-0x800158D8 (104B). Byte-identical.
#include "types.h"
extern char lbl_802FFF6C[];
extern char lbl_802FFF70[];
s32 fn_800099AC(s32, s32, s32);
// BannerCheck @ 0x80015870
s32 BannerCheck(s32 arg0) {
    if (((s32) *(s32 *)&lbl_802FFF6C == 0) && (arg0 != 0)) {
        fn_800099AC(0x2C, 0, 1);
        *(s32 *)&lbl_802FFF6C = fn_800159B4();
    }
    *(s32 *)&lbl_802FFF70 += 1;
    return *(s32 *)&lbl_802FFF6C;
}
