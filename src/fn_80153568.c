// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153568-0x801535F8 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80219580(CStruct *, s32);
bool ScriptSetNetworkMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;

    sp8 = 0;
    temp_r31 = lbl_80305F9C;
    GetInteger(pParams, 0, &sp8, 0);
    if (sp8 == 0) {
        fn_80219580(temp_r31, 0);
    } else if (sp8 == 1) {
        fn_80219580(temp_r31, 1);
    } else if (sp8 == 2) {
        fn_80219580(temp_r31, 2);
    }
    return true;
}
