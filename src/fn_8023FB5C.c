// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023FB5C-0x8023FC44 (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 Script_GenerateCRC(s32);
extern void AddChecksum(CStruct *, s32, s32);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_801311A0(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, Unk_80577C09 *);
extern s32 fn_80128C80(CStruct *, void *, void *, s32);
extern s32 CStruct_delete(CStruct *, s32);
s32 fn_8023FB5C(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r31;

    temp_r29 = CStruct_ctor(CStruct_new(8));
    temp_r31 = CStruct_ctor(CStruct_new(8));
    sp8 = 0;
    AddChecksum(temp_r29, QB_KEY, Script_GenerateCRC(arg0));
    if (arg1 > -1) {
        AddInteger(temp_r29, QB_INDEX, arg1);
    }
    fn_801311A0(QB_PARKED_GETRESOURCEVALUE, temp_r29, 0, temp_r31);
    fn_80128C80(temp_r31, QB_SIZE, &sp8, 1);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    if (temp_r29 != 0) {
        CStruct_delete(temp_r29, 3);
    }
    return sp8;
}
