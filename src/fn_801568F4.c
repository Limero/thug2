// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801568F4-0x80156930 (60B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
extern s32 fn_801745B4(s32);
extern s32 fn_801403CC(void *);
s32 fn_801568F4(void) {
    s32 temp_r3;

    temp_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
    if (temp_r3 == 0) {
        return 0;
    }
    return fn_801403CC(temp_r3);
}
