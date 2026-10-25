// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BA34-0x8018BC14 (480B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void CStruct_dtor(CStruct *);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 GetChecksum(CStruct *, s32);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_80127C14(CStruct *, s32, CStruct *);
extern void CStruct_delete(CStruct *, s32);
void fn_8018BA34(Unk_C7387A53 *arg0, CStruct *arg1) {
    void *sp8;
    s32 spC;
    void *sp10;
    s32 var_i;
    s32 var_j;
    s32 var_k;
    s32 var_count;
    s32 var_count2;
    s32 temp_arr;
    s32 var_handle;

    CStruct_dtor(arg0->unk0x24);
    arg0->unk0x5C = 0;
    if (GetArray(arg1, QB_GOAL_FLAGS, &sp8, 0) != 0) {
        if (((Unk_A5D07D11 *)sp8)->unk0x2 == 0xA) {
            AddChecksum(arg0->unk0x24, 0, QB_SKATER_FLAGS);
            var_count = ((Unk_A5D07D11 *)sp8)->unk0x4;
            for (var_i = 0; var_i < var_count; var_i++) {
                GetChecksum_2(temp_arr = fn_80129528((s32)sp8, var_i), QB_SKATER, &spC, 1);
                var_handle = CStruct_ctor(CStruct_new(8));
                GetArray(temp_arr, QB_GOAL_FLAGS, &sp10, 1);
                var_count2 = ((CStruct *)sp10)->unk0x4;
                for (var_j = 0; var_j < var_count2; var_j++) {
                    AddInteger(var_handle, GetChecksum((s32)sp10, var_j), 0);
                }
                AddInteger(var_handle, QB_NUM_FLAGS, var_count2);
                AddInteger(var_handle, QB_NUM_FLAGS_SET, 0);
                fn_80127C14(arg0->unk0x24, spC, var_handle);
                if (var_handle != 0) {
                    CStruct_delete(var_handle, 3);
                }
            }
        } else {
            for (var_k = 0; (u32)var_k < (u32)(((Unk_A5D07D11 *)sp8)->unk0x4); var_k++) {
                AddInteger(arg0->unk0x24, GetChecksum((s32)sp8, var_k), 0);
                arg0->unk0x5C += 1;
            }
        }
    }
    AddInteger(arg0->unk0x20, QB_NUM_FLAGS, arg0->unk0x5C);
}
