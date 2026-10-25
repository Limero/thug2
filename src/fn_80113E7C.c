// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113E7C-0x80113ECC (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
void fn_8011D810(s32);
// ScriptSetMusicLooping @ 0x80113E7C
bool ScriptSetMusicLooping(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_8011D810(sp8 != 0);
    return true;
}
