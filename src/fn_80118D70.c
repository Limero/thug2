// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118D70-0x80118DF8 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetText(CStruct *, s32, void *, s32);
s32 fn_80054E1C(s32);
void fn_800567E4(s32, s32);

bool ScriptAddCollision(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    s32 spC = 0;

    GetText(pParams, 0x26861025, &sp8, 0);
    GetText(pParams, 0x02E58C18, &spC, 0);
    if (sp8 != 0 && spC != 0) {
        fn_800567E4(fn_80054E1C(sp8), spC);
    }
    return true;
}
