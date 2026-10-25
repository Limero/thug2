// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CFF4-0x8015D09C (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 fn_801746A4(Unk_C7387A53 * obj, s32 idx);
extern s32 fn_80174AB8(void * obj, s32 idx);
extern s32 GetChecksum_3(Unk_6A70655D * a, s32 b);
extern s32 fn_800B6254(s32 a, s32 b, s32 c);
bool ScriptRefreshSkaterUV(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;

    sp8 = 0;
    spC = 0;
    GetInteger(pParams, QB_PROFILE, &sp8, 1);
    GetInteger(pParams, QB_SKATER, &spC, 1);
    temp_r30 = fn_801746A4(*(s32 *)&lbl_80305EAC, spC);
    temp_r29 = fn_80174AB8(*(s32 *)&lbl_80305EAC, sp8) + 4;
    fn_800B6254(GetChecksum_3(temp_r30, QB_MODEL), temp_r29, QB_SET_UV_FROM_APPEARANCE);
    return true;
}
