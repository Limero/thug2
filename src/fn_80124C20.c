// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80124C20-0x80124C88 (104B). Byte-identical.
#include "types.h"
extern char lbl_80303148[];
extern char lbl_8030314C[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_80124CEC(void);
s32 fn_80124C20(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80303148 == 0) && (arg0 != 0)) {
        fn_800099AC(0x100, 0, 1);
        *(s32 *)&lbl_80303148 = fn_80124CEC();
    }
    *(s32 *)&lbl_8030314C += 1;
    return *(s32 *)&lbl_80303148;
}
