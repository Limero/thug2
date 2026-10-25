// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D704-0x8004D768 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, void *, void *);
s32 fn_8004C7B0(Unk_C7387A53 *, void *);
extern char lbl_80300434[];
bool ScriptSetRootScreenElement(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    temp_r31 = *(s32 *)&lbl_80300434;
    if (ResolveComplexID(temp_r31, pParams, QB_ID, &sp8) != 0) {
        fn_8004C7B0(temp_r31, sp8);
        return true;
    }
    return false;
}
