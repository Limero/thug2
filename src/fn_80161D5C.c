// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161D5C-0x80161DD4 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern CStruct * lbl_80366474;
s32 GetText(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8005CA70(CStruct *, void *, s32, s32, s32);

bool ScriptLoadTexture(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;

    GetText(pParams, 0, &sp8, 0);
    temp_r3 = ContainsFlag(pParams, QB_NO_VRAM_ALLOC);
    return fn_8005CA70(lbl_80366474, sp8, 1, temp_r3 == 0, 1) ? 1 : 0;
}
