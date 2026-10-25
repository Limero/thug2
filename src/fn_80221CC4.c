// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221CC4-0x80221CFC (56B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern s32 lbl_803A3140;
s32 ScriptJustStartedNetGame(CStruct *pParams, CScript *pScript) {
    return (u32)(fn_800145AC() - lbl_803A3140) < 0x1388U;
}
