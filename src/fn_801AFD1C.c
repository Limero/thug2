// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AFD1C-0x801AFD88 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_801A6CCC(Unk_93C2DF4D *);
extern s32 fn_801A6B64(Unk_93C2DF4D *, s32);
void fn_801AF5DC(CStruct *);

bool ScriptGiveAllGaps(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    temp_r31 = *(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x24);
    if (GetInteger(pParams, QB_LEVEL, &sp8, 0) == 0) {
        sp8 = fn_801A6CCC(temp_r31);
    }
    fn_801AF5DC(fn_801A6B64(temp_r31, sp8));
    return true;
}
