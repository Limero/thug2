// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D438-0x8015D4E4 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801988AC(s32, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_801988DC(s32, s32);
bool ScriptSetScoreAccumulation(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_801988AC(lbl_80305EC0, sp8 != 0);
    if ((sp8 == 0) && (ContainsFlag(pParams, QB_FREEZE_SCORE) != 0)) {
        fn_801988DC(lbl_80305EC0, 1);
    } else {
        fn_801988DC(lbl_80305EC0, 0);
    }
    return true;
}
