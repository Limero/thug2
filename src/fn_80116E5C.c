// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116E5C-0x80116EB0 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
extern s32 lbl_80302C28;
// ScriptEnableScriptPrintf @ 0x80116E5C
bool ScriptEnableScriptPrintf(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    lbl_80302C28 = (sp8 != 0);
    return true;
}
