// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C6600-0x801C66B4 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_3(Unk_6A70655D *, s32);

void fn_801C6600(Unk_67E10D8C *arg0) {
    arg0->unk0x2AC = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATEHISTORY);
    arg0->unk0x2B8 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
    arg0->unk0x2BC = GetChecksum_3(arg0->unk0xC, QB_SKATERENDRUN);
    arg0->unk0x2B0 = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
    arg0->unk0x2C0 = GetChecksum_3(arg0->unk0xC, QB_SKATERFLIPANDROTATE);
    arg0->unk0x2B4 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    arg0->unk0x2C4 = GetChecksum_3(arg0->unk0xC, QB_SHADOW);
}
