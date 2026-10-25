// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80082EB8-0x80082F38 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80082D8C(s32, s32, s32, s32);
bool fn_80082EB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (fn_80082D8C(arg0, arg1, arg2, arg3) != 0) {
        if (fn_80082D8C(arg0, arg2, arg1, arg3) != 0) {
            if (fn_80082D8C(arg0, arg3, arg1, arg2) != 0) {
                return true;
            }
        }
    }
    return false;
}
