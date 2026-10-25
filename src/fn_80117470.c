// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117470-0x801174B4 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
bool ScriptIsArray(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    sp8 = 0;
    return (GetArray(pParams, 0, &sp8, 0) != 0);
}
