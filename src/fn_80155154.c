// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155154-0x80155198 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803A0090[];
void GetText(CStruct *, void *, void *, s32);
void sprintf(s32, ...);
bool ScriptSetLevelName(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetText(pParams, 0, &sp8, 1);
    sprintf((s32)lbl_803A0090, sp8);
    return true;
}
