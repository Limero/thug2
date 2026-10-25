// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800539DC-0x80053A14 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80053704(CStruct *);
void GetText(CStruct *, void *, void *, s32);
// ScriptUnloadFont @ 0x800539DC
bool ScriptUnloadFont(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetText(pParams, 0, &sp8, 0);
    fn_80053704(sp8);
    return true;
}
