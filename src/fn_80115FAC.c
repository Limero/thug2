// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115FAC-0x80116018 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80127E70(void *, void *, void *, void *);
s32 GetArray(CStruct *, void *, s32 *, void *);

bool ScriptSizeOf(CStruct *pParams, CScript *pScript) {
    void *sp8;
    s32 var_r6;

    sp8 = NULL;
    GetArray(pParams, 0, &sp8, 0);
    var_r6 = 0;
    if (sp8 != NULL)
        var_r6 = ((CStruct *)sp8)->unk0x4;
    fn_80127E70(pScript->unk0x18, QB_ARRAYSIZE, 1, var_r6);
    return true;
}
