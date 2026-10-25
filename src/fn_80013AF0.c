// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013AF0-0x80013B58 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_802FFF24;
extern s32 lbl_802FFF28;
s32 fn_800099AC(s32, s32, s32);
s32 fn_80013AF0(s32 arg0) {
    if ((lbl_802FFF24 == 0) && (arg0 != 0)) {
        fn_800099AC(0x1C, 0, 1);
        lbl_802FFF24 = fn_80013BD0();
    }
    lbl_802FFF28 += 1;
    return lbl_802FFF24;
}
