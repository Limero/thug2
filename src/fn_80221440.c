// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221440-0x80221494 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_80305F9C;
void GetInteger(CStruct *, s32, s32 *, s32);
void fn_802195C4(Unk_C7387A53 *, s32);
bool ScriptSetHostMode(CStruct *pParams, CScript *pScript) {
    void *sp8;
    void *mgr = lbl_80305F9C;

    sp8 = NULL;
    GetInteger(pParams, 0, &sp8, 0);
    fn_802195C4((s32)mgr, (s32)sp8);
    return true;
}
