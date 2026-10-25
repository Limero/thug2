// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017561C-0x80175668 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128E34(CStruct *, void *, void *, s32);
void fn_80174AE0(Unk_C7387A53 *, s32);
bool ScriptSetGameType(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = lbl_80305EAC;
    fn_80128E34(pParams, 0, &sp8, 1);
    fn_80174AE0((void *)temp_r30, sp8);
    return true;
}
