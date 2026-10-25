// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1874-0x800A18DC (104B). Byte-identical.
#include "types.h"
extern char lbl_80301A38[];
extern s32 lbl_80301A3C;
s32 fn_800099AC(s32, s32, s32);
s32 fn_800A1874(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80301A38 == 0) && (arg0 != 0)) {
        fn_800099AC(0x454, 0, 1);
        *(s32 *)&lbl_80301A38 = fn_800A1954();
    }
    lbl_80301A3C += 1;
    return *(s32 *)&lbl_80301A38;
}
