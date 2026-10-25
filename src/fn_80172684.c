// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172684-0x801726D0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EA4;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80171B54(s32, s32);
register s32 _r31_guard __asm__("r31");
bool ScriptTODManager_EnableBloom(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 mgr;

    mgr = lbl_80305EA4;
    GetInteger(pParams, 0, &sp8, 1);
    fn_80171B54(mgr, sp8);
    return true;
}
