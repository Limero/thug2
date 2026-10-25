// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801138D0-0x8011391C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D108;
extern char lbl_80302C34[];
s32 fn_8011A7FC(s32, f32);
s32 GetFloat(CStruct *, s32, f32 *, s32);

bool ScriptSetSfxVolume(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    sp8 = lbl_8029D108;
    GetFloat(pParams, 0, &sp8, 0);
    fn_8011A7FC(*(s32 *)&lbl_80302C34, sp8);
    return true;
}
