// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A638C-0x800A63F8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, s32, s32);
s32 fn_800A5308(CStruct *, s32);
extern void* lbl_80300434;
extern s32 lbl_80301A78;
bool ScriptObjectExists(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31 = lbl_80301A78;
    if (ResolveComplexID(lbl_80300434, pParams, QB_ID, (s32)&sp8) != 0) {
        if (fn_800A5308(temp_r31, sp8) != 0) {
            return true;
        }
    }
    return false;
}
