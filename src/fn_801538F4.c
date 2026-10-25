// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801538F4-0x8015396C (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8021F988(s32, s32, s32);

void ScriptConnectToInternet(CStruct *pParams, CScript *pScript) {
    s32 ctx;
    s32 sp8;
    s32 spC;

    ctx = lbl_80305F9C;
    sp8 = 0;
    spC = 0;
    GetChecksum_2(pParams, QB_SUCCESS, &sp8, 0);
    GetChecksum_2(pParams, QB_FAILURE, &spC, 0);
    fn_8021F988(ctx, sp8, spC);
}
