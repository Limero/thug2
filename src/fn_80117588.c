// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117588-0x801175D4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptAddFlag(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, 0, &sp8, 0);
    AddChecksum(pScript->unk0x18, 0, sp8);
    return true;
}
