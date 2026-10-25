// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC770-0x800CC7D4 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800CC770(Unk_C7387A53 *arg0) {
    arg0->unk0x34 = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
    arg0->unk0x38 = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    arg0->unk0x3C = GetChecksum_3(arg0->unk0xC, QB_MODEL);
}
