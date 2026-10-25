// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7178-0x801A71DC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetInteger(s32, s32, s32 *, s32);
void AddInteger(s32, s32, s32);
void fn_801A7178(Unk_93C2DF4D *arg0, s32 arg1) {
    s32 sp8;

    GetInteger(arg0->unk0x6E4, QB_POINTS_AVAILABLE, &sp8, 1);
    sp8 += arg1;
    AddInteger(arg0->unk0x6E4, QB_POINTS_AVAILABLE, sp8);
}
