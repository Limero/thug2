// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112DDC-0x80112E38 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011E548(s32);

s32 ScriptStreamExists(CStruct *pParams, CScript *pScript) {
    s32 ret = 0;
    s32 sp8 = 0;

    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0 && fn_8011E548(sp8) != 0) {
        ret = 1;
    }
    return ret;
}
