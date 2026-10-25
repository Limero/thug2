// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112E38-0x80112EBC (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011CAF0(s32, s32, s32);

s32 ScriptAddStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;

    sp8 = 0;
    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        spC = 0;
        if (GetChecksum_2(pParams, QB_ADD, &spC, 0) != 0)
            return fn_8011CAF0(sp8, spC, 0);
    }
    return 0;
}
