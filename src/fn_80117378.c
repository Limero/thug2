// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117378-0x80117418 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126FF4(s32, s32);
s32 GetStructure(s32, s32);
void fn_80127CD4(s32, s32, s32);
bool ScriptAppendStruct(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 temp;
    GetChecksum_2(pParams, QB_STRUCT, &sp8, 1);
    GetChecksum_2(pParams, QB_FIELD, &spC, 1);
    GetStructure_2(pParams, QB_PARAMS, &sp10, 1);
    temp = CStruct_ctor(CStruct_new(8));
    fn_80126FF4(temp, sp10);
    fn_80127CD4(GetStructure(sp8, 1), spC, temp);
    return true;
}
