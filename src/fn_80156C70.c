// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156C70-0x80156CB0 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EFC[];
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void fn_801A63E8(Unk_C7387A53 *, s32);
void ScriptAddTemporaryProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    fn_801A63E8(*(s32 *)&lbl_80305EFC, sp8);
}
