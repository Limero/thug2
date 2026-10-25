// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215E58-0x80215EC4 (108B). Byte-identical.
#include "types.h"
extern char lbl_80305F9C[];
extern char lbl_80305FA0[];
s32 fn_800099AC(s32, s32, s32);
s32 fn_80215F28(void);
s32 fn_80215E58(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305F9C == 0) && (arg0 != 0)) {
        fn_800099AC(0x9A30, 0, 1);
        *(s32 *)&lbl_80305F9C = fn_80215F28();
    }
    *(s32 *)&lbl_80305FA0 += 1;
    return *(s32 *)&lbl_80305F9C;
}
