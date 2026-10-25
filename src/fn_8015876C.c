// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015876C-0x801587C8 (92B). Byte-identical.
#include "types.h"
extern char lbl_80305EFC[];
#include "qb_constants.h"
#include "structs.h"

s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 defval);
s32 fn_801A5D9C(s32 a, s32 b);
void fn_80126FF4(Unk_80577C09 * a, CStruct * b);

bool ScriptGetSkaterProfileInfo(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 prof;
    s32 ret;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    prof = *(s32 *)&lbl_80305EFC;
    ret = fn_801A5D9C(prof, sp8);
    fn_80126FF4(pScript->unk0x18, ret + 0x6C);
    return true;
}
