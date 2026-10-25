// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156220-0x801562A0 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8014DB40(s32, s32, s32);

void ScriptSetActiveCamera(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    s32 ret;
    register s32 defval __asm__("r6");

    sp8 = 0;
    GetChecksum_2(arg0, QB_ID, &sp8, 0);
    spC = 0;
    __asm__("li %0,0" : "=r"(defval));
    GetInteger(arg0, QB_VIEWPORT, &spC, defval);
    ret = ContainsFlag(arg0, QB_MOVE);
    fn_8014DB40(sp8, spC, ret);
}
