// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EDA4-0x8010EE18 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_800F0F84(s32, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);

bool ScriptAppendNodeParams(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    GetChecksum_2(pParams, QB_NODE, &sp8, 1);
    temp_r29 = fn_800F0F84(sp8, 1);
    GetStructure_2(pParams, QB_PARAMS, &spC, 1);
    fn_80126FF4(temp_r29, spC);
    return true;
}
