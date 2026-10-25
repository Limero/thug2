// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C2320-0x801C2398 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801C2320(CStruct *arg0) {
    arg0->unk0x54 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    arg0->unk0x58 = GetChecksum_3(arg0->unk0xC, QB_SKATERBALANCETRICK);
    arg0->unk0x5C = GetChecksum_3(arg0->unk0xC, QB_SKATERPHYSICSCONTROL);
    arg0->unk0x60 = GetChecksum_3(arg0->unk0xC, QB_WALK);
}
