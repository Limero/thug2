// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011372C-0x80113774 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80302C34;

s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8011A150(void *, s32);

bool ScriptClearSoundBank(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    if (GetInteger(pParams, 0, &sp8, 0) != 0) {
        fn_8011A150(*(void **)&lbl_80302C34, sp8);
    }
    return true;
}
