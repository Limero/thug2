// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FE5D0-0x801FE60C (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801FE5D0(Unk_C7387A53 *arg0) {
    arg0->unk0x28 = GetChecksum_3(arg0->unk0xC, QB_WALK);
}
