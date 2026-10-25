// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801513D4-0x80151468 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_80176F28(s32 arg0, s32 arg1);
s32 fn_8013FF5C(s32 arg0, s32 arg1);
s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
void AddString(CStruct * arg0, s32 arg1, void * arg2);
bool ScriptGetPreferenceString(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = pScript->unk0x18;
    GetChecksum_2(pParams, 0, &sp8, 0);
    GetChecksum_2(pParams, QB_PREF_TYPE, &spC, 0);
    GetString(fn_8013FF5C(fn_80176F28(spC, 1), sp8), QB_UI_STRING, &sp10, 0);
    AddString(temp_r29, QB_UI_STRING, sp10);
    return true;
}
