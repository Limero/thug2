// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114170-0x801141C8 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
extern void *lbl_80302C34;
// ScriptSetPositionalSoundSilenceOverrideMode @ 0x80114170
bool ScriptSetPositionalSoundSilenceOverrideMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CStruct *ptr;

    sp8 = 1;
    GetInteger(pParams, 0, &sp8, 1);
    ptr = *(void **)((char *)&lbl_80302C34);
    ptr->unk0x4 = (sp8 != 0);
    return true;
}
