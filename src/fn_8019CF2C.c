// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019CF2C-0x8019CF94 (104B). Byte-identical.
#include "types.h"
extern char lbl_80305EE4[];
extern s32 lbl_80305EE8;
s32 fn_800099AC(s32, s32, s32);
s32 fn_8019D00C(void);
s32 fn_8019CF2C(s32 arg0) {
    if (((s32) *(s32 *)&lbl_80305EE4 == 0) && (arg0 != 0)) {
        fn_800099AC(0x19C, 0, 1);
        *(s32 *)&lbl_80305EE4 = fn_8019D00C();
    }
    lbl_80305EE8 += 1;
    return *(s32 *)&lbl_80305EE4;
}
