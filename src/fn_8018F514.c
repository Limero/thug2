// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018F514-0x8018F70C (504B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8018E6E4(Unk_C7387A53 * arg0);
extern void fn_8018E584(Unk_C7387A53 * arg0);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_80128978(s32 arg0, s32 arg1);
extern void CStruct_dtor(CStruct * arg0);
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern s32 fn_80127358(CStruct * arg0, Unk_C7387A53 * arg1);

void fn_8018F514(Unk_9AA07378 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 var_zero;
    s32 var_count;
    Unk_9994C3F5 *var_node;
    s32 temp_r3;
    Unk_4AA2E777 *temp_r9;

    var_zero = 0;
    sp8 = var_zero;
    GetInteger(arg1, QB_HASBEATEN, &sp8, 1);
    if (sp8 != 0) {
        temp_r9 = *((void * *)&arg0->unk0x14);
        ((void (*)(void *))temp_r9->unk0xDC)(
            (char *)arg0 + temp_r9->unk0xD8);
    }
    spC = 1;
    GetInteger(arg1, QB_ISLOCKED, &spC, 1);
    if (spC == 0) {
        fn_8018E6E4(arg0);
    }
    sp10 = var_zero;
    GetInteger(arg1, QB_HASSEEN, &sp10, 1);
    if (sp10 != 0) {
        fn_8018E584(arg0);
    }
    sp14 = var_zero;
    GetInteger(arg1, QB_WIN_RECORD, &sp14, 1);
    AddInteger(arg0->unk0x20, QB_WIN_RECORD, sp14);
    if (GetChecksum_2(arg0->unk0x20, QB_RECORD_TYPE, &sp18, 0) != 0) {
        if (sp18 == QB_TIME) {
            arg0->unk0x4C = sp14;
        } else if (sp18 == QB_SCORE) {
            arg0->unk0x50 = sp14;
        }
    }
    if (fn_80128978(arg1, QB_GOAL_FLAGS) != 0) {
        var_count = 0;
        CStruct_dtor(arg0->unk0x24);
        sp1C = var_count;
        GetStructure_2(arg1, QB_GOAL_FLAGS, &sp1C, 1);
        fn_80126FF4(arg0->unk0x24, sp1C);
        arg0->unk0x5C = var_count;
        arg0->unk0x60 = var_count;
        var_node = fn_80127358(arg0->unk0x24, 0);
        if (var_node != 0) {
            do {
                temp_r3 = fn_80127358(arg0->unk0x24, var_node);
                arg0->unk0x5C += 1;
                if (var_node->unk0x8 != 0) {
                    arg0->unk0x60 += 1;
                }
                var_node = temp_r3;
            } while (var_node != 0);
        }
    }
}
