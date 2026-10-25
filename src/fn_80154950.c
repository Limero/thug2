// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154950-0x801549A0 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 GetText(CStruct *, void *, void *, s32);
void fn_8021B270(Unk_BF863306 *, s32);
bool ScriptJoinWithPassword(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    GetText(pParams, QB_STRING, &sp8, 1);
    fn_8021B270(temp_r30, sp8);
    return true;
}
