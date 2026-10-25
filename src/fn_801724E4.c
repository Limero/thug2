// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801724E4-0x8017253C (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EA4;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80170444(Unk_9D99273B *, s32);
register s32 _r31_guard __asm__("r31");
bool ScriptTODManager_ResetLevelLights(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 mgr;

    mgr = lbl_80305EA4;
    sp8 = 0;
    GetChecksum_2(pParams, QB_STATE_NAME, &sp8, 0);
    fn_80170444(mgr, sp8);
    return true;
}
