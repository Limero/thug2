// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801540C4-0x8015410C (72B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80305F9C[];
extern char lbl_802A7F14[];

s32 fn_80128A90(CStruct *, void *);
void fn_8022B524(Unk_31DE137E *, s32);

bool ScriptRefreshServerList(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    fn_8022B524(temp_r30, fn_80128A90(pParams, (s32)lbl_802A7F14));
    return true;
}
