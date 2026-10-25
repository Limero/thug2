// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114C94-0x80114D08 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetText(CStruct *, void *, void *, s32);
s32 Script_GenerateCRC(s32);

bool ScriptStringEquals(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;

    GetText(pParams, QB_A, &sp8, 1);
    GetText(pParams, QB_B, &spC, 1);
    temp_r30 = Script_GenerateCRC(sp8);
    return temp_r30 == Script_GenerateCRC(spC);
}
