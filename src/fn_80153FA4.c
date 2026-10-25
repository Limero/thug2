// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153FA4-0x80154048 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7F04[];
s32 GetText(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8005B884(void *, s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_8005B8D4(f32);

bool ScriptDisplayLoadingScreen(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    f32 spC;
    s32 str;
    s32 a;

    sp8 = (s32)lbl_802A7F04;
    GetText(pParams, 0, &sp8, 0);
    str = sp8;
    a = ContainsFlag(pParams, QB_FREEZE);
    fn_8005B884(str, a, ContainsFlag(pParams, QB_BLANK));
    if (GetFloat(pParams, 0, &spC, 0) != 0) {
        fn_8005B8D4(spC);
    }
    return true;
}
