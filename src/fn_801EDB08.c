// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EDB08-0x801EDB94 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801EDB08(Unk_C7387A53 *arg0) {
    arg0->unk0x24 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    arg0->unk0x28 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    arg0->unk0x2C = GetChecksum_3(arg0->unk0xC, QB_SHADOW);
    arg0->unk0x30 = GetChecksum_3(arg0->unk0xC, QB_MOVABLECONTACT);
    arg0->unk0x34 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
}
