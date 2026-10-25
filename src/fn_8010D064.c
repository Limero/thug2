// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010D064-0x8010D0E8 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800A398C(s32, s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptGetUniqueCompositeObjectID(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 8;
    GetChecksum_2((s32)pParams, QB_PREFERREDID, &sp8, 0);
    for (; fn_800A398C(lbl_80301A38, sp8) != 0; sp8++) {
    }
    AddChecksum(pScript->unk0x18, QB_UNIQUEID, sp8);
    return true;
}
