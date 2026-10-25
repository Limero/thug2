// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801213D0-0x801213FC (44B). Byte-identical.
#include "types.h"
extern s32 lbl_80302F28;
extern char lbl_8039D9F4[];
bool fn_801213D0(void) {
    if (lbl_80302F28 != 0) {
        if ((s32) *(s32 *)&lbl_8039D9F4 != 0) {
            return true;
        }
    }
    return false;
}
