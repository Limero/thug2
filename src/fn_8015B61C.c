// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B61C-0x8015B698 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern char lbl_802A8180[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 GetStructure_3(CStruct *, void *, void *, s32);
s32 fn_8003A944(s32, CStruct *, s32);
register s32 r31_guard __asm__("r31");
bool ScriptSetPlayerAppearance(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    temp_r30 = fn_80174AB8(lbl_80305EAC, sp8) + 4;
    GetStructure_3(pParams, (s32)lbl_802A8180, &spC, 1);
    fn_8003A944(temp_r30, spC, 1);
    return true;
}
