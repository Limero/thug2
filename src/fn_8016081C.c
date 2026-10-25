// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016081C-0x80160874 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801A6534(Unk_C7387A53 *, s32);

bool ScriptLockCurrentSkaterProfileIndex(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, (s32 *)1);
    fn_801A6534(lbl_80305EFC, (sp8 != 0));
    return true;
}
