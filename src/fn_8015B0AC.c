// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B0AC-0x8015B138 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801A2CF8(Unk_31DE137E *, s32, Unk_C7387A53 *);
bool ScriptSetObjectAnimSkippable(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 var_r5;
    s32 objv;
    s32 sp8v;

    sp8 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 0);
    spC = 0;
    GetInteger(pParams, QB_SKIPPABLE, &spC, 0);
    sp8v = sp8;
    objv = *(s32 *)((char *)*(void **)&lbl_80305EAC + 0x37C);
    var_r5 = (spC == 0) ? 0 : 1;
    fn_801A2CF8(objv, sp8v, var_r5);
    return true;
}
