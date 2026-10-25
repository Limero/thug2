// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801166CC-0x80116718 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_80128978(void *, void *);
void ScriptGotParam(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    fn_80128978(pScript->unk0x18, sp8);
}
