// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118E90-0x80118EDC (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80054D54(s32);
void GetText(CStruct *, void *, void *, s32);
bool ScriptQuickReload(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetText(pParams, QB_SCENE, &sp8, 0);
    if (sp8 != 0) {
        fn_80054D54(sp8);
    }
    return true;
}

