// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017253C-0x80172590 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EA4;
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80171614(Unk_9472DC69 *, s32);
bool ScriptTODManager_SetTODScript(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;

    temp_r30 = lbl_80305EA4;
    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    fn_80171614(temp_r30, sp8);
    return true;
}
