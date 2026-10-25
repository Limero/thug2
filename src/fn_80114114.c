// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114114-0x8011414C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8011C0A8(s32);
void GetInteger(CStruct *, s32, s32 *, s32);
// ScriptUseUserSoundtrack @ 0x80114114
bool ScriptUseUserSoundtrack(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, 0, &sp8, 1);
    fn_8011C0A8(sp8);
    return true;
}
