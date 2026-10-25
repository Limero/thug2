// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B1C4-0x8015B210 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801A2E28(Unk_31DE137E *, s32);
void ScriptObjectAnimFinished(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 0);
    fn_801A2E28(*(s32 *)((char *)*(void **)&lbl_80305EAC + 0x37C), sp8);
}
