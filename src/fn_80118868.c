// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118868-0x801188D8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80301B48;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80128C80(CStruct *, s32, s32 *, s32);
void fn_800F2F88(void *, s32);

bool ScriptSetReferenceChecksum(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    void *ref;

    ref = *(void **)&lbl_80301B48;
    if (GetChecksum_2(pParams, 0, &sp8, 0) == 0) {
        fn_80128C80(pParams, 0, &sp8, 1);
    }
    fn_800F2F88(ref, sp8);
    return true;
}
