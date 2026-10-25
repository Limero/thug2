// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113DF4-0x80113E3C (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
void fn_8011E46C(s32);

bool ScriptSetMusicMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 value;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 0);
    value = sp8 == 0;
    fn_8011E46C(value);
    return true;
}
