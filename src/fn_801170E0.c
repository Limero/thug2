// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801170E0-0x801171A0 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptMangleChecksums(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    if (GetChecksum_2(pParams, QB_A, &sp8, NULL) == 0) {
        GetInteger(pParams, QB_A, &sp8, 1);
    }
    if (GetChecksum_2(pParams, (s32 *)QB_B, &spC, 0) == 0) {
        GetInteger(pParams, QB_B, &spC, 1);
    }
    AddChecksum(pScript->unk0x18, QB_MANGLED_ID, sp8 + spC);
    return true;
}
