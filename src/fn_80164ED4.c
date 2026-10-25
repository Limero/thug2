// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80164ED4-0x80164F28 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptTheme_GetHighlightedTextColor(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_RETURN_VALUE, &sp8, 1);
    AddChecksum(pScript->unk0x18, sp8, QB_DE_HIGHLIGHTED_TEXT_COLOR);
    return true;
}
