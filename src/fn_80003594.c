// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003594-0x800035FC (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 Mth_Rnd(s32 scale);

extern f32 lbl_8028FB88;

float Mth_PlusOrMinus(float arg)
{
    volatile double _dummy;
    float r = (float)Mth_Rnd(10000);
    r -= lbl_8028FB88;
    return arg * r / lbl_8028FB88;
}
