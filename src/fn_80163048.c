// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163048-0x801630A0 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern CStruct * lbl_80366478;
void GetText(CStruct *, void *, void *, s32);
s32 fn_8005CA70(CStruct *, s32, s32, s32, s32);
bool ScriptLoadSFPTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetText(pParams, 0, &sp8, 0);
    return fn_8005CA70(lbl_80366478, sp8, 0, 1, 1) != 0;
}
