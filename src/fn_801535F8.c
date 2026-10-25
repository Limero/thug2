// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801535F8-0x8015364C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80124E54(Unk_6A70655D *, s32);
bool ScriptProfileTasks(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = lbl_80303148;
    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_80124E54(temp_r30, sp8);
    return true;
}
