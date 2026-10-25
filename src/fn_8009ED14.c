// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009ED14-0x8009ED88 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 fn_8009ED14(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 temp_r28;
    s32 temp_r3;
    s32 var_r3;

    temp_r28 = arg0->unk0x28;
    temp_r3 = fn_8009EEAC();
    var_r3 = 0;
    if (temp_r3 != 0) {
        if (ContainsFlag(arg1, QB_CLEAR) != 0) {
            arg0->unk0x28 = (s32) (arg0->unk0x28 & ~temp_r3);
        }
        if (!(temp_r28 & temp_r3)) {
            var_r3 = 0;
        } else {
            var_r3 = 1;
        }
    }
    return var_r3;
}
