// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117620-0x801176F8 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_80128E34(CStruct *, void *, void *, void *);
s32 fn_80131DC0(Unk_FFAD6788 *, void *, void *, void *, void *, CStruct *);
bool ScriptSetEventHandler(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r28;

    sp8 = 0;
    fn_80128E34(arg0, QB_EX, &sp8, (s32 *)1);
    spC = 0;
    fn_80128E34(arg0, (s32 *)QB_SCR, &spC, 1);
    sp10 = QB_DEFAULT;
    GetChecksum_2(arg0, QB_GROUP, &sp10, 0);
    temp_r28 = ContainsFlag(arg0, 0x80367192);
    sp14 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp14, 0);
    fn_80131DC0(arg1, sp8, spC, sp10, temp_r28, sp14);
    return true;
}
