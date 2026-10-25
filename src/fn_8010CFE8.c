// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010CFE8-0x8010D064 (124B). Byte-identical.
#include "types.h"
extern char lbl_80301A38[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A1AE8(void *, void *, void *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetArray(CStruct *, void *, s32 *, void *);
bool ScriptCreateCompositeObject(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetArray(pParams, QB_COMPONENTS, &sp8, 1);
    spC = 0;
    GetStructure_2(pParams, QB_PARAMS, &spC, 0);
    fn_800A1AE8(*(s32 *)&lbl_80301A38, sp8, spC, 1);
    return true;
}
