// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A64F0-0x800A6588 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, s32, s32);
s32 fn_800A5308(CStruct *, s32);
void fn_800A5390(Unk_C7387A53 *, s32, Unk_C7387A53 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void* lbl_80300434;
extern s32 lbl_80301A78;
bool ScriptAssignAlias(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;

    if (ResolveComplexID(lbl_80300434, pParams, QB_ID, (s32)&sp8) == 0) {
        return false;
    }
    temp_r30 = lbl_80301A78;
    temp_r29 = fn_800A5308((CStruct *)temp_r30, sp8);
    GetChecksum_2(pParams, QB_ALIAS, &spC, 1);
    fn_800A5390((Unk_C7387A53 *)temp_r30, spC, (Unk_C7387A53 *)temp_r29);
    return true;
}
