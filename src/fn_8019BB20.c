// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019BB20-0x8019BB98 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8017471C(s32, s32);
extern char lbl_80305EAC[];
bool fn_8019BB20(s32 arg0) {
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 8; var_r30 += 1) {
        if (fn_8017471C(*(s32 *)&lbl_80305EAC, var_r30) != 0 && *(u32 *)(arg0 + 0x410 + var_r30 * 4) >= strlen((char *)(arg0 + 0x10))) {
            return true;
        }
    }
    return false;
}