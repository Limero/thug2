// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A6588-0x800A660C (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, void *, void *);
s32 fn_800A5308(CStruct *, void *);
extern char lbl_80300434[];
extern char lbl_80301A78[];
bool ScriptSetObjectProps(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    void *temp_r3;
    Unk_89391A04 *temp_r9;

    if (ResolveComplexID(*(s32 *)&lbl_80300434, pParams, QB_ID, &sp8) == 0) {
        return false;
    }
    temp_r3 = fn_800A5308(*(s32 *)&lbl_80301A78, sp8);
    temp_r9 = ((Unk_9994C3F5 *)temp_r3)->unk0x8;
    ((s32 (*)(void *, void *))temp_r9->unk0x14)(temp_r3 + temp_r9->unk0x10, pParams);
    return true;
}
