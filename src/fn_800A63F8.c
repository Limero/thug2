// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A63F8-0x800A64F0 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, void *, void *);
s32 fn_800A5308(CStruct *, void *);
s32 GetArray(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum(CStruct *, void *);
s32 fn_80131BAC(Unk_15EF4A35 *, void *);
extern char lbl_80300434[];
extern char lbl_80301A78[];

bool ScriptTerminateObjectsScripts(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    void *spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;
    u32 temp_r4;
    u32 var_r31;

    if (ResolveComplexID(*(s32 *)&lbl_80300434, pParams, QB_ID, &sp8) == 0) {
        return false;
    }
    temp_r30 = fn_800A5308(*(s32 *)&lbl_80301A78, sp8);
    temp_r3 = GetArray(pParams, QB_SCRIPTS, &spC, 0);
    if (temp_r3 != 0) {
        var_r31 = 0U;
        if (var_r31 < (u32) *((u32 *)&((CStruct *)spC)->unk0x4)) {
            do {
                temp_r4 = var_r31;
                var_r31 += 1;
                fn_80131BAC(temp_r30, GetChecksum(spC, temp_r4));
            } while (var_r31 < (u32) *((u32 *)&((CStruct *)spC)->unk0x4));
        }
    } else {
        sp10 = temp_r3;
        GetChecksum_2(pParams, QB_SCRIPT_NAME, &sp10, 0);
        fn_80131BAC(temp_r30, sp10);
    }
    return true;
}
