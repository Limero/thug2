// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220BA8-0x80220C0C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern s32 fn_800145AC(void);
extern s32 lbl_80305FB0;
void Script_RunScript(s32, s32, s32, s32, s32);
bool ScriptDisplayFlagBaseWarning(CStruct *pParams, CScript *pScript) {
    if ((u32)(fn_800145AC() - lbl_80305FB0) > 0xBB8U) {
        Script_RunScript(QB_DISPLAY_FLAG_BASE_WARNING, 0, 0, 0, 0);
        lbl_80305FB0 = fn_800145AC();
    }
    return true;
}
