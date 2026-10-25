// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113E3C-0x80113E7C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8011D788(s32);
void GetInteger(CStruct *, s32, s32 *, s32);
// ScriptSetRandomMode @ 0x80113E3C
bool ScriptSetRandomMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    fn_8011D788(sp8);
    return true;
}
