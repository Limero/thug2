// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113A9C-0x80113ADC (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void PauseStream(s32);
void GetInteger(CStruct *, s32, s32 *, s32);
// ScriptPauseStream @ 0x80113A9C
bool ScriptPauseStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    PauseStream(sp8);
    return true;
}
