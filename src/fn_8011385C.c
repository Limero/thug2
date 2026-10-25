// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011385C-0x801138D0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80302C34;
extern f32 lbl_8029D104;
extern f32 lbl_8029D100;
extern f32 lbl_8029D0FC;

void GetFloat(CStruct *, s32, f32 *, s32);
void fn_80119A54(void *, f32);

bool ScriptSetSfxDropoff(CStruct *pParams, CScript *pScript) {
    f32 sp8 = lbl_8029D0FC;

    GetFloat(pParams, 0, &sp8, 0);
    if (sp8 <= lbl_8029D100) {
        return false;
    }
    fn_80119A54(*(void **)&lbl_80302C34, sp8 * lbl_8029D104);
    return true;
}
