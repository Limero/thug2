// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118CF4-0x80118D70 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80054E1C(void *);
s32 ContainsFlag(CStruct *, void *);
s32 GetText(CStruct *, void *, void *, void *);
s32 fn_80056500(void *, void *, s32);
bool ScriptLoadCollision(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    sp8 = 0;
    GetText(pParams, QB_SCENE, &sp8, 0);
    if (sp8 != 0) {
        temp_r30 = ContainsFlag(pParams, QB_IS_NET);
        fn_80056500(fn_80054E1C(sp8), sp8, temp_r30);
    }
    return true;
}
