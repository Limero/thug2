// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112F40-0x80112F8C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011BEFC(s32);
void fn_8011BEAC(s32);

bool ScriptStopStream(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        fn_8011BEFC(sp8);
    } else {
        fn_8011BEAC(-1);
    }
    return true;
}
