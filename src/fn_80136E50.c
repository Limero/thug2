// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136E50-0x80136EB8 (104B). Byte-identical.
#include "types.h"
extern char lbl_80303448[];
extern char lbl_8030344C[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_80137434(void);
s32 fn_80136E50(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80303448 == 0) && (arg0 != 0)) {
        fn_800099AC(0x2390, 0, 1);
        *(s32 *)&lbl_80303448 = fn_80137434();
    }
    *(s32 *)&lbl_8030344C += 1;
    return *(s32 *)&lbl_80303448;
}
