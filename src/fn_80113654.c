// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113654-0x801136AC (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80302C34;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8011A95C(void *, s32, s32 *);

s32 ScriptIsSoundPlaying(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    s32 ret;

    if (GetChecksum_2(pParams, 0, &sp8, 0) == 0) {
        ret = 0;
    } else {
        ret = fn_8011A95C(*(void **)&lbl_80302C34, sp8, 0);
    }
    return ret;
}
