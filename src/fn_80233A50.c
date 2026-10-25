// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233A50-0x80233A9C (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305FF8;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_802337C4(Unk_FFAD6788 *, s32);
bool ScriptSetParkEditorTimeOfDay(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(pParams, QB_TOD_SCRIPT, &sp8, 0);
    fn_802337C4(lbl_80305FF8, sp8);
    return true;
}
