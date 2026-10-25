// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C928-0x8020CA04 (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, u32);
void fn_8020C928(Unk_BF3B342B *arg0) {
    arg0->unk0x183C = GetChecksum_3(arg0->unk0xC, QB_INPUT);
    arg0->unk0x1840 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
    arg0->unk0x1844 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    arg0->unk0x1848 = GetChecksum_3(arg0->unk0xC, QB_TRIGGER);
    arg0->unk0x184C = GetChecksum_3(arg0->unk0xC, QB_SKATERPHYSICSCONTROL);
    arg0->unk0x1850 = GetChecksum_3(arg0->unk0xC, QB_MOVABLECONTACT);
    arg0->unk0x1854 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
    arg0->unk0x1858 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    arg0->unk0x185C = GetChecksum_3(arg0->unk0xC, QB_TAGGINGCONTROL);
}
