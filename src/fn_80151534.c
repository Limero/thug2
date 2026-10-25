// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151534-0x801515C8 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddChecksum(CStruct *, s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 fn_8013FF5C(s32, s32);
s32 fn_80176F28(s32, s32);
extern char lbl_802A7D28[];
bool ScriptGetPreferenceChecksum(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = pScript->unk0x18;
    GetChecksum_2(pParams, 0, &sp8, 0);
    GetChecksum_4(pParams, (s32)lbl_802A7D28, &spC, 0);
    GetChecksum_2(fn_8013FF5C(fn_80176F28(spC, 1), sp8), QB_CHECKSUM, &sp10, 0);
    AddChecksum(temp_r29, QB_CHECKSUM, sp10);
    return true;
}
