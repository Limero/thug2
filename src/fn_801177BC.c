// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801177BC-0x80117840 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
void fn_80131ED8(Unk_FFAD6788 *, CStruct *, CStruct *);
bool ScriptResetEventHandlersFromTable(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    GetChecksum_2(arg0, 0, &sp8, (s32 *)1);
    temp_r29 = fn_801259C8(sp8, 0);
    spC = QB_DEFAULT;
    GetChecksum_2(arg0, (s32 *)QB_GROUP, &spC, 0);
    fn_80131ED8(arg1, temp_r29, spC);
    return true;
}
