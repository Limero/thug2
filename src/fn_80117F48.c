// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117F48-0x80117F80 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8001075C(s32);
void GetText(CStruct *, void *, void *, s32);
// ScriptPushMemProfile @ 0x80117F48
bool ScriptPushMemProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetText(pParams, 0, &sp8, 1);
    fn_8001075C(sp8);
    return true;
}
