// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F298-0x8001F2D8 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern void (*lbl_80300280)(s32, s32, s32);
// GX_SetZMode @ 0x8001F298
void GX_SetZMode(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r4 = arg1 * 2;
    temp_r5 = arg2 * 0x10;
    (*lbl_80300280)(arg0 | temp_r4 | temp_r5 | QB_UNKNOWN_0x40000000, temp_r4, temp_r5);
}
