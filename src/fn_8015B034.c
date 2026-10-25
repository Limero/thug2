// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B034-0x8015B0AC (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_801A2FE4(Unk_C7387A53 *, CStruct *, void *, void *);
bool ScriptPlayObjectAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    ContainsFlag(pParams, QB_STOP);
    sp8 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 0);
    fn_801A2FE4(*(s32 *)((char *)*(void **)&lbl_80305EAC + 0x37C), sp8, pParams, QB_OBJECTANIM);
    return true;
}
