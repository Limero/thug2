// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115BC8-0x80115C28 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801270B4(CStruct *, s32);
void fn_8012720C(CStruct *, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
// ScriptRemoveParameter @ 0x80115BC8
bool ScriptRemoveParameter(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    temp_r29 = pScript->unk0x18;
    fn_801270B4(temp_r29, sp8);
    fn_8012720C(temp_r29, sp8);
    return true;
}
