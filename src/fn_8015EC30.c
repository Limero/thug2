// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EC30-0x8015ECA8 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003D50C(void *, void *, void *);
s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptGetActualCASOptionStruct(CStruct *pParams, CScript *pScript) {
    s32 temp_r5;
    s32 spC;
    s32 sp8;

    GetChecksum_2(pParams, QB_PART, &sp8, (s32 *)1);
    GetChecksum_2(pParams, (s32 *)QB_DESC_ID, &spC, 1);
    temp_r5 = fn_8003D50C(sp8, spC, 1);
    fn_80126FF4(pScript->unk0x18,  temp_r5);
    return false;
}
