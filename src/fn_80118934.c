// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118934-0x80118980 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8010CB44(s32);
bool ScriptLoadTerrainSounds(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    if (GetChecksum_2(pParams, QB_TERRAIN, &sp8, 0) == 0) {
        return false;
    }
    fn_8010CB44(sp8);
    return true;
}
