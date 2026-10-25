// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ECD98-0x800ECDFC (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800ECD98(Unk_C7387A53 *arg0) {
    arg0->unk0x24 = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
    arg0->unk0x28 = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    arg0->unk0x2C = GetChecksum_3(arg0->unk0xC, QB_MODEL);
}
