// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B29F8-0x801B2A4C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_801B29F8(Unk_6A70655D *);
bool fn_801B29F8(Unk_6A70655D *arg0) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
    temp_r3->unk0x20 = (s32) (temp_r3->unk0x20 | 4);
    arg0->unk0xE0 = 1;
    return true;
}
