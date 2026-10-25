// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801111A8-0x801111E4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012834C(CStruct *, void *, void *, s32);
void fn_8006EBB8(f32);
extern char lbl_8029CFA4[];
bool ScriptSetFogExponent(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    fn_8012834C(pParams, (void *)lbl_8029CFA4, &sp8, 0);
    fn_8006EBB8(sp8);
    return true;
}
