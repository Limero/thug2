// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163AEC-0x80163BC8 (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
void AddString(CStruct *, s32, void *);
bool ScriptGetSkaterLastNameString(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    CStruct *arr;
    s32 cnt;
    s32 entry;
    s32 i;

    GetChecksum_2(pParams, 0, &sp8, 1);
    for (i = 0, arr = fn_801259C8(QB_MASTER_SKATER_LIST, 1), cnt = arr->unk0x4; i < cnt; i++) {
        entry = fn_80129528(arr, i);
        GetChecksum_2(entry, QB_NAME, &spC, 1);
        if (spC == sp8) {
            if (GetString(entry, QB_LAST_NAME, &sp10, 0) != 0) {
                AddString(pScript->unk0x18, QB_LAST_NAME, sp10);
                return true;
            }
            return false;
        }
    }
    return false;
}
