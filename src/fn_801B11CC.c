// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B11CC-0x801B126C (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80033594(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801B11CC(CScript *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;

    fn_80033594();
    if (GetInteger(arg1, QB_FLIPPED, &sp8, 0) != 0) {
        arg0->unk0x18 = (sp8 != 0);
    }
    if (GetInteger(arg1, QB_ROTATED, &spC, 0) != 0) {
        arg0->unk0x1C = (spC != 0);
    }
}
