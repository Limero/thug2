// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C59EC-0x801C5A3C (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);

void fn_801C59EC(Unk_C7387A53 *arg0) {
    arg0->unk0x40 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
    arg0->unk0x44 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
}
