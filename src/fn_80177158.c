// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80177158-0x801771C8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009CFA0(s32);
extern char lbl_80305F9C[];
bool fn_80177158(Unk_7258DEBD *arg0) {
    s32 temp_r3;

    if (fn_8009CFA0(*(s32 *)&lbl_80305F9C) != 0) {
        return true;
    }
    temp_r3 = arg0->unk0x384;
    if ((temp_r3 == -QB_UNKNOWN_0x16D13502) || (temp_r3 == QB_LOAD_CAS)) {
        return true;
    }
    return false;
}
