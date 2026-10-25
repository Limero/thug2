// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117334-0x80117378 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetStructure(s32, s32);
void CStruct_dtor(void);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
// ScriptClearStruct @ 0x80117334
bool ScriptClearStruct(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_STRUCT, &sp8, 1);
    GetStructure(sp8, 1);
    CStruct_dtor();
    return true;
}
