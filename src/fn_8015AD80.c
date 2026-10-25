// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015AD80-0x8015AE0C (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_801A3568(s32);
void fn_801A35A4(Unk_31DE137E *, s32);

bool ScriptPauseCutscene(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;
    Unk_40426380 *temp_r31;
    s32 zerov;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    temp_r31 = lbl_80305EAC;
    temp_r29 = (sp8 ^ 1) == 0;
    if (ContainsFlag(pParams, QB_TOGGLE) != 0) {
        fn_801A3568(temp_r31->unk0x378);
    } else {
        fn_801A35A4(temp_r31->unk0x378, temp_r29);
    }
    return true;
}
