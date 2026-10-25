// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E468-0x8019E4C0 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32* lbl_80305EE4;
s32 fn_80128C80(CStruct *, void *, void *, s32);
void fn_8019D3E0(void *, s32);
bool ScriptSetAnalogStickActiveForMenus(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    fn_80128C80(pParams, 0, &sp8, 0);
    fn_8019D3E0(lbl_80305EE4, sp8 == 0 ? 0 : 1);
    return true;
}
