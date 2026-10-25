// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD574-0x801CD68C (280B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801CD574(Unk_8C41D852 *arg0) {
    arg0->unk0x15A0 = GetChecksum_3(arg0->unk0xC, QB_INPUT);
    arg0->unk0x15A8 = GetChecksum_3(arg0->unk0xC, QB_SKATERSOUND);
    arg0->unk0x15A4 = GetChecksum_3(arg0->unk0xC, QB_TRIGGER);
    arg0->unk0x15AC = GetChecksum_3(arg0->unk0xC, QB_TRICK);
    arg0->unk0x15B0 = GetChecksum_3(arg0->unk0xC, QB_SKATERROTATE);
    arg0->unk0x15B4 = GetChecksum_3(arg0->unk0xC, QB_SKATERSCORE);
    arg0->unk0x15B8 = GetChecksum_3(arg0->unk0xC, QB_SKATERBALANCETRICK);
    arg0->unk0x15BC = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
    arg0->unk0x15C0 = GetChecksum_3(arg0->unk0xC, QB_MOVABLECONTACT);
    arg0->unk0x15C4 = GetChecksum_3(arg0->unk0xC, QB_SKATERPHYSICSCONTROL);
    arg0->unk0x15C8 = GetChecksum_3(arg0->unk0xC, QB_WALK);
    arg0->unk0x15CC = GetChecksum_3(arg0->unk0xC, QB_TAGGINGCONTROL);
}
