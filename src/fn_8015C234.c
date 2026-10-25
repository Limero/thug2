// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C234-0x8015C288 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80156930(s32, s32);
s32 fn_801A6F8C(s32, s32);
// ScriptSetGlobalFlag @ 0x8015C234
bool ScriptSetGlobalFlag(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80128C80(pParams, QB_FLAG, &sp8, 1);
    fn_801A6F8C(fn_80156930(sp8, pParams), sp8);
    return true;
}
