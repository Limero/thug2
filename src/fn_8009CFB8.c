// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CFB8-0x8009D020 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_8030191C;
extern char lbl_80301920[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_8009CFB8(s32 arg0) {
    if ((lbl_8030191C == 0) && (arg0 != 0)) {
        fn_800099AC(0x270, 0, 1);
        lbl_8030191C = fn_8009D084();
    }
    *(s32 *)&lbl_80301920 += 1;
    return lbl_8030191C;
}
