// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1328-0x801C1364 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801C1328(Unk_C7387A53 *arg0) {
    arg0->unk0x4C = GetChecksum_3(arg0->unk0xC, QB_SKATERPHYSICSCONTROL);
}
