// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B528-0x8015B574 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801744B8(s32, s32, s32);
bool ScriptSpinTapsOn(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    fn_801744B8(lbl_80305EAC, sp8, 1);
    return true;
}
