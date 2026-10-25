// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EB38-0x8015EBA0 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
extern char lbl_802A8234[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801A5D9C(s32, s32);
s32 fn_801A52E4(s32);
void fn_801276E8(CStruct *, void *, s32);
bool ScriptGetNumStatPointsAvailable(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    temp_r3 = fn_801A52E4(fn_801A5D9C(lbl_80305EFC, sp8));
    fn_801276E8(pScript->unk0x18, (s32)lbl_802A8234, temp_r3);
    return true;
}
