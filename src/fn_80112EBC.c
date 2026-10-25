// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112EBC-0x80112F40 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011CBFC(s32, s32, s32);

s32 ScriptRemoveStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;

    sp8 = 0;
    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        spC = 0;
        if (GetChecksum_2(pParams, QB_REMOVE, &spC, 0) != 0)
            return fn_8011CBFC(sp8, spC, 0);
    }
    return 0;
}
