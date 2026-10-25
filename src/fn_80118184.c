// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118184-0x80118214 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000A778(s32);
s32 GetText(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 lbl_802FFE98;
s32 fn_80010400(s32, s32, s32);
bool ScriptMemHeapExists(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    if (GetText(pParams, QB_NAME, &sp8, 0) != 0) {
        spC = fn_8000A778(sp8);
    } else {
        GetChecksum_2(pParams, QB_NAME, &spC, 1);
    }
    if (fn_80010400(lbl_802FFE98, spC, 0) != 0) {
        return true;
    }
    return false;
}
