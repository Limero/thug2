// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234F2C-0x80234F6C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_802336D8(s32, s32);
extern s32 lbl_80305FF8;
bool ScriptBindParkEditorToController(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    GetInteger(pParams, 0, &sp8, 1);
    fn_802336D8(lbl_80305FF8, sp8);
    return true;
}
