// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DE68-0x8000DEBC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8000D33C(s32, s32);
extern s32 lbl_802FFE84;
extern s32 lbl_802FFE88;
bool fn_8000DE68(void *arg0) {
    s32 temp_r3;

    temp_r3 = fn_8000D33C(lbl_802FFE84, arg0);
    if (temp_r3 != 0) {
        lbl_802FFE88 = 1;
        return true;
    }
    lbl_802FFE88 = 0;
    return false;
}
