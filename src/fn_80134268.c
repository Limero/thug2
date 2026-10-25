// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134268-0x801342D0 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_8030342C;
extern s32 lbl_80303430;
s32 fn_800099AC(s32, s32, s32);
s32 fn_801343B4(void);
s32 fn_80134268(s32 arg0) {
    if ((lbl_8030342C == 0) && (arg0 != 0)) {
        fn_800099AC(0x28, 0, 1);
        lbl_8030342C = fn_801343B4();
    }
    lbl_80303430 += 1;
    return lbl_8030342C;
}
