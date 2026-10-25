// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0AEC-0x801F0B50 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_801F0AEC(Unk_C7387A53 *arg0) {
    arg0->unk0x34 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_SKATERCOREPHYSICS);
    arg0->unk0x30 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_MODEL);
    arg0->unk0x2C = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_ANIMBLENDER);
}
