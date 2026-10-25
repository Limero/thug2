// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117054-0x801170E0 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
s32 ContainsFlag(s32, s32);
s32 ScriptStructureContains(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    if (GetStructure_2(pParams, QB_STRUCTURE, &sp8, 0) != 0) {
        spC = 0;
        GetChecksum_2(pParams, 0, &spC, 0);
        if (fn_80128978(sp8, spC) != 0) {
            return 1;
        }
        return ContainsFlag(sp8, spC);
    }
    return 0;
}
