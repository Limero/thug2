// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018CA50-0x8018CAD0 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801745B4(s32);
s32 fn_8021B574(s32);
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
bool fn_8018CA50(Unk_C7387A53 *arg0) {
    s32 g;

    g = lbl_80305F9C;
    if (fn_801745B4(lbl_80305EAC) == 0) {
        return true;
    }
    if (fn_8021B574(g) == 0) {
        return true;
    }
    if (arg0->unk0x70 & 0x80000) {
        return false;
    }
    if (arg0->unk0x54 <= 0) {
        return true;
    }
    return false;
}
