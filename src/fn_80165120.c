// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165120-0x80165174 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptTheme_GetIconOnColor(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_RETURN_VALUE, &sp8, 1);
    AddChecksum(pScript->unk0x18, sp8, QB_DE_ICON_ON_VALUE);
    return true;
}
