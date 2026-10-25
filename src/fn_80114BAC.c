// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114BAC-0x80114C20 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetInteger(CStruct *, s32, s32 *, s32);

bool ScriptIntegerEquals(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    s32 spC;

    GetInteger(pParams, 0x174841BC, &sp8, 0);
    spC = 0;
    GetInteger(pParams, 0x8E411006, &spC, 0);
    return sp8 == spC;
}
