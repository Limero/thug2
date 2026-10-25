// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118088-0x80118104 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 fn_80010434(s32, s32, s32, s32, s32);
s32 Script_GenerateCRC(s32);
s32 fn_80128C80(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, s32, s32 *, s32);
extern s32 lbl_802FFE98;
bool ScriptMemInitHeap(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 v;
    GetText(pParams, QB_NAME, &sp8, 1);
    fn_80128C80(pParams, QB_SIZE, &spC, 1);
    v = Script_GenerateCRC(sp8);
    fn_80010434(lbl_802FFE98, v, spC, sp8, 0);
    return true;
}
