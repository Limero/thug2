// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E1B4-0x8000E24C (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE8C;
void GetText(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8000DBFC(s32, s32, s32, s32, s32);
bool ScriptLoadPreFile(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;

    GetText(pParams, 0, &sp8, 1);
    temp_r26 = lbl_802FFE8C;
    temp_r27 = sp8;
    temp_r28 = ContainsFlag(pParams, QB_ASYNC);
    temp_r29 = ContainsFlag(pParams, QB_DONT_ASSERT);
    fn_8000DBFC(temp_r26, temp_r27, temp_r28, temp_r29, ContainsFlag(pParams, QB_USE_BOTTOM_UP_HEAP));
    return true;
}
