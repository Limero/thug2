// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113A5C-0x80113A9C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void PauseMusic(s32);
void GetInteger(CStruct *, s32, s32 *, s32);
// ScriptPauseMusic @ 0x80113A5C
bool ScriptPauseMusic(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    PauseMusic(sp8);
    return true;
}
