// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B490-0x8015B4DC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80174508(s32, s32, s32);
bool ScriptAutoKickOff(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    fn_80174508(lbl_80305EAC, sp8, 0);
    return true;
}
