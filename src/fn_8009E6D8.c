// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E6D8-0x8009E7A0 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E6D8(Unk_C7387A53 *, CStruct *);
s32 ContainsFlag(CStruct *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
void fn_8009E2AC(Unk_C8FEE62D *, CStruct *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_8009E474(Unk_C7387A53 *, CStruct *);
void fn_8009E4B0(Unk_C7387A53 *, CStruct *);
void fn_8009E6D8(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r29;

    temp_r29 = ContainsFlag(arg1, QB_REPLACE_HANDLERS);
    if (GetArray(arg1, QB_EVENT_HANDLERS, &sp8, 0) != 0) {
        fn_8009E2AC(arg0, sp8, temp_r29);
    }
    if (GetStructure_2(arg1, QB_TAGS, &spC, 0) != 0) {
        fn_8009E474(arg0, spC);
    }
    if (GetArray(arg1, QB_REMOVE_TAGS, &sp10, 0) != 0) {
        fn_8009E4B0(arg0, sp10);
    }
}
