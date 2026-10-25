// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B47E8-0x800B484C (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_800B47E8(Unk_D0BC5E8C *arg0) {
    arg0->unk0x214 = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    arg0->unk0x218 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
    arg0->unk0x21C = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
}
