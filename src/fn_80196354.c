// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196354-0x80196468 (276B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_8018C054(Unk_C7387A53 *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern s32 AddInteger(CStruct *, s32, s32);
extern s32 fn_80127C14(CStruct *, s32, CStruct *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
void fn_80196354(Unk_C8FEE62D *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r31;

    sp8 = 0;
    GetArray(arg0->unk0x20, QB_GOAL_OBJECTS, &sp8, 1);
    if (GetInteger((temp_r29 = fn_80129528(sp8, arg0->unk0x60)), QB_TIME,
                    &spC, 1) != 0) {
        fn_8018C054(arg0, spC);
    }
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80126FF4(temp_r31, arg0->unk0x20);
    fn_80126FF4(temp_r31, temp_r29);
    AddInteger(temp_r31, QB_GOAL_OBJECTS_INDEX, arg0->unk0x60);
    if (arg0->unk0x60 == 1) {
        fn_80127C14(temp_r31, QB_FIRST_SPOT_PARAMS, fn_80129528(sp8, 0));
    }
    Script_RunScript(QB_GOAL_SKATE_THE_LINE_NEXT_CLUSTER, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
}
