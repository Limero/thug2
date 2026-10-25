// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115C28-0x80115C78 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012720C(CStruct *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptRemoveFlag(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    fn_8012720C(pScript->unk0x18, sp8);
    return true;
}
