// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D388-0x8015D3E0 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EC0[];
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 fn_8019890C(s32 obj, s32 val);
bool ScriptSetScoreDegradation(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_8019890C(*(s32 *)&lbl_80305EC0, (sp8 != 0) ? 1 : 0);
    return true;
}
