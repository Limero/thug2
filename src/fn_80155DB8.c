// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155DB8-0x80155E08 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EE4;
s32 fn_80128C80(CStruct *, void *, void *, s32);
void fn_8019D388(Unk_C8FEE62D *, s32);

bool ScriptStartKeyboardHandler(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = lbl_80305EE4;
    fn_80128C80(pParams, QB_MAX_LENGTH, &sp8, 1);
    fn_8019D388(temp_r30, sp8);
    return true;
}
