// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C96C-0x8009C9D4 (104B). Byte-identical.
#include "types.h"
extern s32 lbl_80301914;
extern char lbl_80301918[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_8009C96C(s32 arg0) {
    if ((lbl_80301914 == 0) && (arg0 != 0)) {
        fn_800099AC(0x24, 0, 1);
        lbl_80301914 = fn_8009CA38();
    }
    *(s32 *)&lbl_80301918 += 1;
    return lbl_80301914;
}
