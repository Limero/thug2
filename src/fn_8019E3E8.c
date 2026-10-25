// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E3E8-0x8019E468 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EE4;
s32 ContainsFlag(CStruct *, s32);
void fn_8019D62C(s32, CStruct *);
bool ScriptSetButtonEventMappings(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;
    Unk_FFAD6788 *temp_r30;

    temp_r30 = (void *)lbl_80305EE4;
    fn_8019D62C(temp_r30, pParams);
    temp_r3 = ContainsFlag(pParams, QB_BLOCK_MENU_INPUT);
    if (temp_r3 != 0) {
        temp_r30->unk0x8C = 1;
    } else if (ContainsFlag(pParams, QB_UNBLOCK_MENU_INPUT) != 0) {
        temp_r30->unk0x8C = temp_r3;
    }
    return true;
}
