// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111574-0x801115B8 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_800546A0(s32);
void fn_80058320(void *, s32);
void GetChecksum_4(CStruct *, void *, void *, s32);
extern char lbl_8029CFC0[];
// ScriptEnableExplicitUVWibble @ 0x80111574
bool ScriptEnableExplicitUVWibble(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_4(pParams, (s32)lbl_8029CFC0, &sp8, 0);
    fn_80058320(fn_800546A0(sp8), 1);
    return true;
}
