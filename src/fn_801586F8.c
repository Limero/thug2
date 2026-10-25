// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801586F8-0x8015876C (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 fn_801A5D9C(void *, void *);
extern char lbl_80305EFC[];
bool ScriptSetSkaterProfileInfo(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    GetStructure_2(pParams, QB_PARAMS, &spC, 1);
    fn_80126FF4(fn_801A5D9C(*(s32 *)&lbl_80305EFC, sp8) + 0x6C, spC);
    return true;
}
