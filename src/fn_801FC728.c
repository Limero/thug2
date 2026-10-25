// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC728-0x801FC760 (56B). Byte-identical.
#include "types.h"
bool fn_801FC728(s32 arg0, s32 *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        if (arg0 == arg1[i]) {
            return true;
        }
    }
    return false;
}
