// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9EC8-0x801B9F08 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_801B9EC8(Unk_C7387A53 *);
bool fn_801B9EC8(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
    if (temp_r3 != NULL) {
        *((f32 *)&temp_r3->unk0x34) = (f32) *((f32 *)&temp_r3->unk0x30);
    }
    return true;
}
