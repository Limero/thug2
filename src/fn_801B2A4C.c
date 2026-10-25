// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2A4C-0x801B2AB4 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_801B2A4C(Unk_6A70655D *);
bool fn_801B2A4C(Unk_6A70655D *arg0) {
    s32 var_r0;
    Unk_C7387A53 *temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
    if (temp_r3 != NULL) {
        if ((s32) arg0->unk0xE0 != 0) {
            var_r0 = temp_r3->unk0x20 | 4;
        } else {
            var_r0 = temp_r3->unk0x20 & QB_UNKNOWN_0xFFFFFFFB;
        }
        temp_r3->unk0x20 = var_r0;
    }
    return true;
}
