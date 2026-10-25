// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800725FC-0x80072660 (100B). Byte-identical.
#include "types.h"
extern s8 lbl_8030160C;
extern s8 lbl_8030160D;
void fn_800725FC(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 >= 0) {
        lbl_8030160C = ((arg1 << 8) - arg1) / 100;
    }
    if (arg2 >= 0) {
        lbl_8030160D = ((arg2 << 8) - arg2) / 100;
    }
}
