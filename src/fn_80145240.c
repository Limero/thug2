// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145240-0x8014535C (284B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
void GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80145240(s32 arg0, CStruct *arg1) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r4;
    s32 var_r29;
    void **var_r31;
    CStruct *temp_r9;

    sp8 = 0;
    GetArray(arg1, QB_TRICKS, &sp8, 0);
    var_r31 = arg0 + 0x194;
    var_r29 = 0;
    do {
        temp_r4 = var_r29;
        var_r29 += 1;
        temp_r30 = fn_80129528(sp8, temp_r4);
        spC = 0;
        GetStructure_2(temp_r30, QB_OTHER, &spC, 1);
        fn_80126FF4(*(s32 *)((s32 *)(*((s32 *)var_r31)) + 0x0), spC);
        sp10 = 0;
        GetArray(temp_r30, QB_ANIMATIONS, &sp10, 1);
        fn_80126E28(*(s32 *)((char *)(*((s32 *)var_r31)) + (s32)0x8), sp10);
        sp14 = 0;
        GetArray(temp_r30, QB_ROTATIONS, &sp14, 1);
        temp_r9 = *((s32 *)var_r31);
        var_r31 = (void **)((char *)var_r31 + 4);
        fn_80126E28(temp_r9->unk0x4, sp14);
    } while (var_r29 <= 0xA);
    Script_RunScript(QB_KILL_LOAD_PREMADE_CATS, 0, 0, 0, 0);
}
