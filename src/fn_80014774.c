// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014774-0x800147E8 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_8000DE40();
s32 fn_8000DE5C();
s32 fn_8000DE68(void *);
void fn_8001B5B8(Unk_A07EDCEF *);
s32 fn_8001B788(void *, s32);

s32 fn_80014774(void *arg0) {
    Unk_A07EDCEF sp8;
    s32 temp_r30;

    if (fn_8000DE40() != 0) {
        temp_r30 = fn_8000DE68(arg0);
        if (fn_8000DE5C() != 0) {
            return temp_r30;
        }
    }
    fn_8001B5B8(&sp8);
    return fn_8001B788(&sp8, arg0) != 0;
}
