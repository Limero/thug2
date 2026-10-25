// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055880-0x800558C0 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800557F4(s32);
void fn_80128C80(CStruct *, void *, void *, s32);
// ScriptSetScreenBlur @ 0x80055880
bool ScriptSetScreenBlur(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    fn_80128C80(pParams, 0, &sp8, 0);
    fn_800557F4(sp8);
    return true;
}
