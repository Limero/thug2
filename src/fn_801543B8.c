// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801543B8-0x801543FC (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
extern char lbl_80305EAC[];
bool ScriptSetLevelStructureName(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    *(s32 *)((char *)(*(void **)&lbl_80305EAC) + 0x390) = sp8;
    return true;
}
