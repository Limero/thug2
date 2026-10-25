// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9C70-0x800A9CC0 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

s32 fn_800A9C70(CStruct *arg0) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0, QB_CLASS, &sp8, 0);
    return (sp8 ^ QB_RESTART) == 0;
}
