// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC56C-0x801FC5B8 (76B). Byte-identical.
#include "types.h"
extern bool lbl_80305F98;
extern bool lbl_803A30F0[];

bool fn_801FC56C(s32 arg0) {
    s32 i;

    for (i = 0; i < lbl_80305F98; i++) {
        if (arg0 == lbl_803A30F0[i]) {
            return true;
        }
    }
    return false;
}
