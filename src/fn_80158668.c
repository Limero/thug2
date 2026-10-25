// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158668-0x801586F8 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_80174F88(Unk_C7387A53 *, void *, void *);
extern char lbl_80305EAC[];
bool ScriptResetSkaters(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r28;

    sp8 = 0;
    GetInteger(pParams, QB_NODE_NUMBER, &sp8, 0);
    spC = 0;
    GetChecksum_2(pParams, QB_NODE_NAME, &spC, 0);
    temp_r28 = *(s32 *)&lbl_80305EAC;
    fn_80174F88(temp_r28, spC, ContainsFlag(pParams, QB_RESTARTWALKING));
    return true;
}
