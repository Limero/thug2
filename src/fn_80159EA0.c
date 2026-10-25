// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159EA0-0x80159F1C (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 fn_80128C80(CStruct *, void *, void *, void *);
s32 fn_801A5D9C(void *, void *);
extern char lbl_80305EFC[];
bool ScriptGetSkaterSex(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    fn_80128C80(fn_801A5D9C(*(s32 *)&lbl_80305EFC, sp8) + 0x6C, QB_IS_MALE, &spC, 1);
    AddInteger(pScript->unk0x18, QB_IS_MALE, spC);
    return true;
}
