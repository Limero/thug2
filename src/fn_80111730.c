// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111730-0x80111770 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800546A0(s32);
void fn_800583D0(void);
extern char lbl_8029CFC0[];
void GetChecksum_4(CStruct *, void *, void *, s32);
// ScriptStopTextureAnim @ 0x80111730
bool ScriptStopTextureAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_4(pParams, (s32)lbl_8029CFC0, &sp8, 0);
    fn_800546A0(sp8);
    fn_800583D0();
    return true;
}
