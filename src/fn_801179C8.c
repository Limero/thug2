// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801179C8-0x801179F0 (40B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern bool lbl_80302C2C;

bool ScriptFirstTimeThisIsCalled(CStruct *pParams, CScript *pScript) {
    if (lbl_80302C2C != 0) {
        lbl_80302C2C = 0;
        return true;
    }
    return false;
}
