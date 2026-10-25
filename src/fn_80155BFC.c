// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155BFC-0x80155C48 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802A7FDC;
extern char lbl_80305EAC[];
s32 GetFloat(CStruct *, s32, f32 *, s32);

bool ScriptSetStatOverride(CStruct *pParams, CScript *pScript) {
    f32 sp8;

    sp8 = lbl_802A7FDC;
    GetFloat(pParams, 0, &sp8, 0);
    *(f32 *)((char *)*(s32 *)&lbl_80305EAC + 0x420) = sp8;
    return true;
}
