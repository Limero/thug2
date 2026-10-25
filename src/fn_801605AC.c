// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801605AC-0x80160620 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009D364(void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
extern void * lbl_8030191C;

bool ScriptControllerBoundToSkater(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    GetInteger(pParams, QB_CONTROLLER, &sp8, (s32 *)1);
    GetInteger(pParams, (s32 *)QB_SKATER, &spC, 1);
    temp_r3 = fn_8009D364(lbl_8030191C, spC) ^ sp8;
    return temp_r3 == 0;
}
