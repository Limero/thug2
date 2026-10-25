// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801653C0-0x80165414 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptTheme_GetBalanceArrowColor(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_RETURN_VALUE, &sp8, 1);
    AddChecksum(pScript->unk0x18, sp8, QB_DE_BALANCE_ARROW_COLOR);
    return true;
}
