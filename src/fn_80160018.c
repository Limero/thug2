// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160018-0x801600C8 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 AddChecksum(CStruct *, s32, s32);

bool ScriptGetTrickType(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r31;

    GetChecksum_2(pParams, QB_TRICK, &sp8, 1);
    if ((GetChecksum_2(temp_r31 = GetStructure(sp8, 1), QB_TRICKTYPE, &spC, 0) == 0) &&
        (GetChecksum_2(temp_r31, QB_SCR, &spC, 0) == 0)) {
        spC = QB_GRINDTRICK;
    }
    AddChecksum(pScript->unk0x18, QB_TRICK_TYPE, spC);
    return true;
}
