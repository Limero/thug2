// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220640-0x8022067C (60B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
extern void *lbl_80305F9C;
extern s32 fn_8000A578(s32, s32);
bool ScriptStartCTFGame(CStruct *pParams, CScript *pScript) {
    fn_8000A578(lbl_80303148 + 8, ((Unk_FFAD6788 *)lbl_80305F9C)->unk0x104);
    return true;
}
