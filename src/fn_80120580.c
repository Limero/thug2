// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120580-0x801205D0 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302F10;
s32 fn_80015310(void *, s32);
bool fn_80120580(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        return true;
    }
    if (lbl_80302F10 == 0) {
        return false;
    }
    if (fn_80015310(arg0, lbl_80302F10) == 0) {
        return false;
    }
    return true;
}
