// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B6F48-0x801B6F8C (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
// AdjustSpeed @ 0x801B6F48
void AdjustSpeed(Unk_C7387A53 *arg0, f32 farg0) {
    volatile double _dummy;
    Unk_C7387A53 *temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
    *((f32 *)&temp_r3->unk0x30) = (f32) (*((f32 *)&temp_r3->unk0x30) * farg0);
}
