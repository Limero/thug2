// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C4F0C-0x801C4F64 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);

void fn_801C4F0C(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r3;

    arg0->unk0x34 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
    arg0->unk0x38 = temp_r3;
    temp_r3->unk0x20 = -1;
}
