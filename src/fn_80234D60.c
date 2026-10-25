// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234D60-0x80234DA8 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80235CD4(Unk_673C6403 *, s32);
s32 fn_80238964(void);
// ScriptSetEditorTheme @ 0x80234D60
bool ScriptSetEditorTheme(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_THEME, &sp8, 0);
    fn_80235CD4(fn_80238964(), sp8);
    return true;
}
