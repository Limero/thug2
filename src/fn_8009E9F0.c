// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E9F0-0x8009EA78 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 fn_8009EEAC(Unk_C7387A53 *, CStruct *, s32);
bool fn_8009E9F0(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    s32 temp_r3;

    if (ContainsFlag(arg1, QB_ALL) != 0) {
        arg0->unk0x28 = 0;
        return true;
    }
    temp_r3 = fn_8009EEAC(arg0, arg1, arg2);
    if (temp_r3 == 0) {
        return false;
    }
    arg0->unk0x28 = (s32) (arg0->unk0x28 & ~temp_r3);
    return true;
}
