// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155E44-0x80155EB8 (116B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_801771D4(Unk_F8CDD391 *, void *, Unk_C8FEE62D *);
bool ScriptSetTesterScript(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    spC = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    GetStructure_2(pParams, QB_PARAMS, &spC, 0);
    fn_801771D4(*(s32 *)&lbl_80305EAC, sp8, spC);
    return true;
}
