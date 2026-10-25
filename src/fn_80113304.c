// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113304-0x8011334C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011E7C8(s32);

s32 ScriptFreeStreamFrameAmp(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        return fn_8011E7C8(sp8);
    }
    return 0;
}
