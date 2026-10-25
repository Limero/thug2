// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801158D8-0x80115948 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801270B4(CStruct *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptRemoveComponent(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetChecksum_2(pParams, QB_NAME, &sp8, NULL) == 0) {
        GetChecksum_2(pParams, NULL, &sp8, 1);
    }
    fn_801270B4(pScript->unk0x18, sp8);
    return true;
}
