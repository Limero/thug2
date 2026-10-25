// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A5DC-0x8003A730 (340B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void CStruct_dtor(CStruct *);
void fn_80127E70(s32, s32, s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 CStruct_ctor(s32);
s32 CStruct_new(s32);
// CModelAppearance_set_part @ 0x8003A5DC
void CModelAppearance_set_part(s32, CStruct *, s32, CStruct *);
void CModelAppearance_set_part(s32 arg0, CStruct *arg1, s32 arg2, CStruct *arg3) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;

    temp_r30 = arg0 + 0x58;
    if (GetStructure_2(temp_r30, arg1, &sp8, 0) == 0) {
        temp_r3 = CStruct_ctor(CStruct_new(8));
        sp8 = temp_r3;
        fn_80127E70(temp_r30, arg1, 0xB, temp_r3);
    }
    CStruct_dtor(sp8);
    spC = 1;
    GetInteger(arg3, QB_USE_DEFAULT_HSV, &spC, 0);
    if (spC == 0) {
        GetInteger(arg3, QB_H, &sp10, 1);
        GetInteger(arg3, QB_S, &sp14, 1);
        GetInteger(arg3, QB_V, &sp18, 1);
        AddInteger(sp8, QB_USE_DEFAULT_HSV, 0);
        AddInteger(sp8, QB_H, sp10);
        AddInteger(sp8, QB_S, sp14);
        AddInteger(sp8, QB_V, sp18);
    }
    AddChecksum(sp8, QB_DESC_ID, arg2);
}
