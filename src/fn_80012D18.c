// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012D18-0x80012D4C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800126DC(s32);
void GetString(CStruct *, s32 *, s32 *, s32);
// ScriptUnLoadPipPre @ 0x80012D18
void ScriptUnLoadPipPre(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetString(pParams, 0, &sp8, 1);
    fn_800126DC(sp8);
}
