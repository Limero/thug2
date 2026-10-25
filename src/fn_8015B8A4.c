// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B8A4-0x8015B938 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_80174AB8(void *, s32);
extern s32 GetText(CStruct *, void *, void *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_8003AE20(Unk_31DE137E *);
extern void fn_8003E914(CStruct *, s32, s32);
bool ScriptSetPlayerFaceTexture(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    temp_r29 = fn_80174AB8(*(s32 *)&lbl_80305EAC, sp8) + 4;
    GetText(pParams, QB_TEXTURE, &spC, 1);
    temp_r30 = ContainsFlag(pParams, QB_FULLPATHINCLUDED);
    fn_8003E914(fn_8003AE20(temp_r29), spC, temp_r30);
    return true;
}
